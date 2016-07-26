#pragma once

#include <Eigen/Dense>
#include "Stem.h"

class StemMap
{
public:
	StemMap();
	~StemMap();
	void applyTransMatrix(Eigen::Matrix4f const &transMatrix);
	void addStem(Stem &stem);
	void restoreOriginalCoords();

private:
	std::vector<Stem> stems;
	Eigen::Matrix4f transMatrix; // Transformation matrix since the original
};

