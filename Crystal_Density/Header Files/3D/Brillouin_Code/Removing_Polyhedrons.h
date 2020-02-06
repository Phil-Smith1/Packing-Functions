#pragma once

#include "B_Poly.h"

using namespace std;

typedef Exact_Kernel::Point_3 P3_E;
typedef Exact_Kernel::Plane_3 Pl3_E;

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

void Removing_Polyhedrons ( P3_E const& centre, vector<Pl3_E>const& planes, double plane_distance, vector<B_Poly>& polys, vector<B_Poly>& final_polys, int zone_limit );
