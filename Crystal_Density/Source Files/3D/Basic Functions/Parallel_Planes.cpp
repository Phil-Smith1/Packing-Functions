#include "Angle_Between_Vectors3D.h"

typedef K::Plane_3 Pl3;

#ifndef Pi
#define Pi
const double PI = 3.14159265359;
#endif

bool Parallel_Planes ( Pl3 const& p1, Pl3 const& p2 )
{
    P3 pt1 = P3( 0, 0, 0 ) + p1.orthogonal_vector();
    P3 pt2 = P3( 0, 0, 0 ) + p2.orthogonal_vector();
    
    double angle = Angle_Between_Vectors( pt1, pt2 );
    
    if (angle < tiny_num || abs( angle - PI ) < tiny_num) return true;
    
    else return false;
}
