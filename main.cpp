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

	tlr::StemMap mapTarget;
	mapTarget.loadStemMapFile(pathTarget, minDiam);

	tlr::StemMap mapSource;
	mapSource.loadStemMapFile(pathSource, minDiam);

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
