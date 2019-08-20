#include "Two_Sphere_Intersection_Volume_Within_Cell.h"
#include "Spherical_Wedge_Volume_Within_Cell.h"

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
    
    else
    {
        V3 v = spheres[0].c - spheres[1].c;
        v = v / (double)Norm( v );
        
        double k = spheres[1].r * (spheres[1].r * spheres[1].r + d3 * d3 - spheres[0].r * spheres[0].r) / (double)(2 * spheres[1].r * d3);
        
        P3 pt = spheres[1].c + k * v;
        
        Pl3 p3( pt, v );
        
        v = spheres[0].c - spheres[2].c;
        v = v / (double)Norm( v );
        
        k = spheres[2].r * (spheres[2].r * spheres[2].r + d2 * d2 - spheres[0].r * spheres[0].r) / (double)(2 * spheres[2].r * d2);
        
        pt = spheres[2].c + k * v;
        
        Pl3 p2( pt, v );
        
        v = spheres[1].c - spheres[2].c;
        v = v / (double)Norm( v );
        
        k = spheres[2].r * (spheres[2].r * spheres[2].r + d1 * d1 - spheres[1].r * spheres[1].r) / (double)(2 * spheres[2].r * d1);
        
        pt = spheres[2].c + k * v;
        
        Pl3 p1( pt, v );
        
        //double volume1 = Spherical_Cap_Volume_Within_Cell( cell, spheres[0], p3.opposite() );
        double volume1 = Spherical_Wedge_Volume_Within_Cell( cell, spheres[0], p3.opposite(), p2.opposite() );
        //double volume2 = Spherical_Wedge_Volume_Within_Cell( cell, spheres[2], p3.opposite(), p2 );
        //double volume3 = Spherical_Wedge_Volume_Within_Cell( cell, spheres[1], p3, p1.opposite() );
        //double volume4 = Spherical_Wedge_Volume_Within_Cell( cell, spheres[2], p3, p1 );
        
        std::cout << volume1 << std::endl;
        //std::cout << volume2 << std::endl;
        //std::cout << volume3 << std::endl;
        //std::cout << volume4 << std::endl;
        
        return volume1;// + volume2 + volume3 + volume4;
    }
}
