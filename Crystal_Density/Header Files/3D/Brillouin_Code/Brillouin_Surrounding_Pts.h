#pragma once

#include "Frac_To_Cart_Coords.h"

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

using namespace std;

typedef Exact_predicates_exact_constructions_kernel Exact_Kernel;
typedef Exact_Kernel::Point_3 P3_E;
typedef Exact_Kernel::Vector_3 V3_E;

typedef K::Vector_3 V3;

void Brillouin_Surrounding_Pts ( int perim, double ** matrix, int index, vector<P3>const& pts, multimap<double, P3_E>& surrounding_pts );

void Brillouin_Surrounding_Pts_I ( int perim, double ** matrix, int index, vector<P3>const& pts, multimap<double, P3>& surrounding_pts );
