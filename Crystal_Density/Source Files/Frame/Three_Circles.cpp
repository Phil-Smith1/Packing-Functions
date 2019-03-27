#include "Three_Circles.h"

Three_Circles::Three_Circles ( Two_Circles const& tc1, Two_Circles const& tc2, Two_Circles const& tc3 )
{
    c.reserve( 3 );
    
    c.push_back( tc1.c[0] );
    c.push_back( tc1.c[1] );
    c.push_back( tc2.c[1] );
    
    tc.reserve( 3 );
    
    tc.push_back( tc3 );
    tc.push_back( tc2 );
    tc.push_back( tc1 );
    
    intersection_area = Three_Circle_Intersection_Area();
}

Three_Circles::Three_Circles(){}
Three_Circles::~Three_Circles(){}
