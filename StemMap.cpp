#include "StemMap.h"


StemMap::StemMap()
{
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
	this->applyTransMatrix(this->transMatrix.inverse());
}