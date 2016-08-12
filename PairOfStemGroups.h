#pragma once

#include <algorithm>
#include "StemMap.h"

typedef std::pair<std::vector<Stem*>, std::vector<std::complex<double>>> StemTriplet;

class PairOfStemGroups
{
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW // Fixes wierd memory crashes
	PairOfStemGroups(StemTriplet& targetTriplet, StemTriplet& sourceTriplet);
	~PairOfStemGroups();
	double getLikelihood() const;
	const std::vector<double>& getRadiusSimilarity() const;
	Eigen::Matrix4d computeBestTransform();
	Eigen::Matrix4d getBestTransform() const;
	const std::vector<Stem*> getTargetGroup() const;
	const std::vector<Stem*> getSourceGroup() const;
	void addFittingStem(Stem* sourceStem, Stem* targetStem);
	// To sort by likelihood, and if the transform is computed sort by MSE
	friend bool operator<(PairOfStemGroups& l, PairOfStemGroups& r);
	double meanSquareError();

private:
	void sortStems();
	void updateRadiusSimilarity();
	/* They are only triplet at first. We'll add other stems that fit the model later.
	These are a copy of the vector created by the Registration class. We need to copy them
	because differents pair will generate different models, which means in some case we we'll have
	to add a stem to a group, some case not. When we add a stem to a group we don't want to add it in every pair!

	TODO rendre ca plus clair
	*/
	std::vector<Stem*> targetGroup;
	std::vector<Stem*> sourceGroup;
	double likelihood;
	/* They should be real but I put a complex type this way the
	compiler won't complain */
	std::vector<std::complex<double>> eigenValuesTarget;
	std::vector<std::complex<double>> eigenValuesSource;
	std::vector<double> radiusSimilarity;
	/* This is sadly necessary because of alignement issues in Eigen. Declaring
	the transorm matrix as dynamically sized instead of 4x4 fixes bugs with matrix
	operations in MSVSC++ 2013 */
	Eigen::MatrixXd bestTransform;
	bool transformComputed;
};

