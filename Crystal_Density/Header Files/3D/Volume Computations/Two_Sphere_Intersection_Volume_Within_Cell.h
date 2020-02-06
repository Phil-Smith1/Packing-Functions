#pragma once

#include "Sphere_Ordering.h"
#include "Sphere_Volume_Within_Cell.h"
#include "Spherical_Cap_Volume_Within_Cell.h"

double Two_Sphere_Intersection_Volume_Within_Cell ( Cell3D const& cell, Sphere const& s1, Sphere const& s2 );
