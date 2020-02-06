#include "Two_Circles.h"

Two_Circles::Two_Circles ( Circle const& c1, Circle const& c2 )
{
    c.reserve( 2 );
    
    c.push_back( c1 );
    c.push_back( c2 );
    
    intersection_area = Two_Circle_Intersection_Area( c[0], c[1], i1, i2, non_trivial_intersection );
}

Two_Circles::Two_Circles(){}
Two_Circles::~Two_Circles(){}

