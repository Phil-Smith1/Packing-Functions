#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 P3;
typedef K::Vector_3 V3;
typedef K::Line_3 L3;
typedef K::Plane_3 Pl3;

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

bool Intersection_Of_Line_And_Plane ( Pl3 const& p, L3 const& l, P3& pt );
