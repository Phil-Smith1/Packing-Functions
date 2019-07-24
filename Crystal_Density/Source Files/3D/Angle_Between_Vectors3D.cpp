#include "Norm3D.h"

double Angle_Between_Vectors ( P3 const& p1, P3 const& p2 )
{
    return acos( (p1.x() * p2.x() + p1.y() * p2.y() + p1.z() * p2.z()) / double(Norm( p1 ) * Norm( p2 )) );
}
