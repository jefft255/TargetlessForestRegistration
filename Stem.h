#pragma once

#include <vector>
#include <Eigen/Dense>

class Stem
{
public:
	Stem();
	Stem(double x, double y, double z, double radius);
	Stem(const Stem &stem);
	~Stem();
	void changeCoords(Eigen::Matrix4d const &transMatrix);
	// Getters and setters
	Eigen::Vector4d getCoords();
	void setCoords(const Eigen::Vector4d &coords);
	double getRadius();
	void setRadius(const double &radius);

private:
	/*
	The 4th element is always 1. This is for faster coordinates
	change using 4x4 matrices.
	*/
	Eigen::Vector4d coords;
	double radius;
};

