#pragma once

#include <algorithm>
#include "StemMap.h"

class PairOfStemsTriplet
{
public:
	PairOfStemsTriplet();
	~PairOfStemsTriplet();
	void calculateLikeliness();
	void generateEigenValues();
	float getLikeliness();
	Eigen::Matrix4d& getBestTransform();

private:
	std::vector<Stem*> targetTriplet;
	std::vector<Stem*> targetSource;
	StemMap* targetMap;
	StemMap* sourceMap;
	double likeliness;
	Eigen::Vector3i eigenValues;
	Eigen::Matrix4d bestTransform;
};

