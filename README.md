# TargetlessForestRegistration
Targetless TLS data registration for forest scans. Algorithm by David Kelbe et al., implementation by me.

## Introduction
This program registers one forest scan to another using a "stem map" representing the position and DBH of each tree in a scan.
It does so using an algorithm designed by David Kelbe et al., which I've augmented mainly by reimplementing it in C++ and changing a few
detail to try to get execution time under control.

## Stem maps
A stem map file is a text file contain information for each tree detected in a scan. Each line is : x_position y_position z_position DBH.
I found that [Computree](http://computree.onf.fr/?lang=en) was the best tool for generating a stem map from a scan, but feel free to generate it using other software.

## Compilation
### Dependencies
You need to add the include path of the most recent version of [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page). Your compiler must support OpenMP 4+ and C++14. This means no compiling on windows for now, altough new version of VC++ will eventually fix that in the near future. It could also probably work using MinGW, but it has not been tested.

## Usage
### Parameters
### Shell script and registration reports
### Result reliability

## TODOs
