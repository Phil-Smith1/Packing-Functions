// http://mathworld.wolfram.com/Circumradius.html

#include "Angle_Between_Vectors3D.h"

#ifndef Pi
#define Pi
const double PI = 3.14159265359;
#endif

double Circumradius ( P3 const& p1, P3 const& p2, P3 const& p3 )
{
    double a = Norm( p1, p2 );
    double b = Norm( p1, p3 );
    double c = Norm( p2, p3 );
    double s = 0.5 * (a + b + c);
    V3 v1 = p1 - ORIGIN;
    V3 v2 = p2 - ORIGIN;
    V3 v3 = p3 - ORIGIN;
    
    if (Angle_Between_Vectors( p3 - v1, p2 - v1 ) > 0.5 * PI) return 0.5 * c;
    else if (Angle_Between_Vectors( p3 - v2, p1 - v2 ) > 0.5 * PI) return 0.5 * b;
    else if (Angle_Between_Vectors( p1 - v3, p2 - v3 ) > 0.5 * PI) return 0.5 * a;
    
    else if ((s - a) * (s - b) * (s - c) < tiny_num)
    {
        double max_dist = std::max( a, b );
        max_dist = std::max( max_dist, c );
        
        return 0.5 * max_dist;
    }
    
    else return sqrt( a * a * b * b * c * c / (double)(16 * s * (s - a) * (s - b) * (s - c)) );
}
