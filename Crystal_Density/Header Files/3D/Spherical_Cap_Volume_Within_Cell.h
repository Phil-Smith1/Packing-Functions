#pragma once

#include "Cell3D.h"
#include "General_Spherical_Cone.h"
#include "Sphere_Four_Plane_Intersection_Volume.h"

double Spherical_Cap_Volume_Within_Cell ( Cell3D const& cell, Sphere const& s, Pl3 const& p );
