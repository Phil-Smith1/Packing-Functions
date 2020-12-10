#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef Polyhedron_3<K> Polyhedron_I;

class B_Poly_I
{
    public:
    
    bool check;
    int zone;
    double dist;
    Polyhedron_I poly;
    
    B_Poly_I ( Polyhedron_I const& p, double d, int z );
    
    B_Poly_I();
    ~B_Poly_I();
};
