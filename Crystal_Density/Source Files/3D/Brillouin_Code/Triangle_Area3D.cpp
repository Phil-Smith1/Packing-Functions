#include "Angle_Between_Vectors3D.h"

double Triangle_Area3D ( P3 const& p1, P3 const& p2, P3 const& p3 )
{
    V3 v1 = p2 - p1;
    V3 v2 = p3 - p1;
    
    P3 p4 = P3( v1.x(), v1.y(), v1.z() );
    P3 p5 = P3( v2.x(), v2.y(), v2.z() );
    
    double theta = Angle_Between_Vectors( p4, p5 );
    
    double dist1 = Norm( v1 );
    double dist2 = Norm( v2 );
    
    return 0.5 * dist1 * dist2 * sin( theta );
}
