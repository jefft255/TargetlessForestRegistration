#include "StemMap.h"

#include <stdio.h>

/*
main.cpp

Va etre utilise pour tester les fonctionnalite donc va changer tres souvents
des tests plus rigoureux, unitaires, vont etre implmente tres bientot.
*/
int main()
{
	StemMap map1;
	Stem souche1(11.2, 21, 43.32, 10);
	Stem souche2(141.2, 71, 41.32, 15);
	Stem souche3(-431.2, 21, 43.32, 13);

	map1.addStem(souche1);
	map1.addStem(souche2);
	map1.addStem(souche3);

	// Testing the output
	std::string strMap1 = map1.strStemMap();
	std::cout << strMap1;

	// Now we can test the rotation
	// Identity matrix should give us the same stem map
	StemMap map2 = StemMap(map1);
	Eigen::Matrix4d transMatrixTest;
	transMatrixTest << 1, 0, 0, 0,
					   0, 1, 0, 0,
					   0, 0, 1, 0,
					   0, 0, 0, 1;

	map2.applyTransMatrix(transMatrixTest);
	// Lets see...
	if (map1 == map2)
		std::cout << "Identity rotation succes" << std::endl;
	else
		std::cout << "Identity rotation failure" << std::endl;

	transMatrixTest << 1, 43, 2, 11.4321234,
					   0, 1, 4, -10,
					   43, 0, 1, 2,
					   0, 0, 0, 1;

	map2.applyTransMatrix(transMatrixTest);
	std::cout << map2.strStemMap();
	std::cout << "Restoring the original coordinates..." << std::endl;
	map2.restoreOriginalCoords();
	std::cout << map2.strStemMap();
	if (map1 == map2)
		std::cout << "Success" << std::endl;
	else
		std::cout << "Failure. Needs inspection, can be due to very small FP error." << std::endl;


	int a;
	std::cin >> a;
	return 0;
}