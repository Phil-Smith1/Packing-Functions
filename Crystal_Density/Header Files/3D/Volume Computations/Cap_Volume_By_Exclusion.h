#pragma once

#include "Sphere_Four_Plane_Intersection_Volume.h"

using namespace std;

double Cap_Volume_By_Exclusion ( vector<pair<Pl3, int>>& planes, Pl3 const& p, Sphere const& s );
