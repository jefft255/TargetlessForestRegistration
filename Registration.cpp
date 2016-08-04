#include "Registration.h"
#include <unordered_set>
#include <set>

// Helper functions declaration
double getMeanOfVector(Eigen::Vector4d& coords);
std::vector<std::set<int>> nCombk(const int n, const int k);
bool diametersNotCorresponding(PairOfStemGroups& pair);
bool diamErrorGreaterThanTol(double error);
bool colinearityGreaterThanTol(StemTriplet& triplet);
// Define radius error tolerance here, as well as the thresold for colinear data
const double Registration::DIAMETER_ERROR_TOL = 0.2;
const double Registration::LINEARITY_TOL = 0.975;

// Getting ready for RANSAC, no heavy computation yet.
Registration::Registration(StemMap& target, StemMap& source) : target(target), source(source)
{
	this->generateTriplets(this->source, this->threePermSource);
	this->generateTriplets(this->target, this->threePermTarget);
	this->generateAllEigenValues();
	this->removeHighlyColinearTriplets(this->threePermSource);
	this->removeHighlyColinearTriplets(this->threePermTarget);
	this->generatePairs();
	this->removePairsWithDissimilarRadius();
	this->sortPairsByLikelihood();
}

void
Registration::computeBestTransform()
{
	for (auto& it : this->pairsOfStemTriplets)
	{
		auto printTransform = it.computeBestTransform();
		std::cout << printTransform << std::endl << std::endl;
	}
}


Registration::~Registration()
{
}

int
Factorial(int n)
{
	int result = 1;
	while (n>1) {
		result *= n--;
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
	int repeat = Factorial(n - k);
	do
	{
		std::set<int> tempPerm = {};
		for (int i = 0; i < k; i++)
		{
			tempPerm.insert(d[i]);
		}
		resultP.push_back(tempPerm);
		for (int i = 1; i != repeat; ++i)
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
getMeanOfVector(Eigen::Vector4d& coords)
{
	return (coords[0] + coords[1] + coords[2]) / 3;
}

/* This function populate the stem triplets from both the target scan and the source scan.
   We use the nPerm function to determine all the possible combinations. */
void
Registration::generateTriplets(StemMap& stemMap, std::vector<StemTriplet>& threePerm)
{
	std::vector<std::set<int>> threePermN = nCombk(stemMap.getStems().size(), 3);
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
void
Registration::generatePairs()
{
	for (auto& itSource : this->threePermSource)
	{
		for (auto& itTarget : this->threePermTarget)
		{
			PairOfStemGroups tempPair(itTarget, itSource);
			this->pairsOfStemTriplets.push_back(tempPair);
		}
	}
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
	return error > Registration::DIAMETER_ERROR_TOL;
}

/* This is used to determine if the triplet of stem is too linear, which makes
   it unfit for the rigid transform. */
bool
colinearityGreaterThanTol(StemTriplet& triplet)
{
	return std::get<1>(triplet)[0].real() / (std::get<1>(triplet)[0].real() + std::get<1>(triplet)[1].real())
		> Registration::LINEARITY_TOL;
}