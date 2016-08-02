#pragma once

#include "StemMap.h"
#include "PairOfStemGroups.h"
#include <algorithm>
#include <numeric>

typedef std::pair<std::vector<Stem*>, std::vector<std::complex<double>>> StemTriplet;

class Registration
{
public:
	Registration();
	~Registration();

private:
	void generateTriplets();
	void generatePairs();
	void generateAllEigenValues();
	void generateEigenValues(StemTriplet& triplet);
	void removePairsWithDissimilarRadius();
	void removePairsWithLowLikelihood();

	StemMap target;
	StemMap source;
	/* These two attributes contains, for each stem map, every way to choose
	three stem from the map. The complex vector contains the eigenvalues associated
	with the covariance matrix of the vector. It is here and not in the PairOfStemTriplets
	class because it would result in the eigenvalues being computed multiplet times
	for the same triplet which is computationally expensive. */
	std::vector<StemTriplet> threePermTarget;
	std::vector<StemTriplet> threePermSource;
	/* Contains all possible combinaison of 2 triplets of trees, one from the target
	and another from the source */
	std::vector<PairOfStemGroups> pairsOfStemTriplets;
};

