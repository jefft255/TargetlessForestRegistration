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

#ifndef TLR_STEM_H_
#define TLR_STEM_H_

#include <vector>
#include <Eigen/Dense>

namespace tlr
{

class Stem
{
 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  Stem();
  Stem(double x, double y, double z, double radius);
  Stem(const Stem& stem);
  ~Stem();
  void changeCoords(const Eigen::Matrix4d& transMatrix);
  // Getters and setters
  const Eigen::Vector4d& getCoords() const;
  void setCoords(const Eigen::Vector4d &coords);
  double getRadius() const;
  void setRadius(const double& radius);
  bool operator==(const Stem& stem) const;

 private:
  /*
  The 4th element is always 1. This is for faster coordinates
  change using 4x4 matrices.
  */
  Eigen::Vector4d coords;
  double radius;
};

} // namespace tlr
#endif
