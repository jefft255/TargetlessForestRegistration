#include "Registration.h"
#include <unordered_set>
#include <set>
#include <atomic>

// Helper functions declaration
double getMeanOfVector(const Eigen::Vector4d& coords);
std::vector<std::set<int>> nCombk(const int n, const int k);
std::vector<std::set<int>> threeCombkV2(const unsigned int k);
bool diametersNotCorresponding(PairOfStemGroups& pair);
bool diamErrorGreaterThanTol(double error);
bool colinearityGreaterThanTol(StemTriplet& triplet);

// Getting ready for RANSAC, no heavy computation yet.
Registration::Registration(StemMap& target, StemMap& source) : target(target), source(source)
{
	std::cout << "Nbr de souche toute seule : " << this->removeLonelyStems() << std::endl;
	std::cout << "Generation des triplets... " << std::endl;
	this->generateTriplets(this->source, this->threePermSource);
	this->generateTriplets(this->target, this->threePermTarget);
	this->generateAllEigenValues();
	this->removeHighlyColinearTriplets(this->threePermSource);
	this->removeHighlyColinearTriplets(this->threePermTarget);
	std::cout << "Generation des pairs de triplet... " << std::endl;
	this->generatePairs();
	this->removePairsWithDissimilarRadius();
	std::cout << this->pairsOfStemTriplets.size() << " de transformation a calculer. " << std::endl;
	this->sortPairsByLikelihood();
}

void
Registration::computeBestTransform()
{
	std::cout << "Calcul des transformations... " << std::endl;
	for (auto& it : this->pairsOfStemTriplets)
	{
		it.computeBestTransform();
		// std::cout << printTransform << std::endl << std::endl;
	}
	this->pairsOfStemTriplets.sort();
	std::cout << "====== Best transform ======" << std::endl
		<< this->pairsOfStemTriplets.begin()->getBestTransform() << std::endl
		<< "MSE : " << this->pairsOfStemTriplets.begin()->meanSquareError() << std::endl
		<< "------ Candidats pour l'alignements -----" << std::endl
		<< "Target : " << std::endl
		<< "Stem 1 : " << this->pairsOfStemTriplets.begin()->getTargetGroup()[0]->getCoords()
		<< std::endl << "Radius : " << this->pairsOfStemTriplets.begin()->getTargetGroup()[0]->getRadius() << std::endl
		<< "Stem 2 : " << this->pairsOfStemTriplets.begin()->getTargetGroup()[1]->getCoords()
                << std::endl << "Radius : " << this->pairsOfStemTriplets.begin()->getTargetGroup()[1]->getRadius() << std::endl
		<< "Stem 3 : " << this->pairsOfStemTriplets.begin()->getTargetGroup()[2]->getCoords()
                << std::endl << "Radius : " << this->pairsOfStemTriplets.begin()->getTargetGroup()[2]->getRadius() << std::endl
		<< "Source : " << std::endl
                << "Stem 1 : " << this->pairsOfStemTriplets.begin()->getSourceGroup()[0]->getCoords()
                << std::endl << "Radius : " << this->pairsOfStemTriplets.begin()->getSourceGroup()[0]->getRadius() << std::endl
                << "Stem 2 : " << this->pairsOfStemTriplets.begin()->getSourceGroup()[1]->getCoords()
                << std::endl << "Radius : " << this->pairsOfStemTriplets.begin()->getSourceGroup()[1]->getRadius() << std::endl
                << "Stem 3 : " << this->pairsOfStemTriplets.begin()->getSourceGroup()[2]->getCoords()
                << std::endl << "Radius : " << this->pairsOfStemTriplets.begin()->getSourceGroup()[2]->getRadius() << std::endl;
}


Registration::~Registration()
{
}

unsigned int
Registration::removeLonelyStems()
{
	bool toBeRemoved;
	std::vector<size_t> indicesToRemove = {};
	unsigned int nRemoved = 0;
	size_t i = 0;
	for (auto& itSource : this->source.getStems())
	{
		toBeRemoved = true;
		for (auto& itTarget : this->target.getStems())
		{
			if (!diamErrorGreaterThanTol(
				(fabs(itSource.getRadius() - itTarget.getRadius()) /
				((itSource.getRadius() + itTarget.getRadius())/2))
				))
			{
				toBeRemoved = false;
			}
		}
		if (toBeRemoved)
		{
			indicesToRemove.push_back(i);
			++nRemoved;
		}
		++i;
	}
	// If any stem has to be removed
	if (indicesToRemove.size() > 0)
	{
		// Remove the stems backward so the indices are not all shuffled up
		for (size_t j = indicesToRemove.size() - 1; j > 0; --j)
		{
			this->source.getStems().erase(this->source.getStems().begin() + indicesToRemove[j]);
		}
	}
	// Repeat for the target map
	indicesToRemove = {};
	i = 0;
	for (auto& itTarget : this->target.getStems())
	{
		toBeRemoved = true;
		for (auto& itSource : this->source.getStems())
		{
			if (!diamErrorGreaterThanTol(
				fabs(itSource.getRadius() - itTarget.getRadius())
				))
			{
				toBeRemoved = false; 
			}
		}
		if (toBeRemoved)
		{
			indicesToRemove.push_back(i);
			++nRemoved;
		}
		++i;
	}
	if (indicesToRemove.size() > 0)
	{
		// Remove the stems backward so the indices are not all shuffled up
		for (size_t j = indicesToRemove.size() - 1; j > 0; --j)
		{
			this->target.getStems().erase(this->target.getStems().begin() + indicesToRemove[j]);
		}
	}
	return nRemoved;
}

long long
Factorial(int n)
{
	long long result = 1;
	while (n>1) {
		result *= n--;
	}
	return result;
}


std::vector<std::set<int>>
threeCombkV2(const unsigned int k)
{
	std::vector<std::set<int>> result;
	std::set<int> comb;
		
	for (unsigned int i = 1; i < k - 1; ++i)
	{
		for (unsigned int j = i; j < k; ++j)
		{
			for (unsigned int s = j; s <= k; ++s)
			{
				comb.insert(i);
				comb.insert(j);
				comb.insert(s);
				// Only add combinaison if the numbers are unique
				if (comb.size() == 3)
					result.push_back(comb);
				comb = std::set<int>();
			}
		}
	}

	return result;
}

/* Found on stackoverflow, user Vaughn Cato. I used his permutation function to
generate combinations.
http://stackoverflow.com/questions/28711797/generating-n-choose-k-permutations-in-c */
std::vector<std::set<int>>
nCombk(const int n, const int k)
{
	std::vector<std::set<int>> resultP;
	std::vector<int> d(n);
	std::iota(d.begin(), d.end(), 1);
	long long repeat = Factorial(n - k);
	do
	{
		std::set<int> tempPerm = {};
		for (long long i = 0; i < k; i++)
		{
			tempPerm.insert(d[i]);
		}
		resultP.push_back(tempPerm);
		for (long long i = 1; i != repeat; ++i)
		{
			next_permutation(d.begin(), d.end());
		}
	} while (next_permutation(d.begin(), d.end()));

	// Remove the duplicate (without order), we want combinations not permutations.
	std::vector<std::set<int>> resultC;
	bool permAlreadyThere = false;
	for (auto& perm : resultP)
	{
		for (auto& comb : resultC)
		{
			if (perm == comb)
			{
				permAlreadyThere = true;
				break;
			}
		}
		if (!permAlreadyThere) resultC.push_back(perm);
		permAlreadyThere = false;
	}

	return resultC;
}

void
Registration::generateEigenValues(StemTriplet& triplet)
{
	// Can be coded much cleaner. Needs to be revisited.
	Eigen::Matrix3d covarianceMatrix;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			covarianceMatrix(i, j) =
				 ((std::get<0>(triplet))[i]->getCoords()[0] - getMeanOfVector((std::get<0>(triplet))[i]->getCoords()))
				*((std::get<0>(triplet))[j]->getCoords()[0] - getMeanOfVector((std::get<0>(triplet))[j]->getCoords()))
				+((std::get<0>(triplet))[i]->getCoords()[1] - getMeanOfVector((std::get<0>(triplet))[i]->getCoords()))
				*((std::get<0>(triplet))[j]->getCoords()[1] - getMeanOfVector((std::get<0>(triplet))[j]->getCoords()))
				+((std::get<0>(triplet))[i]->getCoords()[2] - getMeanOfVector((std::get<0>(triplet))[i]->getCoords()))
				*((std::get<0>(triplet))[j]->getCoords()[2] - getMeanOfVector((std::get<0>(triplet))[j]->getCoords()));
		}
	}
	Eigen::Matrix3d::EigenvaluesReturnType eigenvalues = covarianceMatrix.eigenvalues();
	std::get<1>(triplet).push_back(eigenvalues(0));
	std::get<1>(triplet).push_back(eigenvalues(1));
	std::get<1>(triplet).push_back(eigenvalues(2));
}

void
Registration::generateAllEigenValues()
{
	for (auto& it : this->threePermSource)
	{
		this->generateEigenValues(it);
	}
	for (auto& it : this->threePermTarget)
	{
		this->generateEigenValues(it);
	}
}

// This is useful for computing the covariance matrix.
double
getMeanOfVector(const Eigen::Vector4d& coords)
{
	return (coords[0] + coords[1] + coords[2]) / 3;
}

/* This function populate the stem triplets from both the target scan and the source scan.
   We use the nPerm function to determine all the possible combinations. */
void
Registration::generateTriplets(StemMap& stemMap, std::vector<StemTriplet>& threePerm)
{
	std::vector<std::set<int>> threePermN = threeCombkV2(stemMap.getStems().size());
	StemTriplet tempTriplet = StemTriplet();
	
	for (auto it : threePermN)
	{
		for (auto jt : it) // -1 because the combinations start at 1 instead of 0.
			std::get<0>(tempTriplet).push_back(&stemMap.getStems()[jt - 1]);
		threePerm.push_back(tempTriplet);
		tempTriplet = StemTriplet();
	}
}

// Population the pairOfStemsTriplets attributes with all possible pairs. Cleanup is done later.
unsigned int
Registration::generatePairs()
{
	unsigned int nInvalidPairs = 0;
	#pragma omp parallel for
	for (size_t i = 0; i < this->threePermSource.size(); ++i)
	{
		for (size_t j = 0; j < this->threePermTarget.size(); ++j)
		{
			PairOfStemGroups tempPair(this->threePermTarget[j], this->threePermSource[i]);
			if(!diametersNotCorresponding(tempPair))
			{	
				#pragma omp critical
				{
					this->pairsOfStemTriplets.push_back(tempPair);
					//std::cout << "Bingo" << std::endl;
				}
				
			}
			else
			{
			//	nInvalidPairs++;
			}
		}
	}
	return nInvalidPairs;
}

void
Registration::removePairsWithDissimilarRadius()
{
	this->pairsOfStemTriplets.erase(
		std::remove_if(this->pairsOfStemTriplets.begin(), this->pairsOfStemTriplets.end(), diametersNotCorresponding),
		this->pairsOfStemTriplets.end());
}

void
Registration::sortPairsByLikelihood()
{
	this->pairsOfStemTriplets.sort();
}

void
Registration::removeHighlyColinearTriplets(std::vector<StemTriplet>& triplets)
{
	triplets.erase(std::remove_if(triplets.begin(), triplets.end(), colinearityGreaterThanTol),
		triplets.end());
}

// This removes of non-matching pair of triplets.
bool
diametersNotCorresponding(PairOfStemGroups& pair)
{
	return std::find_if(pair.getRadiusSimilarity().begin(), pair.getRadiusSimilarity().end(), diamErrorGreaterThanTol)
		!= pair.getRadiusSimilarity().end();
}

// This is used for the removal of non-matching pair of triplets (diametersNotCorresponding).
bool
diamErrorGreaterThanTol(double error)
{
	return error > DIAMETER_ERROR_TOL;
}

/* This is used to determine if the triplet of stem is too linear, which makes
   it unfit for the rigid transform. */
bool
colinearityGreaterThanTol(StemTriplet& triplet)
{
	return std::get<1>(triplet)[0].real() / (std::get<1>(triplet)[0].real() + std::get<1>(triplet)[1].real())
		> LINEARITY_TOL;
}
