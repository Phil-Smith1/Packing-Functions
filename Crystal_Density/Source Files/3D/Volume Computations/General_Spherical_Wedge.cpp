#include "Parallel_Planes.h"
#include "Spherical_Wedge.h"
#include "Regularised_Spherical_Wedge.h"
#include "Intersection_Of_Line_And_Plane.h"
#include "Intersection_Of_Plane_And_Circle.h"

double General_Spherical_Wedge ( Sphere const& s, Pl3 const& p1, Pl3 const& p2 )
{
    double plane_dist_1 = sqrt( squared_distance( s.c, p1 ) );
    
    if (plane_dist_1 > s.r - tiny_num)
    {
        if (p1.oriented_side( s.c ) == ON_NEGATIVE_SIDE) return 0;
        
        else return Spherical_Cap( s, p2 );
    }
    
    double plane_dist_2 = sqrt( squared_distance( s.c, p1 ) );
    
    if (plane_dist_2 > s.r - tiny_num)
    {
        if (p2.oriented_side( s.c ) == ON_NEGATIVE_SIDE) return 0;
        
        else return Spherical_Cap( s, p1 );
    }
    
    if (Parallel_Planes( p1, p2 ))
    {
        if (p2.oriented_side( p1.point() ) == ON_ORIENTED_BOUNDARY)
        {
            P3 pt = P3( 0, 0, 0 ) + p1.orthogonal_vector();
            
            if (p2.oriented_side( pt ) == ON_NEGATIVE_SIDE) return 0;
            
            else return Spherical_Cap( s, p1 );
        }
        
        else if (p2.oriented_side( p1.point() ) == ON_NEGATIVE_SIDE && p1.oriented_side( p2.point() ) == ON_NEGATIVE_SIDE) return 0;
        
        else if (p2.oriented_side( p1.point() ) == ON_NEGATIVE_SIDE) return Spherical_Cap( s, p2 );
        
        else if (p1.oriented_side( p2.point() ) == ON_NEGATIVE_SIDE) return Spherical_Cap( s, p1 );
        
        else return Spherical_Cap( s, p1 ) + Spherical_Cap( s, p2 ) - s.vol;
    }
    
    L3 l = Line_Of_Intersection_Of_Two_Planes( p1, p2 );
    
    double d = sqrt( squared_distance( s.c, l ) );
    
    if (d >= s.r - 1e-6)
    {
        double sp1 = Sphere_Plane_Distance( s, p1 ), sp2 = Sphere_Plane_Distance( s, p2 );
        
        if (sp1 <= -s.r || sp2 <= -s.r) return 0;
        
        else if (sp1 >= s.r && sp2 >= s.r) return s.vol;
        
        else if (sp1 >= s.r) return Spherical_Cap( s, p2 );
        
        else if (sp2 >= s.r) return Spherical_Cap( s, p1 );
        
        else
        {
            Circle3D c1 = Circular_Intersection_Of_Sphere_And_Plane( s, p1 );
            Circle3D c2 = Circular_Intersection_Of_Sphere_And_Plane( s, p2 );
            
            if (p2.oriented_side( c1.c ) == ON_NEGATIVE_SIDE && p1.oriented_side( c2.c ) == ON_NEGATIVE_SIDE) return 0;
            
            else if (p2.oriented_side( c1.c ) == ON_NEGATIVE_SIDE) return Spherical_Cap( s, p2 );
            
            else if (p1.oriented_side( c2.c ) == ON_NEGATIVE_SIDE) return Spherical_Cap( s, p1 );
            
            else return Spherical_Cap( s, p1 ) + Spherical_Cap( s, p2 ) - s.vol;
        }
    }
    
    if (d < tiny_num) return Spherical_Wedge( s, p1, p2 );
    
    else if (squared_distance( s.c, p1 ) < tiny_num)
    {
        if (p2.oriented_side( s.c ) == ON_POSITIVE_SIDE) return 0.5 * s.vol - Regularised_Spherical_Wedge( s, p2.opposite(), p1 );
        
        else return Regularised_Spherical_Wedge( s, p2, p1 );
    }
    
    else if (squared_distance( s.c, p2 ) < tiny_num)
    {
        if (p1.oriented_side( s.c ) == ON_POSITIVE_SIDE) return 0.5 * s.vol - Regularised_Spherical_Wedge( s, p1.opposite(), p2 );
        
        else return Regularised_Spherical_Wedge( s, p1, p2 );
    }
    
    P3 pt1, pt2;
    
    pt1 = l.point( 1 );
    pt2 = l.point( 2 );
    
    Pl3 p3( pt1, pt2, s.c );
    
    P3 pt3 = p1.point();
    
    if (squared_distance( pt3, l ) < tiny_num)
    {
        pt3 += p1.base1();
        
        if (squared_distance( pt3, l ) < tiny_num) pt3 += p1.base2();
    }
    
    if (p1.oriented_side( s.c ) != p2.oriented_side( s.c ))
    {
        if (p2.oriented_side( pt3 ) != p3.oriented_side( pt3 )) p3 = p3.opposite();
        
        V3 v = pt1 - s.c;
        P3 pt4 = pt1 + v;
        
        L3 l2( pt4, p3.orthogonal_vector() );
        
        P3 i1, i2;
        Pl3 p4, p5;
        
        bool intersect_1 = Intersection_Of_Line_And_Plane( p1, l2, i1 );
        bool intersect_2 = Intersection_Of_Line_And_Plane( p2, l2, i2 );
        
        if (intersect_1 && intersect_2)
        {
            if (p3.oriented_side( i1 ) == p3.oriented_side( i2 ))
            {
                if (p3.oriented_side( i1 ) == ON_POSITIVE_SIDE)
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
                    if (Norm( i1, pt4 ) > Norm( i2, pt4 ))
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
        
        else if (intersect_1)
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
        if (p2.oriented_side( pt3 ) != p3.oriented_side( pt3 )) p3 = p3.opposite();
        
        double volume1 = Regularised_Spherical_Wedge( s, p1.opposite(), p3 );
        double volume2 = Regularised_Spherical_Wedge( s, p2.opposite(), p3.opposite() );
        
        return s.vol - volume1 - volume2;
    }
    
    else
    {
        if (p2.oriented_side( pt3 ) != p3.oriented_side( pt3 )) p3 = p3.opposite();
        
        double volume1 = Regularised_Spherical_Wedge( s, p1, p3 );
        double volume2 = Regularised_Spherical_Wedge( s, p2, p3.opposite() );
        
        return volume1 + volume2;
    }
}
