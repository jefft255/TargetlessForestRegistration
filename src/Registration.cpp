#include "Registration.h"
#include <atomic>

namespace tlr
{

// Getting ready for RANSAC, no heavy computation yet.
Registration::Registration(const StemMap& target, const StemMap& source,
                           double diamErrorTol, double RANSACtol) :
  diamErrorTol(diamErrorTol),
  RANSACtol(RANSACtol),
  target(target),
  source(source)
{
  std::cout << "Number of unmatched stems: " << this->removeLonelyStems() << std::endl;
  std::cout << "Number of stems in source: " << this->source.getStems().size() << std::endl;
  std::cout << "Number of stems in target: " << this->target.getStems().size() << std::endl;
  this->generateTriplets(this->source, this->threePermSource);
  this->generateTriplets(this->target, this->threePermTarget);
  this->generatePairs();
  std::cout << this->pairsOfStemTriplets.size() << " transforms to compute. " << std::endl;
}

void
Registration::computeBestTransform()
{
  if (this->pairsOfStemTriplets.size() == 0) return; // Nothing to compute

  // Compute all possible transforms in parallel
  #pragma omp parallel for
  for (size_t i = 0; i < this->pairsOfStemTriplets.size(); ++i)
  {
    // Compute a first transform then see if other stems matches
    this->pairsOfStemTriplets[i].computeBestTransform();
    this->RANSACtransform(this->pairsOfStemTriplets[i]);
  }

  std::sort(this->pairsOfStemTriplets.begin(), this->pairsOfStemTriplets.end());
}

void
Registration::printFinalReport()
{
  // Check if there was any transformation done first
  if (this->pairsOfStemTriplets.size() == 0)
  {
    std::cout << "Failure. No matching pair was found." << std::endl;
    return;
  }


  PairOfStemGroups bestPair = *this->pairsOfStemTriplets.begin();
  std::cout << "====== Best transform ======" << std::endl
            << bestPair.getBestTransform() << std::endl
            << "MSE : " << bestPair.getMeanSquareError() << std::endl
            << "Number of used stems : " << bestPair.getTargetGroup().size() << std::endl
            << "------ Stems used for registration -----" << std::endl;
  for (size_t i = 0; i < bestPair.getTargetGroup().size(); ++i)
  {
    std::cout << "---- Stem " << i + 1 << " ----" << std::endl
              << "-- Target --" << std::endl << "Coordinates:" << std::endl
              << bestPair.getTargetGroup()[i]->getCoords() << std::endl
              << "Radius: " << bestPair.getTargetGroup()[i]->getRadius() << std::endl
              << "-- Source --" << std::endl << "Coordinates:" << std::endl
              << bestPair.getSourceGroup()[i]->getCoords() << std::endl
              << "Radius: " << bestPair.getSourceGroup()[i]->getRadius() << std::endl;
  }
}

void
Registration::RANSACtransform(PairOfStemGroups& pair)
{
  StemMap sourceCopy;

  sourceCopy = StemMap(this->source);
  sourceCopy.applyTransMatrix(pair.getBestTransform());

  for(size_t i = 0; i < sourceCopy.getStems().size(); ++i)
  {
    for(size_t j = 0; j < this->target.getStems().size(); ++j)
    {
      if (!this->stemDistanceGreaterThanTol(sourceCopy.getStems()[i],
                                            this->target.getStems()[j])
          &&
          !this->stemAlreadyInGroup(this->target.getStems()[j],
                                    pair.getTargetGroup())
          &&
          !this->relDiamErrorGreaterThanTol(this->target.getStems()[j],
                                            this->source.getStems()[i]))
      {
        // We add the stem who was not transformed
        pair.addFittingStem(&this->source.getStems()[i],
                            &this->target.getStems()[j]);
      }
    }
  }
  pair.computeBestTransform();
}

/* Return true if a stem is already present in a group.
   This is useful for the RANSAC part.
*/
bool
Registration::stemAlreadyInGroup(const Stem& stem,
                                 const StemGroup group) const
{
  for (const auto it : group)
  {
    if (stem.getCoords() == it->getCoords()) return true;
  }
  return false;
}

bool
Registration::stemDistanceGreaterThanTol(const Stem& stem1, const Stem& stem2) const
{
  Eigen::Vector4d stemError = stem1.getCoords()
                              - stem2.getCoords();
  return stemError.norm() > this->RANSACtol;
}

// Return true if the relative error between two stems is greater than diamErrorTol
bool
Registration::relDiamErrorGreaterThanTol(const Stem& stem1, const Stem& stem2) const
{
  return fabs(stem1.getRadius() - stem2.getRadius()) /
         ((stem1.getRadius() + stem2.getRadius())/2) > this->diamErrorTol;
}

Registration::~Registration()
{
}

// Needs refactoring. It does work though
unsigned int
Registration::removeLonelyStems()
{
  bool toBeRemoved;
  std::vector<size_t> indicesToRemove = {};
  unsigned int nRemoved = 0;
  size_t i = 0;
  for (auto& itSource : this->source.getStems())
  {
    toBeRemoved = true;
    for (auto& itTarget : this->target.getStems())
    {
      if (!this->relDiamErrorGreaterThanTol(
              itTarget, itSource
         ))
      {
        toBeRemoved = false;
      }
    }
    if (toBeRemoved)
    {
      indicesToRemove.push_back(i);
      ++nRemoved;
    }
    ++i;
  }
  // If any stem has to be removed
  if (indicesToRemove.size() > 0)
  {
    // Remove the stems backward so the indices are not all shuffled up
    for (size_t j = indicesToRemove.size() - 1; j > 0; --j)
    {
      this->source.removeStem(indicesToRemove[j]);
    }
   }
  // Repeat for the target map
  indicesToRemove = {};
  i = 0;
  for (auto& itTarget : this->target.getStems())
  {
    toBeRemoved = true;
    for (auto& itSource : this->source.getStems())
    {
      if (!this->relDiamErrorGreaterThanTol(
              itSource, itTarget
         ))
      {
        toBeRemoved = false;
      }
    }
    if (toBeRemoved)
    {
      indicesToRemove.push_back(i);
      ++nRemoved;
    }
    ++i;
  }
  if (indicesToRemove.size() > 0)
  {
    // Remove the stems backward so the indices are not all shuffled up
    for (size_t j = indicesToRemove.size() - 1; j > 0; --j)
    {
      this->target.removeStem(indicesToRemove[j]);
    }
  }
  return nRemoved;
}

long long
Factorial(int n)
{
  long long result = 1;
  while (n>1) {
    result *= n--;
  }
  return result;
}

// Generates all 3 from K combinations
std::vector<std::set<int>>
ThreeCombK(const unsigned int k)
{
  std::vector<std::set<int>> result;
  std::set<int> comb;

  for (unsigned int i = 1; i < k - 1; ++i)
  {
    for (unsigned int j = i; j < k; ++j)
    {
      for (unsigned int s = j; s <= k; ++s)
      {
        comb.insert(i);
        comb.insert(j);
        comb.insert(s);
        // Only add combinaison if the numbers are unique
        if (comb.size() == 3)
          result.push_back(comb);
        comb = std::set<int>();
      }
    }
  }

  return result;
}

// This is useful for computing the covariance matrix.
double
GetMeanOfVector(const Eigen::Vector4d& coords)
{
  return (coords[0] + coords[1] + coords[2]) / 3;
}

/* This function populate the stem triplets from both the target scan and the source scan.
   We use the nPerm function to determine all the possible combinations. */
void
Registration::generateTriplets(StemMap& stemMap, std::vector<StemGroup>& threePerm)
{
  std::vector<std::set<int>> threePermN = ThreeCombK(stemMap.getStems().size());
  StemGroup tempTriplet = StemGroup();

  for (auto it : threePermN)
  {
    for (auto jt : it)
      tempTriplet.push_back(&stemMap.getStems()[jt - 1]);
    threePerm.push_back(tempTriplet);
    tempTriplet = StemGroup();
  }
}

// Population the pairOfStemsTriplets attributes with all possible pairs. Cleanup is done later.
void
Registration::generatePairs()
{
  #pragma omp parallel for
  for (size_t i = 0; i < this->threePermSource.size(); ++i)
  {
    for (size_t j = 0; j < this->threePermTarget.size(); ++j)
    {
      PairOfStemGroups tempPair(this->threePermTarget[j],
                                this->threePermSource[i]);

      if (!this->diametersNotCorresponding(tempPair)
          && this->pairPositionsAreCorresponding(tempPair))
      {
        #pragma omp critical
        {
          this->pairsOfStemTriplets.push_back(tempPair);
        }
      }
    }
  }
}

// This removes of non-matching (diameter-wise) pair of triplets.
bool
Registration::diametersNotCorresponding(PairOfStemGroups& pair)
{
  for (size_t i = 0; i < pair.getSourceGroup().size(); ++i)
  {
    if (this->relDiamErrorGreaterThanTol(*pair.getSourceGroup()[i],
                                         *pair.getTargetGroup()[i]))
      return true;
  }
  return false;
}

/* This asserts wether the stems are positioned in the same way relative
   to each other in both group. How do we do that? We compare the
   triangle formed by the stems in both group. If a vertice's length
   is too different than the corresponding vertice in the other group then
   they don't match.
*/
bool
Registration::pairPositionsAreCorresponding(PairOfStemGroups& pair)
{
  const std::vector<double> verticeDiffs = pair.getVerticeDifference();
  for (double diff : verticeDiffs)
  {
    if (diff > 2*this->RANSACtol) return false;
  }
  return true;
}

} // namespace tlr
