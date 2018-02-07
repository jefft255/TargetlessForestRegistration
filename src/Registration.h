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

#ifndef TLR_REGISTRATION_H_
#define TLR_REGISTRATION_H_
/** \file Registration.h
 *  \brief Header file for the Registration class.
 */

#include "PairOfStemGroups.h"
#include <numeric>
#include <list>
#include <unordered_set>
#include <set>

namespace tlr
{

typedef std::vector<const Stem*> StemGroup;
// Helper functions declaration
double GetMeanOfVector(const Eigen::Vector4d& coords);
std::vector<std::set<int>> NCombK(const int n, const int k);

/**
 * \brief Container class for the main algorithm
 *
 * This class encapsulate the targetless registration algorithm.
 * To use it, you initialize it and run computeBestTransform. You then
 * run printFinalReport to see the output. Private methode usually represent
 * substeps of the algorithm.
 */
class Registration
{
 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
  Registration(const StemMap& target, const StemMap& source,
               double diamErrorTol, double RANSACtol,
               bool kelbeRegistration);
  ~Registration();
  void computeBestTransform();
  void printFinalReport();

 private:
  unsigned int removeLonelyStems();
  void generateTriplets(StemMap& stemMap,
                        std::vector<StemGroup>& threePerm);
  void generatePairs();
  // This removes of non-matching pair of triplets.
  bool diametersNotCorresponding(PairOfStemGroups& pair);
  bool pairPositionsAreCorresponding(PairOfStemGroups& pair);
  void RANSACtransform(PairOfStemGroups& pair);
  bool stemDistanceGreaterThanTol(const Stem& stem1, const Stem& stem2) const;
  bool stemAlreadyInGroup(const Stem& stem,
                          const StemGroup group) const;
  bool relDiamErrorGreaterThanTol(const Stem& stem1, const Stem& stem2) const;

  double diamErrorTol;
  double RANSACtol;
  StemMap target;
  StemMap source;
  /* These two attributes contains, for each stem map, every way to choose
  three stem from the map. The complex vector contains the eigenvalues associated
  with the covariance matrix of the vector. It is here and not in the PairOfStemTriplets
  class because it would result in the eigenvalues being computed multiplet times
  for the same triplet which is computationally expensive. */
  std::vector<StemGroup> threePermTarget;
  std::vector<StemGroup> threePermSource;
  /* Contains all possible combinaison of 2 triplets of trees, one from the target
  and another from the source. Used list because we are going to be deleting
  a lot of pairs as we go along. */
  std::vector<PairOfStemGroups> pairsOfStemTriplets;
  bool kelbeRegistration;
};

} // namespace tlr
#endif
