#include <stdio.h>
#include "Registration.h"

/*
main.cpp

Va etre utilise pour tester les fonctionnalite donc va changer tres souvents
des tests plus rigoureux, unitaires, vont etre implmente tres bientot.
*/
int main(int argc, char *argv[])
{
	if(argc != 6)
	{
		std::cout << "Bad number of arguments" << std::endl
			<< "Usage: ./TLR path_source path_target" 
			<< "minimum_radius radius_error_tol RANSAC_error_tol"
			<< std::endl;
		return 1;
	}

	double minDiam = std::stod(argv[3]);
	double diamErrorTol = std::stod(argv[4]);
	double distTol = std::stod(argv[5]);
	std::string pathSource = argv[1];
	std::string pathTarget = argv[2];

	// TO BE REMOVED
	Eigen::Matrix4d rotStemMap2;
	rotStemMap2 << 0.224, -0.974, 0, -3.6436,
                        0.974, 0.2264, 0, 11.25,
                        0, 0, 1, -1.378,
                        0, 0, 0, 1;


	Eigen::Matrix4d rotStemMap3;
        rotStemMap3 << 1.0338, 0.1516, -0.0002, 4.456,
                        0.1547, 1.0338, -0.0006, -5.3521,
                        0.0001, 0.0006, 1, -0.42211,
                        0, 0, 0, 1;

	Eigen::Matrix4d rotStemMap4;
        rotStemMap4 << 1, 0, -0.00031, -6.064,
                        0.00031, 0.00456, 1, 1.185,
                        0, -1, 0.00456, 4.396,
                        0, 0, 0, 1;
	// END TO BE REMOVED

	tlr::StemMap mapTarget;
	mapTarget.loadStemMapFile(pathTarget, minDiam);

	tlr::StemMap mapSource;
	mapSource.loadStemMapFile(pathSource, minDiam);
	mapSource.applyTransMatrix(rotStemMap2);

	std::cout << "Beginning registration of "
		<< pathSource << " to " << pathTarget << std::endl;
	
	time_t start = time(NULL);
	tlr::Registration reg = tlr::Registration(mapTarget, mapSource, diamErrorTol, distTol);
	reg.computeBestTransform();
	time_t end = time(NULL);
	long time = end - start;

	std::cout << "End of registration. Total time (s) : " << time << std::endl;

	return 0;
}
