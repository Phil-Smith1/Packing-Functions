#include "Circle.h"
#include "Angle_Between_Vectors3D.h"

typedef K::Plane_3 Pl3;

bool Intersection_Of_Plane_And_Circle ( Pl3 const& p, Circle3D const& c )
{
    double d = sqrt( squared_distance( c.c, p ) );
    
    P3 p1 = c.c + c.v1, p2 = c.c + c.v2;
    
    Pl3 pl2( c.c, p1, p2 );
    
    p1 = P3( 0, 0, 0 ) + p.orthogonal_vector();
    p2 = P3( 0, 0, 0 ) + pl2.orthogonal_vector();
    
    double angle = Angle_Between_Vectors( p1, p2 );
    
    double hypotenuse = d / (double)sin( angle );
    
    return (hypotenuse < c.r) ? true : false;
}
