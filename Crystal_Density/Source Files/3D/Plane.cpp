#include "Plane.h"

Plane::Plane ( P3 const& pt1, P3 const& pt2, P3 const& pt3 )
{
    v1 = pt1 - pt2;
    v2 = pt3 - pt2;
    
    n = normal( pt1, pt2, pt3 );
    
    a = n.x();
    b = n.y();
    c = n.z();
    d = -a * pt1.x() - b * pt1.y() - c * pt1.z();
}

Plane::Plane(){}
Plane::~Plane(){}
