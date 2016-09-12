#include "Stem.h"
#include <stdexcept>

namespace tlr 
{

Stem::Stem() {}

Stem::Stem(double x, double y, double z, double radius)
{
	if (radius < 0) throw std::invalid_argument("Radius must be positive");

	this->coords(0) = x;
	this->coords(1) = y;
	this->coords(2) = z;
	this->coords(3) = 1;
	this->radius = radius;
}

Stem::Stem(const Stem& stem)
{
	this->coords = stem.coords;
	this->radius = stem.radius;
}

Stem::~Stem()
{
}

void
Stem::changeCoords(const Eigen::Matrix4d& transMatrix)
{
	this->coords = transMatrix*this->coords;
}

const Eigen::Vector4d&
Stem::getCoords() const
{
	return this->coords;
}
void
Stem::setCoords(const Eigen::Vector4d& coords)
{
	if (coords[3] != 1) throw std::invalid_argument("4th element must be 1");
	this->coords = coords;
}

double
Stem::getRadius() const
{
	return this->radius;
}

void
Stem::setRadius(const double& radius)
{
	if (radius < 0) throw std::invalid_argument("Radius must be positive");
	this->radius = radius;
}

bool
Stem::operator==(const Stem& stem) const
{
	return stem.coords == this->coords && stem.radius == this->radius;
}

} // namespace tlr