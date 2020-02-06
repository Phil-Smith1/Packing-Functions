#include "Norm.h"

double Angle_Between_Vectors ( P2 const& p1, P2 const& p2 )
{
    return acos( (p1.x() * p2.x() + p1.y() * p2.y()) / double(Norm( p1 ) * Norm( p2 )) );
}
