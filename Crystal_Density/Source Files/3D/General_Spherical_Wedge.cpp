#include "Spherical_Wedge.h"
#include "Regularised_Spherical_Wedge.h"
#include "Intersection_Of_Line_And_Plane.h"

double General_Spherical_Wedge ( Sphere const& s, Pl3 const& p1, Pl3 const& p2 )
{
    L3 l = Line_Of_Intersection_Of_Two_Planes( p1, p2 );
    
    double d = sqrt( squared_distance( s.c, l ) );
    
    if (d >= s.r) return 0;
    
    if (d < tiny_num) return Spherical_Wedge( s, p1, p2 );
    
    else if (squared_distance( s.c, p1 ) < tiny_num) return Regularised_Spherical_Wedge( s, p2, p1 );
    else if (squared_distance( s.c, p2 ) < tiny_num) return Regularised_Spherical_Wedge( s, p1, p2 );
    
    P3 pt1, pt2;
    
    pt1 = l.point( 1 );
    pt2 = l.point( 2 );
    
    Pl3 p3( pt1, pt2, s.c );
    
    if (p1.oriented_side( s.c ) != p2.oriented_side( s.c ))
    {
        P3 pt3 = p1.point();
        
        if (squared_distance( pt3, l ) < tiny_num) pt3 += p1.base1();
        if (squared_distance( pt3, l ) < tiny_num) pt3 += p1.base2();
        
        if (p2.oriented_side( pt3 ) != p3.oriented_side( pt3 )) p3 = p3.opposite();
        
        V3 v = pt1 - s.c;
        P3 pt4 = pt1 + v;
        
        L3 l2( pt4, p3.orthogonal_vector() );
        
        P3 i1, i2;
        Pl3 p4, p5;
        
        if (Intersection_Of_Line_And_Plane( p1, l2, i1 ) && Intersection_Of_Line_And_Plane( p2, l2, i2 ))
        {
            if (p3.oriented_side( i1 ) == p3.oriented_side( i2 ))
            {
                if (Norm( i1, pt4 ) > Norm( i2, pt4 ))
                {
                    p4 = p1;
                    p5 = p2.opposite();
                }
                
                else
                {
                    p4 = p2;
                    p5 = p1.opposite();
                }
            }
            
            else
            {
                if (p3.oriented_side( i1 ) == ON_POSITIVE_SIDE)
                {
                    p4 = p2;
                    p5 = p1.opposite();
                }
                    
                else
                {
                    p4 = p1;
                    p5 = p2.opposite();
                }
            }
        }
        
        else if (Intersection_Of_Line_And_Plane( p1, l2, i1 ))
        {
            if (p3.oriented_side( i1 ) == ON_POSITIVE_SIDE)
            {
                p4 = p2;
                p5 = p1.opposite();
            }
                
            else
            {
                p4 = p1;
                p5 = p2.opposite();
            }
        }
        
        else
        {
            Intersection_Of_Line_And_Plane( p2, l2, i2 );
            
            if (p3.oriented_side( i2 ) == ON_POSITIVE_SIDE)
            {
                p4 = p1;
                p5 = p2.opposite();
            }
            
            else
            {
                p4 = p2;
                p5 = p1.opposite();
            }
        }
        
        double volume1 = Regularised_Spherical_Wedge( s, p4, p3 );
        double volume2 = Regularised_Spherical_Wedge( s, p5, p3 );
        
        return volume1 - volume2;
    }
    
    else if (p1.oriented_side( s.c ) == ON_POSITIVE_SIDE)
    {
        P3 pt3 = p1.point();
        
        if (squared_distance( pt3, l ) < tiny_num) pt3 += p1.base1();
        if (squared_distance( pt3, l ) < tiny_num) pt3 += p1.base2();
        
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
        if (squared_distance( pt3, l ) < tiny_num) pt3 += p1.base2();
        
        if (p2.oriented_side( pt3 ) != p3.oriented_side( pt3 )) p3 = p3.opposite();
        
        double volume1 = Regularised_Spherical_Wedge ( s, p1, p3 );
        
        p3 = p3.opposite();
        
        double volume2 = Regularised_Spherical_Wedge ( s, p2, p3 );
        
        return volume1 + volume2;
    }
}
