#include "Circular_Intersection_Of_Sphere_And_Plane.h"
#include "Intersection_Pts_Of_Plane_And_Circle.h"
#include "Angle_Between_Vectors3D.h"

double Partial_Cone ( Sphere const& s, Pl3 const& p1, Pl3 const& p2 )
{
    Circle3D c = Circular_Intersection_Of_Sphere_And_Plane( s, p1 );
    
    P3 pt1, pt2;
    
    Intersection_Pts_Of_Plane_And_Circle( p2, c, pt1, pt2 );
    
    V3 v = c.c - ORIGIN;
    
    P3 pt3 = pt1 - v;
    P3 pt4 = pt2 - v;
    
    double angle = Angle_Between_Vectors( pt3, pt4 );
    
    double h = Norm( s.c, c.c );
    
    double volume = 0.5 * (angle - sin( angle )) * c.r * c.r * h / (double) 3;
    
    return volume;
}
