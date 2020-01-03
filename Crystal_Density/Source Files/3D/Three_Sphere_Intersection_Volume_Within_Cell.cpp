#include "Two_Sphere_Intersection_Volume_Within_Cell.h"
#include "Spherical_Wedge_Volume_Within_Cell.h"
#include "Circumradius.h"

double Three_Sphere_Intersection_Volume_Within_Cell ( Cell3D const& cell, Sphere const& s1, Sphere const& s2, Sphere const& s3 )
{
    vector<Sphere> spheres = { s1, s2, s3 };
    
    Sphere_Ordering( spheres );
    
    double d1 = Norm( spheres[1].c, spheres[2].c ), d2 = Norm( spheres[0].c, spheres[2].c ), d3 = Norm( spheres[0].c, spheres[1].c );
    
    if (d1 >= spheres[1].r + spheres[2].r - tiny_num) return 0;
    else if (d2 >= spheres[0].r + spheres[2].r - tiny_num) return 0;
    else if (d3 >= spheres[0].r + spheres[1].r - tiny_num) return 0;
    
    else if (d1 <= spheres[2].r - spheres[1].r + tiny_num) return Two_Sphere_Intersection_Volume_Within_Cell( cell, spheres[0], spheres[2] );
    else if (d2 <= spheres[2].r - spheres[0].r + tiny_num) return Two_Sphere_Intersection_Volume_Within_Cell( cell, spheres[1], spheres[2] );
    else if (d3 <= spheres[1].r - spheres[0].r + tiny_num) return Two_Sphere_Intersection_Volume_Within_Cell( cell, spheres[1], spheres[2] );
    
    else if (Circumradius( spheres[0].c, spheres[1].c, spheres[2].c ) > spheres[0].r - tiny_num) return 0;
    
    else
    {
        V3 v = spheres[0].c - spheres[1].c;
        v = v / (double)Norm( v );
        
        double k = (spheres[1].r * spheres[1].r + d3 * d3 - spheres[0].r * spheres[0].r) / (double)(2 * d3);
        
        P3 pt3 = spheres[1].c + k * v;
        
        Pl3 p3( pt3, v );
        
        v = spheres[0].c - spheres[2].c;
        v = v / (double)Norm( v );
        
        k = (spheres[2].r * spheres[2].r + d2 * d2 - spheres[0].r * spheres[0].r) / (double)(2 * d2);
        
        P3 pt2 = spheres[2].c + k * v;
        
        Pl3 p2( pt2, v );
        
        v = spheres[1].c - spheres[2].c;
        v = v / (double)Norm( v );
        
        k = (spheres[2].r * spheres[2].r + d1 * d1 - spheres[1].r * spheres[1].r) / (double)(2 * d1);
        
        P3 pt1 = spheres[2].c + k * v;
        
        Pl3 p1( pt1, v );
        
        Pl3 p4;
        
        if (collinear( spheres[0].c, spheres[1].c, spheres[2].c ))
        {
            if (collinear( spheres[0].c, spheres[1].c, P3( 0, 0, 0 ) ))
            {
                if (collinear( spheres[0].c, spheres[1].c, P3( 1, 0, 0 ) ))
                {
                    p4 = Pl3( spheres[0].c, spheres[1].c, P3( 0, 1, 0 ) );
                }
                
                else p4 = Pl3( spheres[0].c, spheres[1].c, P3( 1, 0, 0 ) );
            }
            
            else p4 = Pl3( spheres[0].c, spheres[1].c, P3( 0, 0, 0 ) );
        }
        
        else p4 = Pl3( spheres[0].c, spheres[1].c, spheres[2].c );
        
        Circle3D c3 = Circular_Intersection_Of_Sphere_And_Plane( spheres[0], p3 );
        Circle3D c2 = Circular_Intersection_Of_Sphere_And_Plane( spheres[0], p2 );
        Circle3D c1 = Circular_Intersection_Of_Sphere_And_Plane( spheres[1], p1 );
        
        L3 l1 = Line_Of_Intersection_Of_Two_Planes( p1, p4 );
        L3 l2 = Line_Of_Intersection_Of_Two_Planes( p2, p4 );
        L3 l3 = Line_Of_Intersection_Of_Two_Planes( p3, p4 );
        
        P3 pt4, pt5, pt6, pt7, pt8, pt9;
        
        pt4 = pt1 + c1.r * l1.to_vector() / (double)Norm( l1.to_vector() );
        pt5 = pt1 - c1.r * l1.to_vector() / (double)Norm( l1.to_vector() );
        pt6 = pt2 + c2.r * l2.to_vector() / (double)Norm( l2.to_vector() );
        pt7 = pt2 - c2.r * l2.to_vector() / (double)Norm( l2.to_vector() );
        pt8 = pt3 + c3.r * l3.to_vector() / (double)Norm( l3.to_vector() );
        pt9 = pt3 - c3.r * l3.to_vector() / (double)Norm( l3.to_vector() );
        
        if (Norm( pt4, spheres[0].c ) < spheres[0].r && Norm( pt5, spheres[0].c ) < spheres[0].r) return Two_Sphere_Intersection_Volume_Within_Cell( cell, spheres[1], spheres[2] );
        else if (Norm( pt6, spheres[1].c ) < spheres[1].r && Norm( pt7, spheres[1].c ) < spheres[1].r) return Two_Sphere_Intersection_Volume_Within_Cell( cell, spheres[0], spheres[2] );
        else if (Norm( pt8, spheres[2].c ) < spheres[2].r && Norm( pt9, spheres[2].c ) < spheres[2].r) return Two_Sphere_Intersection_Volume_Within_Cell( cell, spheres[0], spheres[1] );
        
        else
        {
            double volume1 = Spherical_Wedge_Volume_Within_Cell( cell, spheres[0], p3.opposite(), p2.opposite() );
            double volume2 = Spherical_Wedge_Volume_Within_Cell( cell, spheres[2], p3.opposite(), p2 );
            double volume3 = Spherical_Wedge_Volume_Within_Cell( cell, spheres[1], p3, p1.opposite() );
            double volume4 = Spherical_Wedge_Volume_Within_Cell( cell, spheres[2], p3, p1 );
            
            return volume1 + volume2 + volume3 + volume4;
        }
    }
}
