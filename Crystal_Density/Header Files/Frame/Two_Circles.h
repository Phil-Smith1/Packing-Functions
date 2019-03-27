#pragma once

#include <vector>

#include "Two_Circle_Intersection_Area.h"

using namespace std;

class Two_Circles
{
    public:
    
    bool non_trivial_intersection;
    double intersection_area;
    P2 i1, i2;
    vector<Circle> c;
    
    Two_Circles ( Circle const& c1, Circle const& c2 );
    
    Two_Circles();
    ~Two_Circles();
};
