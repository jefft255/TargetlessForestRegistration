#pragma once

#include <Eigen/Dense>
#include <Eigen/StdVector>
#include "Stem.h"
#include <string>
#include <iostream>

class StemMap
{
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	StemMap();
	StemMap(const StemMap& stemMap);
	~StemMap();
	void applyTransMatrix(const Eigen::Matrix4d& transMatrix);
	void addStem(Stem& stem);
	void restoreOriginalCoords();
	std::string strStemMap() const;
	bool operator==(const StemMap& stemMap) const;
	std::vector<Stem, Eigen::aligned_allocator<Eigen::Vector4f>>& getStems();

private:
	/*
	The aligned_allocator is necessary because of a "bug" in C++98.
	maybe compiling with C++14 or C++17 will fix it. Source :
	https://eigen.tuxfamily.org/dox/group__TopicStlContainers.html
	*/
	std::vector<Stem,Eigen::aligned_allocator<Eigen::Vector4f>> stems;
	Eigen::Matrix4d transMatrix; // Transformation matrix since the original
};

