#pragma once

#include "Triangle_Area3D.h"
#include "B_Poly.h"
#include "Extract_Tetra_Cells.h"
#include "Triangulate_Zones.h"
#include "Divide_Polyhedron.h"

#include <thread>

typedef Exact_Kernel::Vector_3 V3_E;

void Produce_Cube ( double cube_size, P3_E const& centre, Polyhedron& cube );

void Initialise_Cubes ( double cube_size, int num_cubes, P3_E const& centre, vector<Polyhedron>& cubes );

int Compute_Zone( P3_E const& centre, vector<Pl3_E>const& planes, Polyhedron& poly );

void Dividing_Space ( P3_E const& centre, multimap<double, P3_E>const& pts, vector<B_Poly>& final_polys, int zone_limit );

void Compute_Brillouin_Zones ( multimap<double, P3_E> const& pts, int zone_limit, P3_E const& centre, vector<vector<Tetrahedron>>& zones_of_tetras );


