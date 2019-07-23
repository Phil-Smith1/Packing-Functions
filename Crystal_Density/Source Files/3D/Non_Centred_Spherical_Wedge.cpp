#include "Line_Of_Intersection_Of_Two_Planes.h"
#include "Spherical_Cap.h"

double Non_Centred_Spherical_Wedge ( Sphere const& s, Pl3 const& p1, Pl3 const& p2 )
{
    L3 l = Line_Of_Intersection_Of_Two_Planes( p1, p2 );
    
    P3 pt1, pt2;
    
    pt1 = l.point( 1 );
    pt2 = l.point( 2 );
    
    Pl3 p3( pt1, pt2, s.c );
    
    return 0;
}
