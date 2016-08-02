#include "PairOfStemGroups.h"
#include <Eigen/Eigenvalues>
#include <math.h>

Eigen::Vector3d getCentroid(std::vector<Stem*> group);

PairOfStemGroups::PairOfStemGroups(StemTriplet& targetTriplet, StemTriplet& sourceTriplet,
	StemMap* targetMap, StemMap* sourceMap) :
	eigenValuesSource(std::get<1>(sourceTriplet)),
	eigenValuesTarget(std::get<1>(targetTriplet)),
	targetGroup(std::get<0>(targetTriplet)),
	sourceGroup(std::get<0>(sourceTriplet)),
	bestTransform(Eigen::Matrix4d::Identity())
{}


PairOfStemGroups::~PairOfStemGroups()
{
}

double PairOfStemGroups::getLikelihood() const 
{
	// TODO. Kelbe ne considere pas les valeurs complexes????? Aussi peut etre que
	// utiliser la troisieme valeur propre pourrait etre utile. A voir.
	return pow(this->eigenValuesTarget[0].real() - this->eigenValuesSource[0].real(),2) +
		pow(this->eigenValuesTarget[1].real() - this->eigenValuesSource[1].real(),2);
}

/*
	After running the registration using the least square, the registration class
	will determine if another stem is common to the two maps. If so we'll add it
	in each stem group and rerun the registration for better accuracy.
*/
void PairOfStemGroups::addFittingStem(Stem* sourceStem, Stem* targetStem)
{
	this->sourceGroup.push_back(sourceStem);
	this->targetGroup.push_back(targetStem);
}

const Eigen::Matrix4d PairOfStemGroups::getBestTransform()
{
	// Compute the centroids
	Eigen::Vector3d pbar = getCentroid(this->sourceGroup);
	Eigen::Vector3d qbar = getCentroid(this->targetGroup);

	// Center the points and generate the covariance matrix
	Eigen::MatrixXd X;
	Eigen::MatrixXd Yt;

	for (unsigned int i = 0; i < this->sourceGroup.size(); ++i)
	{
		X(0, i) = this->sourceGroup[i]->getCoords()(0) - pbar(0);
		X(1, i) = this->sourceGroup[i]->getCoords()(0) - pbar(1);
		X(2, i) = this->sourceGroup[i]->getCoords()(0) - pbar(2);
		Yt(i, 0) = this->targetGroup[i]->getCoords()(0) - qbar(0);
		Yt(i, 1) = this->targetGroup[i]->getCoords()(0) - qbar(1);
		Yt(i, 2) = this->targetGroup[i]->getCoords()(0) - qbar(2);
	}

	Eigen::MatrixXd S = X*Yt;
	Eigen::JacobiSVD<Eigen::MatrixXd> svd(S, Eigen::ComputeFullU | Eigen::ComputeFullV);
	Eigen::MatrixXd matricePourTrouverR = Eigen::MatrixXd::Identity(this->sourceGroup.size(), this->sourceGroup.size());
	Eigen::MatrixXd matricePourSavoirDet = svd.matrixV()*svd.matrixU().transpose();
	matricePourTrouverR(this->sourceGroup.size(), this->sourceGroup.size()) = matricePourSavoirDet.determinant();
	Eigen::Matrix3d R = svd.matrixV()*matricePourTrouverR*svd.matrixU().transpose();
	Eigen::Vector3d t = qbar - R*pbar;

	// Generate the 4x4 transform matrix from the result
	Eigen::Matrix4d optimalTransform;
	optimalTransform << R(0, 0), R(0, 1), R(0, 2), t(0),
						R(1, 0), R(1, 1), R(1, 2), t(1),
						R(2, 0), R(2, 1), R(2, 2), t(2),
						0,       0,       0,       1;
	return optimalTransform;
}

Eigen::Vector3d getCentroid(std::vector<Stem*> group)
{
	Eigen::Vector3d centroid;
	centroid << 0, 0, 0;
	for (auto it = group.begin(); it != group.end(); it++)
	{
		centroid(0) += (*it)->getCoords()(0);
		centroid(1) += (*it)->getCoords()(1);
		centroid(2) += (*it)->getCoords()(2);
	}
	centroid = (1 / group.size())*centroid;
	return centroid;
}