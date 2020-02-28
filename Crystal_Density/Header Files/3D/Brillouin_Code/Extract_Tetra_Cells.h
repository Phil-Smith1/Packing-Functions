#pragma once

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_exact_constructions_kernel Exact_Kernel;
typedef Exact_predicates_inexact_constructions_kernel K;

typedef Tetrahedron_3<Exact_Kernel> Tetrahedron;
typedef Exact_Kernel::Point_3 P3_E;
typedef Exact_Kernel::Plane_3 Pl3_E;

typedef Tetrahedron_3<K> Tetrahedron_I;
typedef K::Point_3 P3;
typedef K::Line_3 L3;
typedef K::Plane_3 Pl3;

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

void Extract_Tetra_Cells ( vector<vector<Tetrahedron>>const& zones_of_tetras, int zone_limit, vector<vector<vector<Pl3>>>& tetra_cells );

void Extract_Tetra_Cells_I ( P3 const& centre, vector<vector<Tetrahedron_I>>const& zones_of_tetras, int zone_limit, vector<vector<vector<Pl3>>>& tetra_cells, vector<double>& cell_volume );
