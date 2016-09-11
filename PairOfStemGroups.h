#ifndef TLR_PAIROFSTEMGROUPS_H_
#define TLR_PAIROFSTEMGROUPS_H_

#include "StemMap.h"

namespace tlr 
{

typedef std::pair<std::vector<const Stem*>, std::vector<std::complex<double>>> StemTriplet;

class PairOfStemGroups
{
 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW // Fixes wierd memory crashes
  PairOfStemGroups(StemTriplet& targetTriplet, StemTriplet& sourceTriplet);
  ~PairOfStemGroups();
  double getLikelihood() const;
  const std::vector<double>& getRadiusSimilarity() const;
  const std::vector<double> getVerticeDifference() const;
  Eigen::Matrix4d computeBestTransform();
  Eigen::Matrix4d getBestTransform() const;
  const std::vector<const Stem*> getTargetGroup() const;
  const std::vector<const Stem*> getSourceGroup() const;
  void addFittingStem(const Stem* sourceStem, const Stem* targetStem);
  // To sort by likelihood, and if the transform is computed sort by MSE
  friend bool operator<(PairOfStemGroups& l, PairOfStemGroups& r);
  double getMeanSquareError() const;

 private:
  void sortStems();
  void updateRadiusSimilarity();
  double updateMeanSquareError();
  /* They are only triplet at first. We'll add other stems that fit the model later.
  These are a copy of the vector created by the Registration class. We need to copy them
  because differents pair will generate different models, which means in some case we we'll have
  to add a stem to a group, some case not. When we add a stem to a group we don't want to add it in every pair!

  TODO rendre ca plus clair
  */
  std::vector<const Stem*> targetGroup;
  std::vector<const Stem*> sourceGroup;
  double likelihood;
  double meanSquareError;
  /* They should be real but I put a complex type this way the
  compiler won't complain */
  std::vector<std::complex<double>> eigenValuesTarget;
  std::vector<std::complex<double>> eigenValuesSource;
  std::vector<double> radiusSimilarity;
  /* This is sadly necessary because of alignement issues in Eigen. Declaring
  the transorm matrix as dynamically sized instead of 4x4 fixes bugs with matrix
  operations in MSVSC++ 2013 */
  Eigen::MatrixXd bestTransform;
  bool transformComputed;
};

} // namespace tlr
#endif
