#pragma once

#include "Sphere_Ordering.h"
#include "Spherical_Cap.h"

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

double Volume_Of_Intersection_Of_Two_Spheres ( Sphere const& s1, Sphere const& s2 );
