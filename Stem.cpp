#include "Stem.h"


Stem::Stem(float x, float y, float z, float radius)
{
	this->coords(0) = x;
	this->coords(1) = y;
	this->coords(2) = z;
	this->coords(3) = 1;
	this->radius = radius;
}


Stem::~Stem()
{
}

void Stem::changeCoords(Eigen::Matrix4f const &transMatrix)
{
	this->coords = transMatrix*this->coords;
}