#include "PairOfStemGroups.h"
#include <Eigen/Eigenvalues>
#include <math.h>

namespace tlr
{

// Helper functions declarations
void GetCentroid(const std::vector<const Stem*> group,
                 Eigen::Vector3d& centroid);
bool SortStemPointers(const Stem* stem1, const Stem* stem2);

PairOfStemGroups::PairOfStemGroups(StemTriplet& targetTriplet,
                                   StemTriplet& sourceTriplet) :
  eigenValuesSource(std::get<1>(sourceTriplet)),
  eigenValuesTarget(std::get<1>(targetTriplet)),
  targetGroup(std::get<0>(targetTriplet)),
  sourceGroup(std::get<0>(sourceTriplet)),
  bestTransform(Eigen::Matrix4d::Identity()),
  transformComputed(false)
{
  this->sortStems();
  this->updateRadiusSimilarity();
}


PairOfStemGroups::~PairOfStemGroups()
{
}

double
PairOfStemGroups::getLikelihood() const
{
  // TODO. Kelbe ne considere pas les valeurs complexes????? Aussi peut etre que
  // utiliser la troisieme valeur propre pourrait etre utile. A voir.
  return pow(this->eigenValuesTarget[0].real() -
         this->eigenValuesSource[0].real(),2)  +
         pow(this->eigenValuesTarget[1].real() -
         this->eigenValuesSource[1].real(),2);
}

/*
  After running the registration using the least square, the registration class
  will determine if another stem is common to the two maps. If so we'll add it
  in each stem group and rerun the registration for better accuracy.
*/
void
PairOfStemGroups::addFittingStem(const Stem* sourceStem, const Stem* targetStem)
{
  // The new stem is both in the target scan and the source scan.
  this->sourceGroup.push_back(sourceStem);
  this->targetGroup.push_back(targetStem);
  // Update attributes
  // this->sortStems();
  this->updateRadiusSimilarity();
}

// Return the previously computed best transform
Eigen::Matrix4d
PairOfStemGroups::getBestTransform() const
{
  return this->bestTransform;
}

// Compute the best transform between the pair and returns it
Eigen::Matrix4d
PairOfStemGroups::computeBestTransform()
{
  // Declarations
  Eigen::Vector3d pbar;
  Eigen::Vector3d qbar;
  Eigen::MatrixXd X;
  Eigen::MatrixXd Yt;
  Eigen::MatrixXd S;
  Eigen::MatrixXd matricePourTrouverR;
  Eigen::MatrixXd matricePourSavoirDet;
  Eigen::Matrix3d R;
  Eigen::Vector3d t;

  // Compute the centroids
  GetCentroid(this->targetGroup, qbar);
  GetCentroid(this->sourceGroup, pbar);

  // Center the points and generate the covariance matrix
  X.resize(3, this->sourceGroup.size());
  Yt.resize(this->sourceGroup.size(), 3);

  for (unsigned int i = 0; i < this->sourceGroup.size(); ++i)
  {
    X(0, i)  = this->sourceGroup[i]->getCoords()(0) - pbar(0);
    X(1, i)  = this->sourceGroup[i]->getCoords()(1) - pbar(1);
    X(2, i)  = this->sourceGroup[i]->getCoords()(2) - pbar(2);
    Yt(i, 0) = this->targetGroup[i]->getCoords()(0) - qbar(0);
    Yt(i, 1) = this->targetGroup[i]->getCoords()(1) - qbar(1);
    Yt(i, 2) = this->targetGroup[i]->getCoords()(2) - qbar(2);
  }

  S = X*Yt;
  Eigen::JacobiSVD<Eigen::MatrixXd>
  svd(S, Eigen::ComputeFullU | Eigen::ComputeFullV);
  matricePourTrouverR = Eigen::MatrixXd::Identity(3, 3);
  matricePourSavoirDet = svd.matrixV()*svd.matrixU().transpose();
  matricePourTrouverR(2, 2) = matricePourSavoirDet.determinant();
  R = svd.matrixV()*matricePourTrouverR*svd.matrixU().transpose();
  t = qbar - R*pbar;

  // Generate the 4x4 transform matrix from the result
  this->bestTransform << R(0, 0), R(0, 1), R(0, 2), t(0),
                         R(1, 0), R(1, 1), R(1, 2), t(1),
                         R(2, 0), R(2, 1), R(2, 2), t(2),
                         0,       0,       0,       1;
  this->transformComputed = true;
  this->updateMeanSquareError();
  return this->bestTransform;
}

// Sort the stem groups by the DBH
void
PairOfStemGroups::sortStems()
{
  std::sort(this->sourceGroup.begin(), this->sourceGroup.end(), SortStemPointers);
  std::sort(this->targetGroup.begin(), this->targetGroup.end(), SortStemPointers);
}

// Updates the relative error of diameter between corresponding stems
void
PairOfStemGroups::updateRadiusSimilarity()
{
  std::vector<double> result;
  for (unsigned int i = 0; i < this->sourceGroup.size(); ++i)
  {
    result.push_back(fabs(
      this->sourceGroup[i]->getRadius() - this->targetGroup[i]->getRadius())
      /((this->sourceGroup[i]->getRadius() + this->targetGroup[i]->getRadius())/2));
  }
  this->radiusSimilarity = result;
}

// The registration algorithm will use this to determine if the pair matches or not.
const std::vector<double>&
PairOfStemGroups::getRadiusSimilarity() const
{
  return this->radiusSimilarity;
}

const std::vector<const Stem*>
PairOfStemGroups::getTargetGroup() const
{
  return this->targetGroup;
}

const std::vector<const Stem*>
PairOfStemGroups::getSourceGroup() const
{
  return this->sourceGroup;
}

double
PairOfStemGroups::updateMeanSquareError()
{
  double MSE = 0;
  Eigen::Vector4d stemError;
  for (unsigned int i = 0; i < this->targetGroup.size(); ++i)
  {
    stemError = this->targetGroup[i]->getCoords()
                - this->bestTransform*(this->sourceGroup[i]->getCoords());
    MSE += pow(stemError.norm(), 2);
  }

  this->meanSquareError = MSE;
}

double
PairOfStemGroups::getMeanSquareError() const
{
  return this->meanSquareError;
}

/*
  This return a vector of length 3. Each element contains the
  difference between the length of corresponding vertice in each
  stem group. Only considers the first three stems in the group.
*/
const std::vector<double>
PairOfStemGroups::getVerticeDifference() const
{
  std::vector<double> result = {};
  Eigen::Vector4d sourceVector;
  Eigen::Vector4d targetVector;

  for (size_t i = 0; i < this->targetGroup.size(); ++i)
  {
    // Use the next stem, or the first on if we're at the last.
    size_t next = i == this->targetGroup.size()-1 ? 0 : i + 1;
    sourceVector = this->sourceGroup[i]->getCoords() - this->sourceGroup[next]->getCoords();
    targetVector = this->targetGroup[i]->getCoords() - this->targetGroup[next]->getCoords();
    result.push_back(fabs(sourceVector.norm() - targetVector.norm()));
  }

  return result;
}

/* We sort by the number of matching stem. If they are equal,
   then the pair with the lowest MSE comes first.
*/
bool
operator<(PairOfStemGroups& l, PairOfStemGroups& r)
{
  if (l.getSourceGroup().size() == r.getTargetGroup().size())
    return l.getMeanSquareError() < r.getMeanSquareError();
  else
    return l.getSourceGroup().size() > r.getSourceGroup().size();
}

// Compute the "average" point of a group of stems. Used in the least square solving.
void
GetCentroid(const std::vector<const Stem*> group, Eigen::Vector3d& centroid)
{
  centroid << 0, 0, 0;
  for (auto& it : group)
  {
    centroid(0) += it->getCoords()(0);
    centroid(1) += it->getCoords()(1);
    centroid(2) += it->getCoords()(2);
  }
  centroid = (float(1) / float(group.size()))*centroid;
}

/* This is an auxilliary function to sort the vector of stems using
   the DBH */
bool
SortStemPointers(const Stem* stem1, const Stem* stem2)
{
  return stem1->getRadius() < stem2->getRadius();
}

} // namespace tlr
