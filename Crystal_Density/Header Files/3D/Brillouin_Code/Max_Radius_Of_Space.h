#pragma once

#include "B_Poly.h"

using namespace std;

typedef Exact_Kernel::Point_3 P3_E;

double Max_Radius_Of_Space ( P3_E const& centre, vector<B_Poly>& polys );
