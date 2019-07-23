#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;
typedef K::Point_3 P3;
typedef K::Vector_3 V3;

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

class Circle3D
{
public:
    
    int index;
    double r, area;
    P3 c;
    V3 v1, v2;
    
    Circle3D ( P3 const& centre, double radius, V3 const& vec1, V3 const& vec2 );
    
    Circle3D();
    ~Circle3D();
};
