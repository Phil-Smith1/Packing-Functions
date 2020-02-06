#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;

P2 Rotation_About_Pt ( P2 const& centre, P2 const& p, double angle )
{
    V2 v = centre - ORIGIN;
    
    P2 input = p - v;
    
    double x = cos( angle ) * input.x() - sin( angle ) * input.y();
    double y = sin( angle ) * input.x() + cos( angle ) * input.y();
    
    P2 output( x, y );
    
    output = output + v;
    
    return output;
}

