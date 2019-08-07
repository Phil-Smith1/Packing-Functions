#include "Sphere_Ordering.h"
#include "Spherical_Cap.h"

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

double Volume_Of_Intersection_Of_Two_Spheres ( Sphere const& s1, Sphere const& s2 )
{
    vector<Sphere> spheres = { s1, s2 };
    
    Sphere_Ordering( spheres );
    
    double d = Norm( s1.c, s2.c );
    
    if (d >= s1.r + s2.r - tiny_num) return 0;
    
    else if (d <= s2.r - s1.r + tiny_num) return s1.vol;
    
    else
    {
        V3 v = s1.c - s2.c;
        v = v / (double)Norm( v );
        
        double k = s2.r * (s2.r * s2.r + d * d - s1.r * s1.r) / (double)(2 * s2.r * d);
        
        P3 pt = s2.c + k * v;
        
        Pl3 p( pt, v );
        
        double spherical_cap1 = Spherical_Cap( s2, p );
        
        p = p.opposite();
        
        double spherical_cap2 = Spherical_Cap( s1, p );
        
        return spherical_cap1 + spherical_cap2;
    }
}
