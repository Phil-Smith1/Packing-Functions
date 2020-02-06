#pragma once

#include "Sphere_Four_Plane_Intersection_Volume.h"

double Sphere_Five_Plane_Intersection_Volume ( Sphere const& s, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3, Pl3 const& p4, Pl3 const& p5, int iter );

double Parallel_Planes_Case5 ( Sphere const& s, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3, Pl3 const& p4, Pl3 const& p5 );

double Non_Parallel_Lines_Case5A ( Sphere const& s, L3 const& l1, L3 const& l2, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3, Pl3 const& p4, Pl3 const& p5, int iter );

double Non_Parallel_Lines_Case5B ( Sphere const& s, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3, Pl3 const& p4, Pl3 const& p5, int iter );
