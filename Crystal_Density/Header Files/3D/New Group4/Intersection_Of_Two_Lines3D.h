#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 P3;
typedef K::Vector_3 V3;
typedef K::Line_3 L3;

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

P3 Intersection_Of_Two_Lines3D ( L3 const& l1, L3 const& l2 );
