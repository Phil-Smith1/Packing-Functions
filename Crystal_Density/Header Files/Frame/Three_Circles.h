#pragma once

#include "Two_Circles.h"
#include "Triangle_Area.h"
#include "Segment_Area.h"

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

class Three_Circles
{
    public:
    
    bool non_trivial_intersection = false;
    bool non_inclusion_intersection = false;
    double intersection_area;
    P2 i1, i2, i3;
    vector<Circle> c;
    vector<Two_Circles> tc;
    
    Three_Circles ( Two_Circles const& tc1, Two_Circles const& tc2, Two_Circles const& tc3 );
    
    double Three_Circle_Intersection_Area ();
    
    Three_Circles();
    ~Three_Circles();
};
