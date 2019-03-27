#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;

#ifndef Pi
#define Pi
const double PI = 3.14159265359;
#endif

class Circle
{
    public:
    
    int index;
    double r, area;
    P2 c;
    
    Circle ( P2 const& centre, double radius );
    
    Circle();
    ~Circle();
};
