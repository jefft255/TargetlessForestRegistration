#ifndef TLR_STEM_H_
#define TLR_STEM_H_

#include <vector>
#include <Eigen/Dense>

namespace tlr
{

class Stem
{
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	Stem();
	Stem(double x, double y, double z, double radius);
	Stem(const Stem& stem);
	~Stem();
	void changeCoords(const Eigen::Matrix4d& transMatrix);
	// Getters and setters
	const Eigen::Vector4d& getCoords() const;
	void setCoords(const Eigen::Vector4d &coords);
	double getRadius() const;
	void setRadius(const double& radius);
	bool operator==(const Stem& stem) const;

private:
	/*
	The 4th element is always 1. This is for faster coordinates
	change using 4x4 matrices.
	*/
	Eigen::Vector4d coords;
	double radius;
};

} // namespace tlr
#endif