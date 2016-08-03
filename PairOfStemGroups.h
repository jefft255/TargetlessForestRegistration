#pragma once

#include <algorithm>
#include "StemMap.h"

typedef std::pair<std::vector<Stem*>, std::vector<std::complex<double>>> StemTriplet;

class PairOfStemGroups
{
public:
	PairOfStemGroups(StemTriplet& targetTriplet, StemTriplet& sourceTriplet);
	~PairOfStemGroups();
	double getLikelihood() const;
	const std::vector<double>& getRadiusSimilarity() const;
	const Eigen::Matrix4d computeBestTransform();
	const Eigen::Matrix4d getBestTransform();
	void addFittingStem(Stem* sourceStem, Stem* targetStem);
	// To sort by likelihood
	friend bool operator<(PairOfStemGroups& l, PairOfStemGroups& r);

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
	Eigen::Matrix4d bestTransform;
};

