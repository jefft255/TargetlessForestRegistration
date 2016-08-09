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
	map1.loadStemMapFile("C:/Users/Jean-Francois/OneDrive/Stage_labo_foret_numerique/Donnees_JFC/scan_parcelle/1-1stemMapParite2.csv");

	StemMap map2;
	map2.loadStemMapFile("C:/Users/Jean-Francois/OneDrive/Stage_labo_foret_numerique/Donnees_JFC/scan_parcelle/1-2stemMapPartie2.csv");


	std::cout << "Test initialisation classe Registration" << std::endl;

	Registration reg = Registration(map1, map2);

	reg.computeBestTransform();

	int a;
	std::cin >> a;
	return 0;
}