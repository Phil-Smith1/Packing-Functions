#pragma once

#include "Sphere.h"
#include "Angle_Between_Vectors3D.h"

typedef K::Plane_3 Pl3;

double Spherical_Wedge ( Sphere const& s, Pl3 const& p1, Pl3 const& p2 );
