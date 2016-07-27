#pragma once

#include <algorithm>
#include "StemMap.h"

typedef std::pair<std::vector<Stem*>, std::vector<std::complex<double>>> StemTriplet;

class PairOfStemsTriplet
{
public:
	PairOfStemsTriplet(StemTriplet& targetTriplet, StemTriplet& sourceTriplet);
	~PairOfStemsTriplet();
	double getLikelihood() const;
	const Eigen::Matrix4d& getBestTransform() const;

private:
	void calculateLikeliness();

	std::vector<Stem*> targetTriplet;
	std::vector<Stem*> sourceTriplet;
	StemMap* targetMap;
	StemMap* sourceMap;
	double likelihood;
	std::vector<std::complex<double>> eigenValuesTarget;
	std::vector<std::complex<double>> eigenValuesSource;
	Eigen::Matrix4d bestTransform;
};

