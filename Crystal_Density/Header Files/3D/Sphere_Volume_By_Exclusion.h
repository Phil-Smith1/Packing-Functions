#pragma once

#include "General_Spherical_Cone.h"

using namespace std;

double Sphere_Volume_By_Exclusion ( vector<pair<Pl3, int>>const& planes, Sphere const& s );

double Sphere_Volume_By_Exclusion_2 ( vector<pair<Pl3, int>>const& planes, Sphere const& s );
