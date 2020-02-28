#pragma once

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>

using namespace CGAL;

typedef Exact_predicates_exact_constructions_kernel Exact_Kernel;
typedef Exact_predicates_inexact_constructions_kernel K;
typedef Polyhedron_3<Exact_Kernel> Polyhedron;

typedef Polyhedron_3<K> Polyhedron_I;

typedef Exact_Kernel::Point_3 P3_E;
typedef K::Point_3 P3;

typedef Polyhedron::Vertex_iterator vertex_iterator;
typedef Polyhedron_I::Vertex_iterator vertex_iterator_i;

double Max_Distance_To_Polyhedron ( P3_E const& centre, Polyhedron& poly );

double Max_Distance_To_Polyhedron_I ( P3 const& centre, Polyhedron_I& poly );

double Min_Distance_To_Polyhedron_I ( P3 const& centre, Polyhedron_I& poly );
