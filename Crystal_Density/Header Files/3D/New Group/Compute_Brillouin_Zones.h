#pragma once

#include "Initialise_Cubes.h"
#include "Dividing_Space.h"
#include "Triangulate_Zones.h"

void Compute_Brillouin_Zones ( multimap<double, P3_E> const& pts, int zone_limit, P3_E const& centre, vector<vector<Tetrahedron>>& zones_of_tetras );


