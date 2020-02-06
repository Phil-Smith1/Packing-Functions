#include "Sphere.h"

Sphere::Sphere ( P3 const& centre, double radius )
{
    c = centre;
    r = radius;
    vol = 4 * PI * r * r * r / (double)3;
}

Sphere::Sphere(){}
Sphere::~Sphere(){}
