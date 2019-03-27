#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;

#ifndef Pi
#define Pi
const double PI = 3.14159265359;
#endif

bool Deformation ( int deformation_type, int iterations, int counter, P2& p2, P2& p3, P2 const& p4, vector<P2>& interior_pts );
