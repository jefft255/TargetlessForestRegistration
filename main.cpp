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
	map1.loadStemMapFile("/home/jeff/TLR/1-1stemMapPartie2.csv");

	StemMap map2;
	map2.loadStemMapFile("/home/jeff/TLR/1-2stemMapPartie2.csv");

	StemMap map3;
        map3.loadStemMapFile("/home/jeff/TLR/1-3stemMapPartie2.csv");

	StemMap map4;
        map4.loadStemMapFile("/home/jeff/TLR/1-4stemMapPartie2.csv");



	std::cout << "Test alignement des scans a JFC" << std::endl;
	
	std::cout << "-------------------------------------DEBUT 1-2 vers 1-1" << std::endl;
	
	clock_t start = clock();
	Registration reg = Registration(map1, map2);
	reg.computeBestTransform();
	clock_t end = clock();
	double time = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
	std::cout << "FIN 1-2 vers 1-1. Temps total (ms) : " << time << std::endl;
	
	std::cout << "-------------------------------------DEBUT 1-3 vers 1-1" << std::endl;

	start = clock();
	reg = Registration(map1, map3);
        reg.computeBestTransform();
        end = clock();
        time = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
        std::cout << "FIN 1-3 vers 1-1. Temps total (ms) : " << time << std::endl;


	std::cout << "-------------------------------------DEBUT 1-4 vers 1-1" << std::endl;

	start = clock();
	reg = Registration(map1, map4);
        reg.computeBestTransform();
        end = clock();
        time = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
        std::cout << "FIN 1-4 vers 1-1. Temps total (ms) : " << time << std::endl;

	int a;
	std::cin >> a;
	return 0;
}
