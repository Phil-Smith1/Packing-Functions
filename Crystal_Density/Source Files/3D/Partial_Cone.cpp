#include "Circular_Intersection_Of_Sphere_And_Plane.h"

double Partial_Cone ( Sphere const& s, Pl3 const& p1, Pl3 const& p2 )
{
    Circle3D c = Circular_Intersection_Of_Sphere_And_Plane( s, p1 );
    
    return 0;
}
