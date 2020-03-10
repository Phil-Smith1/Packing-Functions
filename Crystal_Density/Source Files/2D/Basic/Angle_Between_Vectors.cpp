#include "Norm.h"

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

double Angle_Between_Vectors ( P2 const& p1, P2 const& p2 )
{
    double k = (p1.x() * p2.x() + p1.y() * p2.y()) / double(Norm( p1 ) * Norm( p2 ));
    
    if (abs( k - 1 ) < tiny_num) k = 1;
    if (abs( k + 1 ) < tiny_num) k = -1;
    
    return acos( k );
}
