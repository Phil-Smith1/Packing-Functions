#pragma once

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_exact_constructions_kernel Exact_Kernel;
typedef Polyhedron_3<Exact_Kernel> Polyhedron;

typedef Exact_Kernel::Point_3 P3_E;
typedef Exact_Kernel::Vector_3 V3_E;
typedef Exact_Kernel::Segment_3 S3_E;
typedef Exact_Kernel::Plane_3 Pl3_E;
typedef Exact_Kernel::Intersect_3 I3;

typedef Polyhedron::Vertex_iterator vertex_iterator;

int Compute_Zone( P3_E const& centre, vector<Pl3_E>const& planes, Polyhedron& poly );
