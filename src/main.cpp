/***************************************************************************
 *   Copyright (C) 2017 by Jean-François Tremblay                          *
 *   jftremblay255@gmail.com                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <stdio.h>
#include <time.h>
#include "Registration.h"
#include <omp.h>

/*
main.cpp

Va etre utilise pour tester les fonctionnalite donc va changer tres souvents
des tests plus rigoureux, unitaires, vont etre implmente tres bientot.
*/
int main(int argc, char *argv[])
{
  if (argc != 6 || argc != 7)
  {
    std::cout << "Bad number of arguments" << std::endl
              << "Usage: ./TLR path_source path_target"
              << "minimum_radius radius_error_tol RANSAC_error_tol"
              << std::endl;
    return 1;
  }

  //omp_set_num_threads(4);

  double minDiam = std::stod(argv[3]);
  double diamErrorTol = std::stod(argv[4]);
  double distTol = std::stod(argv[5]);
  std::string pathSource = argv[1];
  std::string pathTarget = argv[2];

  tlr::StemMap mapTarget;
  mapTarget.loadStemMapFile(pathTarget, minDiam);

  tlr::StemMap mapSource;
  mapSource.loadStemMapFile(pathSource, minDiam);

  std::cout << "Registration of "
            << pathSource << " to " << pathTarget << std::endl;

  time_t start = time(NULL);
  tlr::Registration reg = tlr::Registration(mapTarget, mapSource, diamErrorTol, distTol, argc == 7);
  reg.computeBestTransform();
  reg.printFinalReport();
  time_t end = time(NULL);
  long time = end - start;

  std::cout << "End of registration. Total time (s) : " << time << std::endl;

  return 0;
}
