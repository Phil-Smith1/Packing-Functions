#include "Circular_Intersection_Of_Sphere_And_Plane.h"

double Cone ( Sphere const& s, Pl3 const& p )
{
    Circle3D c = Circular_Intersection_Of_Sphere_And_Plane( s, p );
    
    double h = Norm( s.c, c.c );
    
    return PI * c.r * c.r * h / (double)3;
}
