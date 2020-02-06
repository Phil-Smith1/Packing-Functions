#include "Circle.h"

Circle::Circle ( P2 const& centre, double radius )
{
    c = centre;
    r = radius;
    area = PI * r * r;
}

Circle::Circle(){}
Circle::~Circle(){}

Circle3D::Circle3D ( P3 const& centre, double radius, V3 const& vec1, V3 const& vec2 )
{
    c = centre;
    r = radius;
    v1 = vec1 * r;
    v2 = vec2 * r;
    area = PI * r * r;
}

Circle3D::Circle3D(){}
Circle3D::~Circle3D(){}
