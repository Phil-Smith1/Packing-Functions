#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 P3;

#ifndef Pi
#define Pi
const double PI = 3.14159265359;
#endif

class Sphere
{
    public:
    
    int index;
    double r, vol;
    P3 c;
    
    Sphere ( P3 const& centre, double radius );
    
    Sphere();
    ~Sphere();
};
