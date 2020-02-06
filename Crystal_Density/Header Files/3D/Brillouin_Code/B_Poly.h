#pragma once

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>

using namespace CGAL;

typedef Exact_predicates_exact_constructions_kernel Exact_Kernel;
typedef Polyhedron_3<Exact_Kernel> Polyhedron;

class B_Poly
{
    public:
    
    bool check;
    int zone;
    double dist;
    Polyhedron poly;
    
    B_Poly ( Polyhedron const& p, double d, int z );
    
    B_Poly();
    ~B_Poly();
};
