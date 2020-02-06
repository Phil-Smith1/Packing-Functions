#include "Circle.h"
#include "Angle_Between_Vectors.h"

double Segment_Area ( Circle const& circle, P2 const& p1, P2 const& p2 )
{
    V2 v = circle.c - ORIGIN;
    
    P2 p3 = p1 - v;
    P2 p4 = p2 - v;
    
    double angle = Angle_Between_Vectors( p3, p4 );
    
    return 0.5 * circle.r * circle.r * (angle - sin( angle ));
}
