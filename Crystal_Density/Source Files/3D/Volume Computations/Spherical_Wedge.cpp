#include "Sphere.h"
#include "Angle_Between_Vectors3D.h"

typedef K::Plane_3 Pl3;

double Spherical_Wedge ( Sphere const& s, Pl3 const& p1, Pl3 const& p2 )
{
    P3 pt1 = P3( 0, 0, 0 ) + p1.orthogonal_vector();
    P3 pt2 = P3( 0, 0, 0 ) - p2.orthogonal_vector();
    
    double angle = Angle_Between_Vectors( pt1, pt2 );
    
    double volume = 2 * s.r * s.r * s.r * angle / (double)3;
    
    return volume;
}
