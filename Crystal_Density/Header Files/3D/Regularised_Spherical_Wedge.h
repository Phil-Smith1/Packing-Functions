#include "Sphere.h"
#include "Line_Of_Intersection_Of_Two_Planes.h"
#include "Angle_Between_Vectors3D.h"

#include <CGAL/squared_distance_3.h>

double Regularised_Spherical_Wedge ( Sphere const& s, Pl3 const& p1, Pl3 const& p2 );
