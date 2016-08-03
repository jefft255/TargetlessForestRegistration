#include "PairOfStemGroups.h"
#include <Eigen/Eigenvalues>
#include <math.h>
#include <algorithm>

// Helper functions declarations
void getCentroid(std::vector<Stem*> group, Eigen::Vector3d& centroid);
bool sortStemPointers(Stem* stem1, Stem* stem2);

PairOfStemGroups::PairOfStemGroups(StemTriplet& targetTriplet, StemTriplet& sourceTriplet) :
	eigenValuesSource(std::get<1>(sourceTriplet)),
	eigenValuesTarget(std::get<1>(targetTriplet)),
	targetGroup(std::get<0>(targetTriplet)),
	sourceGroup(std::get<0>(sourceTriplet)),
	bestTransform(Eigen::Matrix4d::Identity())
{
	this->sortStems();
	this->updateRadiusSimilarity();
}


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
	this->sortStems();
	this->updateRadiusSimilarity();
}

// Return the previously computed best transform
const Eigen::Matrix4d PairOfStemGroups::getBestTransform()
{
	return this->bestTransform;
}

// Compute the best transform between the pair and returns it
const Eigen::Matrix4d PairOfStemGroups::computeBestTransform()
{
	// Compute the centroids
	Eigen::Vector3d pbar;
	getCentroid(this->sourceGroup, pbar);
	std::cout << "pbar: " << std::endl << pbar << std::endl;
	Eigen::Vector3d qbar;
	getCentroid(this->targetGroup, qbar);
	std::cout << "qbar: " << std::endl << qbar << std::endl;

	// Center the points and generate the covariance matrix
	Eigen::MatrixXd X;
	Eigen::MatrixXd Yt;
	X.resize(3, this->sourceGroup.size());
	Yt.resize(this->sourceGroup.size(), 3);

	for (unsigned int i = 0; i < this->sourceGroup.size(); ++i)
	{
		X(0, i) = this->sourceGroup[i]->getCoords()(0) - pbar(0);
		X(1, i) = this->sourceGroup[i]->getCoords()(0) - pbar(1);
		X(2, i) = this->sourceGroup[i]->getCoords()(0) - pbar(2);
		Yt(i, 0) = this->targetGroup[i]->getCoords()(0) - qbar(0);
		Yt(i, 1) = this->targetGroup[i]->getCoords()(0) - qbar(1);
		Yt(i, 2) = this->targetGroup[i]->getCoords()(0) - qbar(2);
	}

	std::cout << "X: " << std::endl << X << std::endl;
	std::cout << "Yt: " << std::endl << Yt << std::endl;

	Eigen::MatrixXd S = X*Yt;
	std::cout << "S: " << std::endl << S << std::endl;
	Eigen::JacobiSVD<Eigen::MatrixXd> svd(S, Eigen::ComputeFullU | Eigen::ComputeFullV);
	Eigen::MatrixXd matricePourTrouverR = Eigen::MatrixXd::Identity(this->sourceGroup.size(), this->sourceGroup.size());
	Eigen::MatrixXd matricePourSavoirDet = svd.matrixV()*svd.matrixU().transpose();
	std::cout << "matricePourSavoirDet: " << std::endl << matricePourSavoirDet << std::endl;
	matricePourTrouverR(this->sourceGroup.size()-1, this->sourceGroup.size()-1) = matricePourSavoirDet.determinant();
	std::cout << "matricePourTrouverR: " << std::endl << matricePourTrouverR << std::endl;
	Eigen::Matrix3d R = svd.matrixV()*matricePourTrouverR*svd.matrixU().transpose();
	Eigen::Vector3d t = qbar - R*pbar;

	// Generate the 4x4 transform matrix from the result
	Eigen::Matrix4d optimalTransform;
	this->bestTransform << R(0, 0), R(0, 1), R(0, 2), t(0),
						R(1, 0), R(1, 1), R(1, 2), t(1),
						R(2, 0), R(2, 1), R(2, 2), t(2),
						0,       0,       0,       1;
	return this->bestTransform;
}

// Sort the stem groups by the DBH
void PairOfStemGroups::sortStems()
{
	std::sort(this->sourceGroup.begin(), this->sourceGroup.end(), sortStemPointers);
	std::sort(this->targetGroup.begin(), this->targetGroup.end(), sortStemPointers);
}

void PairOfStemGroups::updateRadiusSimilarity()
{
	std::vector<double> result;
	for (unsigned int i = 0; i < this->sourceGroup.size(); ++i)
	{
		result.push_back(abs(
			(this->sourceGroup[i]->getRadius() - this->targetGroup[i]->getRadius()) /
			((this->sourceGroup[i]->getRadius() + this->targetGroup[i]->getRadius()) / 2)
			));
	}
	this->radiusSimilarity = result;
}

const std::vector<double>& PairOfStemGroups::getRadiusSimilarity() const
{
	return this->radiusSimilarity;
}

bool operator<(PairOfStemGroups& l, PairOfStemGroups& r)
{
	return l.getLikelihood() < r.getLikelihood();
}

// Compute the "average" point of a group of stems. Used in the least square solving.
void getCentroid(std::vector<Stem*> group, Eigen::Vector3d& centroid)
{
	centroid << 0, 0, 0;
	for (auto it = group.begin(); it != group.end(); it++)
	{
		centroid(0) += (*it)->getCoords()(0);
		centroid(1) += (*it)->getCoords()(1);
		centroid(2) += (*it)->getCoords()(2);
	}
	centroid = (float(1) / float(group.size()))*centroid;
}

/* This is an auxilliary function to sort the vector of stems using
   the DBH */
bool sortStemPointers(Stem* stem1, Stem* stem2)
{
	return stem1->getRadius() < stem2->getRadius();
}