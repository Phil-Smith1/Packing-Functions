#pragma once

#include "Initialise_Cubes.h"
#include "Dividing_Space.h"
#include "Triangulate_Zones.h"

void Compute_Brillouin_Zones ( multimap<double, P3_E>const& pts, int zone_limit, P3_E const& centre, vector<vector<Tetrahedron>>& zones_of_tetras );

void Compute_Brillouin_Zones_I ( multimap<double, P3>const& pts, int zone_limit, P3 const& centre, vector<vector<Tetrahedron_I>>& zones_of_tetras, vector<double>& max_radii );

void Compute_Brillouin_Zones_IT ( multimap<double, P3>const pts, int zone_limit, P3 const centre, vector<vector<Tetrahedron_I>>& zones_of_tetras, vector<double>& max_radii );
