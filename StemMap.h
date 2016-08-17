#ifndef TLR_STEMMAP_H_
#define TLR_STEMMAP_H_

#include <Eigen/StdVector>
#include <string>
#include <iostream>
#include "Stem.h"

namespace tlr
{

class StemMap
{
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	StemMap();
	StemMap(const StemMap& stemMap);
	~StemMap();

	void loadStemMapFile(std::string path, double minDiam);
	void applyTransMatrix(const Eigen::Matrix4d& transMatrix);
	void addStem(Stem& stem);
	void restoreOriginalCoords();
	std::string strStemMap() const;
	bool operator==(const StemMap& stemMap) const;
	const std::vector<Stem, Eigen::aligned_allocator<Eigen::Vector4f>>& getStems() const;
	void removeStem(size_t indice);

private:
	/*
	The aligned_allocator is necessary because of a "bug" in C++98.
	maybe compiling with C++14 or C++17 will fix it. Source :
	https://eigen.tuxfamily.org/dox/group__TopicStlContainers.html
	*/
	std::vector<Stem,Eigen::aligned_allocator<Eigen::Vector4f>> stems;
	Eigen::Matrix4d transMatrix; // Transformation matrix since the original
};

} // namespace tlr
#endif