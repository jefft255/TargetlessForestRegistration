/***************************************************************************
 *   Copyright (C) 2017 by Jean-François Tremblay                          *
 *   jftremblay255@gmail.com                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

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
