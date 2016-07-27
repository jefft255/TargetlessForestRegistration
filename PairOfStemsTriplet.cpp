#include "PairOfStemsTriplet.h"
#include <Eigen/Eigenvalues>
#include <math.h>

PairOfStemsTriplet::PairOfStemsTriplet(StemTriplet& targetTriplet, StemTriplet& sourceTriplet)
{
}


PairOfStemsTriplet::~PairOfStemsTriplet()
{
}

void PairOfStemsTriplet::calculateLikeliness()
{

}

double PairOfStemsTriplet::getLikelihood() const 
{
	// TODO. Kelbe ne considere pas les valeurs complexes?????
	return pow(this->eigenValuesTarget[0].real() - this->eigenValuesSource[0].real(),2) +
		pow(this->eigenValuesTarget[1].real() - this->eigenValuesSource[1].real(),2);
}