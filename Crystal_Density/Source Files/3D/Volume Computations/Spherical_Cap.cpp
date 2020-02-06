#include "Circular_Intersection_Of_Sphere_And_Plane.h"

double Spherical_Cap ( Sphere const& s, Pl3 const& p )
{
    double sphere_plane_distance = Sphere_Plane_Distance( s, p );
    
    if (sphere_plane_distance >= s.r || sphere_plane_distance <= -s.r)
    {
        if (p.oriented_side( s.c ) == ON_POSITIVE_SIDE) return s.vol;
        
        else return 0;
    }
    
    Circle3D c = Circular_Intersection_Of_Sphere_And_Plane( s, p );
    
    double h = s.r - abs( sphere_plane_distance );
    
    double spherical_cap = PI * h * (3 * c.r * c.r + h * h) / (double)6;
    
    if (p.oriented_side( s.c ) == ON_POSITIVE_SIDE) return s.vol - spherical_cap;
    
    else return spherical_cap;
}
