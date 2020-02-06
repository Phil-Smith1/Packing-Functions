#pragma once

#include "Triangle_Area3D.h"
#include "B_Poly.h"

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_3.h>
#include <CGAL/Triangulation_3.h>

using namespace std;

typedef K::Plane_3 Pl3;

typedef Tetrahedron_3<Exact_Kernel> Tetrahedron;
typedef Triangulation_3<Exact_Kernel> Triangulation;

typedef Exact_Kernel::Point_3 P3_E;
typedef Exact_Kernel::Vector_3 V3_E;
typedef Exact_Kernel::Segment_3 S3_E;
typedef Exact_Kernel::Plane_3 Pl3_E;
typedef Exact_Kernel::Intersect_3 I3;

typedef Polyhedron::Halfedge_iterator halfedge_iterator;
typedef Polyhedron::Vertex_iterator vertex_iterator;

typedef Triangulation::Finite_cells_iterator cells_iterator;

void Produce_Cube ( double cube_size, P3_E const& centre, Polyhedron& cube );

void Initialise_Cubes ( double cube_size, int num_cubes, P3_E const& centre, vector<Polyhedron>& cubes );

int Compute_Zone( P3_E const& centre, vector<Pl3_E>const& planes, Polyhedron& poly );

double Max_Distance_To_Polygon ( P3_E const& centre, Polyhedron& poly );

void Removing_Distant_Polygons ( P3_E const& centre, vector<Pl3_E>const& planes, double plane_distance, vector<B_Poly>& polys, vector<B_Poly>& final_polys, int zone_limit );

double Max_Radius_Of_Space ( P3_E const& centre, vector<pair<double, Polyhedron>>& polys );

void Dividing_Space ( P3_E const& centre, multimap<double, P3_E>const& pts, vector<B_Poly>& final_polys, int zone_limit );

void Compute_Brillouin_Zones ( int perim, int zone_limit, P3_E const& centre, vector<vector<Tetrahedron>>& zones_of_tetras );

void Extract_Tetra_Cells ( vector<vector<Tetrahedron>>const& zones_of_tetras, int zone_limit, vector<vector<vector<Pl3>>>& tetra_cells );
