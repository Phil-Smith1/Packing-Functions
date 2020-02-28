#pragma once

#include "B_Poly.h"
#include "B_Poly_I.h"

using namespace std;

typedef Exact_Kernel::Point_3 P3_E;
typedef K::Point_3 P3;

double Max_Radius_Of_Space ( P3_E const& centre, vector<B_Poly>& polys );

double Max_Radius_Of_Space ( P3 const& centre, vector<B_Poly_I>& polys );
