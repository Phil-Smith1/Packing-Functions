#pragma once

#include "Initialise_Cubes.h"
#include "Divide_Polyhedron.h"

#include <thread>

void Dividing_Space ( P3_E const& centre, multimap<double, P3_E>const& pts, vector<B_Poly>& final_polys, int zone_limit );
