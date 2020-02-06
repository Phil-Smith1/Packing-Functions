#pragma once

#include "General_Spherical_Wedge.h"
#include "Intersection_Pts_Of_Plane_And_Circle.h"

double No_Intersection_Of_Plane_And_Circle ( Sphere const& s, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3, Circle3D const& c1, Circle3D const& c2 );

double General_Spherical_Cone_Exterior_Vertex ( Sphere const& s, P3 const& vertex, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3 );
