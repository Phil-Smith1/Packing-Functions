#include "Sphere_Ordering.h"
#include "Sphere_Volume_Within_Cell.h"
#include "Spherical_Cap_Volume_Within_Cell.h"

double Two_Sphere_Intersection_Volume_Within_Cell ( Cell3D const& cell, Sphere const& s1, Sphere const& s2 )
{
    vector<Sphere> spheres = { s1, s2 };
    
    Sphere_Ordering( spheres );
    
    double d = Norm( s1.c, s2.c );
    
    if (d >= s1.r + s2.r - tiny_num) return 0;
    
    else if (d <= spheres[1].r - spheres[0].r + tiny_num) return Sphere_Volume_Within_Cell( cell, spheres[0] );
    
    else
    {
        V3 v = s1.c - s2.c;
        v = v / (double)Norm( v );
        
        double k = s2.r * (s2.r * s2.r + d * d - s1.r * s1.r) / (double)(2 * s2.r * d);
        
        P3 pt = s2.c + k * v;
        
        Pl3 p( pt, v );
        
        double volume1 = Spherical_Cap_Volume_Within_Cell( cell, s2, p );
        
        p = p.opposite();
        
        double volume2 = Spherical_Cap_Volume_Within_Cell( cell, s1, p );
        
        return volume1 + volume2;
    }
}
