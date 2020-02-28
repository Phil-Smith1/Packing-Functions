#pragma once

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/convex_hull_3.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_exact_constructions_kernel Exact_Kernel;
typedef Exact_predicates_inexact_constructions_kernel K;
typedef Polyhedron_3<Exact_Kernel> Polyhedron;

typedef Polyhedron_3<K> Polyhedron_I;

typedef Exact_Kernel::Point_3 P3_E;
typedef Exact_Kernel::Vector_3 V3_E;

typedef K::Point_3 P3;
typedef K::Vector_3 V3;

void Generate_Cube ( double cube_size, P3_E const& centre, Polyhedron& cube );

void Generate_Cube_I ( double cube_size, P3 const& centre, Polyhedron_I& cube );
