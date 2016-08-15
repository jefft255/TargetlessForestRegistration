#pragma once

#include "PairOfStemGroups.h"
#include <numeric>
#include <list>

// Define thresold for colinear data
#define LINEARITY_TOL 0.975

typedef std::pair<std::vector<Stem*>, std::vector<std::complex<double>>> StemTriplet;

class Registration
{
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
	Registration(StemMap& target, StemMap& source, double diamErrorTol);
	~Registration();
	void computeBestTransform();

private:
	unsigned int removeLonelyStems();
	void generateTriplets(StemMap& stemMap, std::vector<StemTriplet>& threePerm);
	unsigned int generatePairs();
	void generateAllEigenValues();
	void generateEigenValues(StemTriplet& triplet);
	void removeHighlyColinearTriplets(std::vector<StemTriplet>& triplets);	
	void sortPairsByLikelihood();
	// This removes of non-matching pair of triplets.
	bool diametersNotCorresponding(PairOfStemGroups& pair);
	// This is used for the removal of non-matching pair of triplets (diametersNotCorresponding).
	bool diamErrorGreaterThanTol(double error);
	void RANSACtransform(PairOfStemGroups& pair);

	double diamErrorTol;
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
	and another from the source. Used list because we are going to be deleting
	a lot of pairs as we go along. */
	std::vector<PairOfStemGroups> pairsOfStemTriplets;
};

