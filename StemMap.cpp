#include "StemMap.h"
#include <fstream>
#include <sstream>

void split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

StemMap::StemMap()
{
	this->stems = std::vector<Stem, Eigen::aligned_allocator<Eigen::Vector4f>>();
	this->transMatrix = Eigen::Matrix4d::Identity(); // No transform applied yet
}

StemMap::StemMap(const StemMap &stemMap)
{
	this->stems = stemMap.stems;
	this->transMatrix = stemMap.transMatrix;
}

StemMap::~StemMap()
{
}

void
StemMap::applyTransMatrix(Eigen::Matrix4d const &transMatrix)
{
	// Could gain significant speedup from parralelization
	for (auto it : this->stems)
	{
		it.changeCoords(transMatrix);
	}

	this->transMatrix *= transMatrix; // We store the transformation
}

void
StemMap::restoreOriginalCoords()
{
	// Simply apply the inverse transform!!
	this->applyTransMatrix(this->transMatrix.inverse());
	this->transMatrix = Eigen::Matrix4d::Identity();
}

void
StemMap::addStem(Stem &stem)
{
	this->stems.push_back(stem);
}

std::string
StemMap::strStemMap() const
{
	std::stringstream output;
	for (auto it : this->stems)
	{
		output << "Coords : " << it.getCoords()[0] << 
			" " << it.getCoords()[1] << " " << it.getCoords()[2];
		output << ", Radius : " << it.getRadius() << std::endl;
	}

	return output.str();
}

bool
StemMap::operator==(const StemMap &stemMap) const
{
	return stemMap.stems == this->stems && stemMap.transMatrix == this->transMatrix;
}

std::vector<Stem, Eigen::aligned_allocator<Eigen::Vector4f>>&
StemMap::getStems()
{
	return this->stems;
}

void
StemMap::loadStemMapFile(std::string path)
{
	std::ifstream stemMapFile(path);
	std::string line;
	Stem tempStem;
	int i = 0;

	while (std::getline(stemMapFile, line))
	{
		if (i > 0) { // Skip header
			std::vector<std::string> lineData = split(line, ';');
			tempStem = Stem(
				std::stod(lineData[2]),
				std::stod(lineData[3]),
				std::stod(lineData[4]),
				std::stod(lineData[5])
				);
			this->addStem(tempStem);
		}
		++i;
	}
}

/*
Stack overflow code for splitting string
Used in StemMap::loadStemMapFile
*/
void split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
}


std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}
// End of stackoverflow code