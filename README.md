# TargetlessForestRegistration
Targetless TLS data registration for forest scans described in [Tremblay & Béland](https://www.sciencedirect.com/science/article/pii/S0924271618302892). Algorithm inspired by [David Kelbe et al.](http://ieeexplore.ieee.org/document/7446318/?reload=true&arnumber=7446318), parallel implementation and improvements by me.

## Introduction
This program registers one forest scan to another using a "stem map" representing the position and DBH of each tree in a scan.
A stem map file is a text file contain information for each tree detected in a scan. Each line is : x_position y_position z_position DBH.
I found that [Computree](http://computree.onf.fr/?lang=en) was the best tool for generating a stem map from a scan, but feel free to generate it using other software.

## Compilation
### Dependencies
You need to add the include path of the most recent version of [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page). Your compiler must support OpenMP 4+ and C++11. Windows compilation is untested but should work with the latest versions of VC++. It could also probably work using MinGW, but it has not been tested.

## Usage
### Parameters
- Path to source stem map file
- Path to target stem map file
- Minimum diameter: diameter under which stem can be ignored. Can help speed up the registration if there are a lot of trees detected in your scan. Make sure enough tree above that diameter are in both scan for the registration to work (you need at least three trees that are common to both scans for it to work)
- Max diameter error: maximum relative difference between to DBH. If the error is above that the trees are considered as different trees. If below that the algorithm considers them as potential matches.
- Max positional error: maximum error of the tree position for them to match (norm of the difference of the position vectors)
