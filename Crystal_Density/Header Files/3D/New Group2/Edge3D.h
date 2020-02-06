#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 P3;
typedef K::Line_3 L3;

class Edge3D
{
    public:
    
    int index, intersection_type;
    P3 startpt, endpt, i1, i2;
    L3 line;
    
    Edge3D ( L3 const& l, P3 const& s, P3 const& e, int i );
    
    Edge3D();
    ~Edge3D();
};
