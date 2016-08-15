#include "Registration.h"

#include <stdio.h>

/*
main.cpp

Va etre utilise pour tester les fonctionnalite donc va changer tres souvents
des tests plus rigoureux, unitaires, vont etre implmente tres bientot.
*/
int main()
{
	double minDiam;
	double diamErrorTol;
        std::cout << "Test alignement des scans a JFC" << std::endl;
        std::cout << "Entrez le diametre minimum a considerer : ";
        std::cin >> minDiam;
	std::cout << "Entrez la tolerance sur l'erreur du DBH : ";
        std::cin >> diamErrorTol;
	
	Eigen::Matrix4d rotStemMap2;
	rotStemMap2 << 0.224, -0.974, 0, -3.6436,
                        0.974, 0.2264, 0, 11.25,
                        0, 0, 1, -1.378,
                        0, 0, 0, 1;


	Eigen::Matrix4d rotStemMap3;
        rotStemMap3 << 0.224, -0.974, 0, -3.6436,
                        0.974, 0.2264, 0, 11.25,
                        0, 0, 1, -1.378,
                        0, 0, 0, 1;

	Eigen::Matrix4d rotStemMap4;
        rotStemMap4 << 0.224, -0.974, 0, -3.6426,
                        0.974, 0.2264, 0, 11.25,
                        0, 0, 1, -1.378,
                        0, 0, 0, 1;


	StemMap map1;
	map1.loadStemMapFile("/home/jeff/TLR/1-1stemMapPartie2.csv", minDiam);

	StemMap map2;
	map2.loadStemMapFile("/home/jeff/TLR/1-2stemMapPartie2.csv", minDiam);
	map2.applyTransMatrix(rotStemMap2);

	StemMap map3;
        map3.loadStemMapFile("/home/jeff/TLR/1-3stemMapPartie2.csv", minDiam);
	map3.applyTransMatrix(rotStemMap3);

	StemMap map4;
        map4.loadStemMapFile("/home/jeff/TLR/1-4stemMapPartie2.csv", minDiam);
	map4.applyTransMatrix(rotStemMap4);

	std::cout << "-------------------------------------DEBUT 1-2 vers 1-1" << std::endl;
	
	clock_t start = clock();
	Registration reg = Registration(map1, map2, diamErrorTol);
	reg.computeBestTransform();
	clock_t end = clock();
	double time = (double) (end-start) / CLOCKS_PER_SEC;
	std::cout << "FIN 1-2 vers 1-1. Temps total (s) : " << time << std::endl;
	
	std::cout << "-------------------------------------DEBUT 1-3 vers 1-1" << std::endl;

	start = clock();
	reg = Registration(map1, map3, diamErrorTol);
        reg.computeBestTransform();
        end = clock();
        time = (double) (end-start) / CLOCKS_PER_SEC;
        std::cout << "FIN 1-3 vers 1-1. Temps total (s) : " << time << std::endl;


	std::cout << "-------------------------------------DEBUT 1-4 vers 1-1" << std::endl;

	start = clock();
	reg = Registration(map1, map4, diamErrorTol);
        reg.computeBestTransform();
        end = clock();
        time = (double) (end-start) / CLOCKS_PER_SEC;
        std::cout << "FIN 1-4 vers 1-1. Temps total (s) : " << time << std::endl;

	int a;
	std::cin >> a;
	return 0;
}
