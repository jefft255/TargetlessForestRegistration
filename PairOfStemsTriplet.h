#pragma once

#include <algorithm>
#include "StemMap.h"

class PairOfStemsTriplet
{
public:
	PairOfStemsTriplet();
	~PairOfStemsTriplet();
	float getLikelihood();
	Eigen::Matrix4d& getBestTransform();

private:
	void calculateLikeliness();
	void generateCovarianceMatrix();
	void generateEigenValues();

	std::vector<Stem*> targetTriplet;
	std::vector<Stem*> targetSource;
	StemMap* targetMap;
	StemMap* sourceMap;
	double likelihood;
	Eigen::Vector3d eigenValues;
	Eigen::Matrix3d covarianceMatrix;
	Eigen::Matrix4d bestTransform;
};

