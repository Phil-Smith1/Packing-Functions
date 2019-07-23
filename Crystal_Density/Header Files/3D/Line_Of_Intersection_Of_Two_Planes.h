#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 P3;
typedef K::Vector_3 V3;
typedef K::Line_3 L3;
typedef K::Plane_3 Pl3;

L3 Line_Of_Intersection_Of_Two_Planes ( Pl3 const& p1, Pl3 const& p2 );
