#include "Circle.h"

Circle::Circle ( P2 const& centre, double radius )
{
    c = centre;
    r = radius;
    area = PI * r * r;
}

Circle::Circle(){}
Circle::~Circle(){}
