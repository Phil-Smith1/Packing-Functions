#pragma once

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_exact_constructions_kernel Exact_Kernel;
typedef Exact_predicates_inexact_constructions_kernel K;
typedef Polyhedron_3<Exact_Kernel> Polyhedron;
typedef Polyhedron_3<K> Polyhedron_I;

typedef Exact_Kernel::Point_3 P3_E;
typedef Exact_Kernel::Plane_3 Pl3_E;

typedef K::Point_3 P3;
typedef K::Plane_3 Pl3;

typedef Polyhedron::Vertex_iterator vertex_iterator;
typedef Polyhedron_I::Vertex_iterator vertex_iterator_i;

int Plane_Intersect_Polyhedron ( Polyhedron& cube, Pl3_E const& plane );

int Plane_Intersect_Polyhedron_I ( Polyhedron_I& cube, Pl3 const& plane );
