#pragma once

#include "B_Poly.h"
#include "B_Poly_I.h"

#include <CGAL/Triangulation_3.h>

using namespace std;

typedef Tetrahedron_3<Exact_Kernel> Tetrahedron;
typedef Triangulation_3<Exact_Kernel> Triangulation;

typedef Tetrahedron_3<K> Tetrahedron_I;
typedef Triangulation_3<K> Triangulation_I;

typedef Exact_Kernel::Point_3 P3_E;
typedef K::Point_3 P3;

typedef Polyhedron::Vertex_iterator vertex_iterator;
typedef Polyhedron_I::Vertex_iterator vertex_iterator_i;

typedef Triangulation::Finite_cells_iterator cells_iterator;
typedef Triangulation_I::Finite_cells_iterator cells_iterator_i;

void Triangulate_Zones ( vector<B_Poly>& polys, int zone_limit, vector<vector<Tetrahedron>>& zones_of_tetras );

void Triangulate_Zones_I ( vector<B_Poly_I>& polys, int zone_limit, vector<vector<Tetrahedron_I>>& zones_of_tetras );
