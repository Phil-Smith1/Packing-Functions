#pragma once

#include "B_Poly.h"

#include <CGAL/Triangulation_3.h>

using namespace std;

typedef Tetrahedron_3<Exact_Kernel> Tetrahedron;
typedef Triangulation_3<Exact_Kernel> Triangulation;

typedef Exact_Kernel::Point_3 P3_E;

typedef Polyhedron::Vertex_iterator vertex_iterator;

typedef Triangulation::Finite_cells_iterator cells_iterator;

void Triangulate_Zones ( vector<B_Poly>& polys, int zone_limit, vector<vector<Tetrahedron>>& zones_of_tetras );
