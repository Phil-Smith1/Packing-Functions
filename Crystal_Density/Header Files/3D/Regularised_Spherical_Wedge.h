#pragma once

#include "Line_Of_Intersection_Of_Two_Planes.h"
#include "Angle_Between_Vectors3D.h"
#include "Spherical_Cap.h"

#include <CGAL/squared_distance_3.h>

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

double Regularised_Spherical_Wedge ( Sphere const& s, Pl3 const& p1, Pl3 const& p2 );
