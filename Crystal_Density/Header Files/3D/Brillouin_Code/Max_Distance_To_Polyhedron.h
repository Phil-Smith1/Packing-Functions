#pragma once

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>

using namespace CGAL;

typedef Exact_predicates_exact_constructions_kernel Exact_Kernel;
typedef Polyhedron_3<Exact_Kernel> Polyhedron;

typedef Exact_Kernel::Point_3 P3_E;

typedef Polyhedron::Vertex_iterator vertex_iterator;

double Max_Distance_To_Polyhedron ( P3_E const& centre, Polyhedron& poly );
