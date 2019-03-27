#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;
typedef K::Line_2 L2;

bool Same_Side ( L2 const& l, P2 const& p1, P2 const& p2 );
