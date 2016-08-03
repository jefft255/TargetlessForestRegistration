#include "Registration.h"

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
	Stem souche4(-100, 23, 43.32, 13);
	Stem souche5(-150, 21, 43.32, 13);

	map1.addStem(souche1);
	map1.addStem(souche2);
	map1.addStem(souche3);
	map1.addStem(souche4);
	map1.addStem(souche5);

	StemMap map2;
	Stem souche6(21.2, 21, 43.32, 10);
	Stem souche7(151.2, 71, 41.32, 15);
	Stem souche8(-421.2, 21, 43.32, 13);
	Stem souche9(-90, 23, 43.32, 13);
	Stem souche10(-140, 21, 43.32, 13);

	map2.addStem(souche6);
	map2.addStem(souche7);
	map2.addStem(souche8);
	map2.addStem(souche9);
	map2.addStem(souche10);

	std::cout << "Test initialisation classe Registration" << std::endl;

	Registration reg = Registration(map1, map2);

	reg.computeBestTransform();

	int a;
	std::cin >> a;
	return 0;
}