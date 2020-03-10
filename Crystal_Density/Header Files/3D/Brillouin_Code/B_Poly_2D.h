#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef Polygon_2<K> Polygon;

class B_Poly_2D
{
    public:
    
    bool check;
    int zone;
    double dist;
    Polygon poly;
    
    B_Poly_2D ( Polygon const& p, double d, int z );
    
    B_Poly_2D();
    ~B_Poly_2D();
};
