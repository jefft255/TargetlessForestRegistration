#pragma once

#include <Eigen/Dense>
#include "Stem.h"
#include <string>
#include <iostream>

class StemMap
{
public:
	StemMap();
	~StemMap();
	void applyTransMatrix(Eigen::Matrix4d const &transMatrix);
	void addStem(Stem &stem);
	void restoreOriginalCoords();
	std::string strStemMap();

private:
	std::vector<Stem> stems;
	Eigen::Matrix4d transMatrix; // Transformation matrix since the original
};

