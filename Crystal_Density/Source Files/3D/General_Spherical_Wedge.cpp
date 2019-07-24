#include "Spherical_Wedge.h"
#include "Regularised_Spherical_Wedge.h"

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

double General_Spherical_Wedge ( Sphere const& s, Pl3 const& p1, Pl3 const& p2 )
{
    L3 l = Line_Of_Intersection_Of_Two_Planes( p1, p2 );
    
    double d = sqrt( squared_distance( s.c, l ) );
    
    if (d < tiny_num) return Spherical_Wedge( s, p1, p2 );
    
    else
    {
        P3 pt1, pt2;
        
        pt1 = l.point( 1 );
        pt2 = l.point( 2 );
        
        Pl3 p3( pt1, pt2, s.c );
        
        double volume1 = Regularised_Spherical_Wedge ( s, p1, p3 );
        double volume2 = Regularised_Spherical_Wedge ( s, p2, p3 );
        
        return volume1 + volume2;
    }
}
