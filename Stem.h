#pragma once

#include <vector>
#include <Eigen/Dense>

class Stem
{
public:
	Stem();
	~Stem();
	void changeCoords(Eigen::Matrix4f transMatrix);

private:
	/*
	The 4th element is always 1. This is for faster coordinates
	change using 4x4 matrices.
	*/
	Eigen::Vector4f coords;
	float radius;
};

