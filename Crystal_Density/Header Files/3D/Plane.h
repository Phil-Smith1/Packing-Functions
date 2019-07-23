#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 P3;
typedef K::Vector_3 V3;

class Plane
{
    public:
    
    double a, b, c, d;
    P3 p1, p2, p3;
    V3 v1, v2, n;
    
    Plane ( P3 const& pt1, P3 const& pt2, P3 const& pt3 );
    
    Plane();
    ~Plane();
};
