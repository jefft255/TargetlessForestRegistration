#include "PairOfStemsTriplet.h"
#include <Eigen/Eigenvalues>

float getMeanOfVector(Eigen::Vector4d& coords);

PairOfStemsTriplet::PairOfStemsTriplet()
{
}


PairOfStemsTriplet::~PairOfStemsTriplet()
{
}

void PairOfStemsTriplet::generateCovarianceMatrix()
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			this->covarianceMatrix(i, j) =
				 (this->targetTriplet[i]->getCoords()[0] - getMeanOfVector(this->targetTriplet[i]->getCoords()))
				*(this->targetSource[j]->getCoords()[0]  - getMeanOfVector(this->targetSource[j]->getCoords()))
				+(this->targetTriplet[i]->getCoords()[1] - getMeanOfVector(this->targetTriplet[i]->getCoords()))
				*(this->targetSource[j]->getCoords()[1]  - getMeanOfVector(this->targetSource[j]->getCoords()))
				+(this->targetTriplet[i]->getCoords()[2] - getMeanOfVector(this->targetTriplet[i]->getCoords()))
				*(this->targetSource[j]->getCoords()[2]  - getMeanOfVector(this->targetSource[j]->getCoords()));
		}
	}
}

float getMeanOfVector(Eigen::Vector4d& coords)
{
	return (coords[0] + coords[1] + coords[2]) / 3;
}

void PairOfStemsTriplet::generateEigenValues()
{
	this->eigenValues = this->covarianceMatrix.eigenvalues;
}