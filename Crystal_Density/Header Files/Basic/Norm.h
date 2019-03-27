#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;
typedef K::Vector_2 V2;

double Norm ( P2 const& p );

double Norm ( P2 const& p1, P2 const& p2 );

double Norm ( V2 const& v );
