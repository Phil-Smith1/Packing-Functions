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
    
    else if (squared_distance( s.c, p1 ) < tiny_num) return Regularised_Spherical_Wedge( s, p2, p1 );
    else if (squared_distance( s.c, p2 ) < tiny_num) return Regularised_Spherical_Wedge( s, p1, p2 );
    
    P3 pt1, pt2;
    
    pt1 = l.point( 1 );
    pt2 = l.point( 2 );
    
    Pl3 p3( pt1, pt2, s.c );
    
    if (p1.oriented_side( s.c ) != p2.oriented_side( s.c ))
    {
        double volume1 = Regularised_Spherical_Wedge( s, p1, p3 );
        double volume2 = Regularised_Spherical_Wedge( s, p2, p3 );
        
        double volume = abs( volume1 - volume2 );
        
        return volume;
    }
    
    else if (p1.oriented_side( s.c ) == ON_POSITIVE_SIDE)
    {
        P3 pt3 = p1.point();
        
        if (squared_distance( pt3, l ) < tiny_num) pt3 += p1.base1();
        else if (squared_distance( pt3, l ) < tiny_num) pt3 += p1.base2();
        
        if (p2.oriented_side( pt3 ) != p3.oriented_side( pt3 )) p3 = p3.opposite();
        
        Pl3 p4 = p1.opposite();
        
        double volume1 = Regularised_Spherical_Wedge ( s, p4, p3 );
        
        p3 = p3.opposite();
        p4 = p2.opposite();
        
        double volume2 = Regularised_Spherical_Wedge ( s, p4, p3 );
        
        return s.vol - volume1 - volume2;
    }
    
    else
    {
        P3 pt3 = p1.point();
        
        if (squared_distance( pt3, l ) < tiny_num) pt3 += p1.base1();
        else if (squared_distance( pt3, l ) < tiny_num) pt3 += p1.base2();
        
        if (p2.oriented_side( pt3 ) != p3.oriented_side( pt3 )) p3 = p3.opposite();
        
        double volume1 = Regularised_Spherical_Wedge ( s, p1, p3 );
        
        p3 = p3.opposite();
        
        double volume2 = Regularised_Spherical_Wedge ( s, p2, p3 );
        
        return volume1 + volume2;
    }
}
