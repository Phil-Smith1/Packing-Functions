#include "Norm.h"

double Triangle_Area ( double base, double height )
{
    return 0.5 * base * height;
}

double Triangle_Area ( P2 const& p1, P2 const& p2, P2 const& p3 )
{
    V2 v1 = p1 - ORIGIN;
    
    P2 p4 = p2 - v1;
    P2 p5 = p3 - v1;
    
    double l1 = Norm( p4 );
    double l2 = Norm( p5 );
    
    double angle = acos( (p4.x() * p5.x() + p4.y() * p5.y()) / (double)(l1 * l2) );
    
    return 0.5 * l1 * l2 * sin( angle );
}
