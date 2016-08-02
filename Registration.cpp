#include "Registration.h"

double getMeanOfVector(Eigen::Vector4d& coords);
std::vector<std::vector<int>> nPerm(int n, int k);

Registration::Registration()
{
	this->generateTriplets();
	this->generateAllEigenValues();
	this->generatePairs();
	this->removeHighlyColinearPairs();
	this->removePairsWithDissimilarRadius();
	this->removePairsWithLowLikelihood();
}


Registration::~Registration()
{
}

int Factorial(int n)
{
	int result = 1;
	while (n>1) {
		result *= n--;
	}
	return result;
}

/* Found on stackoverflow, user Vaughn Cato
http://stackoverflow.com/questions/28711797/generating-n-choose-k-permutations-in-c */
std::vector<std::vector<int>> nPerm(int n, int k)
{
	std::vector<std::vector<int>> result;
	std::vector<int> d(n);
	std::iota(d.begin(), d.end(), 1);
	int repeat = Factorial(n - k);
	do
	{
		std::vector<int> tempPerm = {};
		for (int i = 0; i < k; i++)
		{
			tempPerm.push_back(d[i]);
		}
		result.push_back(tempPerm);
		for (int i = 1; i != repeat; ++i)
		{
			next_permutation(d.begin(), d.end());
		}
	} while (next_permutation(d.begin(), d.end()));

	return result;
}

void Registration::generateEigenValues(StemTriplet& triplet)
{
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
	std::get<1>(triplet)[0] = eigenvalues(0);
	std::get<1>(triplet)[1] = eigenvalues(1);
	std::get<1>(triplet)[2] = eigenvalues(2);
}

void Registration::generateAllEigenValues()
{
	for (auto it = this->threePermSource.begin(); it != this->threePermSource.end(); ++it)
	{
		this->generateEigenValues(*it);
	}
	for (auto it = this->threePermTarget.begin(); it != this->threePermTarget.end(); ++it)
	{
		this->generateEigenValues(*it);
	}
}

// This is useful for computing the covariance matrix.
double getMeanOfVector(Eigen::Vector4d& coords)
{
	return (coords[0] + coords[1] + coords[2]) / 3;
}

/* This function populate the stem triplets from both the target scan and the source scan.
   We use the nPerm function to determine all the possible permutations. */
void Registration::generateTriplets()
{
	std::vector<std::vector<int>> threePermNSource = nPerm(3, this->source.getStems().size());
	std::vector<std::vector<int>> threePermNTarget = nPerm(3, this->target.getStems().size());
	StemTriplet tempTriplet = StemTriplet();
	for (auto it = threePermNSource.begin(); it != threePermNSource.end(); ++it)
	{
		std::get<0>(tempTriplet).push_back(&this->source.getStems()[(*it)[0]]);
		std::get<0>(tempTriplet).push_back(&this->source.getStems()[(*it)[1]]);
		std::get<0>(tempTriplet).push_back(&this->source.getStems()[(*it)[2]]);
		this->threePermSource.push_back(tempTriplet);
		tempTriplet = StemTriplet();
	}
	for (auto it = threePermNTarget.begin(); it != threePermNTarget.end(); ++it)
	{
		std::get<0>(tempTriplet).push_back(&this->target.getStems()[(*it)[0]]);
		std::get<0>(tempTriplet).push_back(&this->target.getStems()[(*it)[1]]);
		std::get<0>(tempTriplet).push_back(&this->target.getStems()[(*it)[2]]);
		this->threePermTarget.push_back(tempTriplet);
		tempTriplet = StemTriplet();
	}
}

void Registration::generatePairs()
{
	for (auto itSource = this->threePermSource.begin(); itSource != this->threePermSource.begin(); ++itSource)
	{
		for (auto itTarget = this->threePermSource.begin(); itTarget != this->threePermSource.begin(); ++itTarget)
		{
			PairOfStemGroups tempPair(*itTarget, *itSource);
			this->pairsOfStemTriplets.push_back(tempPair);
		}
	}
}
void Registration::removePairsWithDissimilarRadius() {}
void Registration::removePairsWithLowLikelihood() {}
void Registration::removeHighlyColinearPairs() {}