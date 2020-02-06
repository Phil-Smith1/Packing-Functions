#pragma once

#include "Three_Circles.h"

class Four_Circles
{
    public:
    
    bool non_trivial_intersection = false;
    bool non_inclusion_intersection = false;
    double intersection_area;
    P2 i1, i2, i3, i4;
    vector<int> arc_order;
    vector<Circle> c;
    vector<Two_Circles> tc;
    vector<Three_Circles> thc;
    
    Four_Circles ( Three_Circles const& thc1, Three_Circles const& thc2, Three_Circles const& thc3, Three_Circles const& thc4 );
    
    double Four_Circle_Intersection_Area ();
    
    Four_Circles();
    ~Four_Circles();
};
