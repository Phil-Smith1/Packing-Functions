#include "Sphere.h"

typedef K::Plane_3 Pl3;

double Sphere_Plane_Distance ( Sphere const& s, Pl3 const& p )
{
    double d = (p.a() * s.c.x() + p.b() * s.c.y() + p.c() * s.c.z() + p.d()) / (double)(sqrt( p.a() * p.a() + p.b() * p.b() + p.c() * p.c() ));
    
    return d;
}
