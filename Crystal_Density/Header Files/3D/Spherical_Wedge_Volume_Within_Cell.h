#pragma once

#include "Cell3D.h"
#include "Sphere_Five_Plane_Intersection_Volume.h"

double Spherical_Wedge_Volume_Within_Cell ( Cell3D const& cell, Sphere const& s, Pl3 const& p1, Pl3 const& p2 );
