#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;
typedef K::Line_2 L2;

class Edge
{
    public:
    
    int index, intersection_type;
    P2 startpt, endpt, i1, i2;
    L2 line;
    
    Edge ( L2 const& l, P2 const& s, P2 const& e, int i );
    
    Edge();
    ~Edge();
};
