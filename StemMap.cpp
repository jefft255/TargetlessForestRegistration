#include "StemMap.h"


StemMap::StemMap()
{
	this->stems = std::vector<Stem>();
	this->transMatrix = Eigen::Matrix4f::Identity(); // No transform applied yet
}


StemMap::~StemMap()
{
}

void StemMap::applyTransMatrix(Eigen::Matrix4f const &transMatrix)
{
	// Could gain significant speedup from parralelization
	for (auto it = this->stems.begin(); it != stems.end(); it++)
	{
		it->changeCoords(transMatrix);
	}

	this->transMatrix *= transMatrix; // We store the transformation
}

void StemMap::restoreOriginalCoords()
{
	// Simply apply the inverse transform!!
	this->applyTransMatrix(this->transMatrix.inverse());
}

void StemMap::addStem(Stem &stem)
{
	this->stems.push_back(stem);
}