#pragma once

#include "StemMap.h"
#include <algorithm>
#include <numeric>

class Registration
{
public:
	Registration();
	~Registration();

private:
	void generateTriplets(StemMap& stemMap, std::vector<std::vector<Stem*>>& permList);
	void generatePairs();
	void calculateLikeliness();
	void generateEigenValues();

	StemMap target;
	StemMap source;
	/* These two attributes contains, for each stem map, every way to choose
	three stem from the map. */
	std::vector<std::vector<Stem*>> threePermTarget;
	std::vector<std::vector<Stem*>> threePermSource;
	/* Contains all possible combinaison of 2 triplets of trees, one from the target
	and another from the source */
	std::vector<std::tuple<std::vector<Stem*>, std::vector<Stem*>>> pairsOfStemTriplets;
};

