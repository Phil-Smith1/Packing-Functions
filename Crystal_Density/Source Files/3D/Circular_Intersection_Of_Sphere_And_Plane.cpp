#include "Sphere_Plane_Distance.h"
#include "Circle.h"

Circle3D Circular_Intersection_Of_Sphere_And_Plane ( Sphere const& s, Pl3 const& p )
{
    double sphere_plane_distance = Sphere_Plane_Distance( s, p );
    
    //if (sphere_plane_distance >= s.r || sphere_plane_distance <= -s.r) return 0;
    
    double r = sqrt( s.r * s.r - sphere_plane_distance * sphere_plane_distance );
    P3 c = s.c + V3( sphere_plane_distance * p.a(), sphere_plane_distance * p.b(), sphere_plane_distance * p.c() );
    V3 v1 = p.base1();
    V3 v2 = p.base2();
    
    return Circle3D( c, r, v1, v2 );
}
