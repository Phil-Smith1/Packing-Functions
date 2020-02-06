#include "Angle_Between_Vectors3D.h"

typedef K::Line_3 L3;

#ifndef Pi
#define Pi
const double PI = 3.14159265359;
#endif

bool Parallel_Lines ( L3 const& l1, L3 const& l2 )
{
    P3 pt1 = P3( 0, 0, 0 ) + l1.to_vector();
    P3 pt2 = P3( 0, 0, 0 ) + l2.to_vector();
    
    double angle = Angle_Between_Vectors( pt1, pt2 );
    
    if (angle < tiny_num || abs( angle - PI ) < tiny_num) return true;
    
    else return false;
}
