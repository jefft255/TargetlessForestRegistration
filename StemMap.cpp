#include "StemMap.h"


StemMap::StemMap()
{
	this->stems = std::vector<Stem>();
	this->transMatrix = Eigen::Matrix4d::Identity(); // No transform applied yet
}


StemMap::~StemMap()
{
}

void StemMap::applyTransMatrix(Eigen::Matrix4d const &transMatrix)
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
	this->transMatrix = Eigen::Matrix4d::Identity();
}

void StemMap::addStem(Stem &stem)
{
	this->stems.push_back(stem);
}

std::string StemMap::strStemMap()
{
	std::stringstream output;
	for (auto it = this->stems.begin(); it != stems.end(); it++)
	{
		output << "Coords : " << it->getCoords();
		output << ", Radius : " << it->getRadius() << std::endl;
	}

	return output.str();
}