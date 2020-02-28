#pragma once

#include "B_Poly.h"
#include "B_Poly_I.h"

using namespace std;

typedef Exact_Kernel::Point_3 P3_E;
typedef Exact_Kernel::Plane_3 Pl3_E;

typedef K::Point_3 P3;
typedef K::Plane_3 Pl3;

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

void Removing_Polyhedrons ( P3_E const& centre, vector<Pl3_E>const& planes, double plane_distance, vector<B_Poly>& polys, vector<B_Poly>& final_polys, int zone_limit );

void Removing_Polyhedrons_I ( P3 const& centre, vector<Pl3>const& planes, double plane_distance, vector<B_Poly_I>& polys, vector<B_Poly_I>& final_polys, int zone_limit );
