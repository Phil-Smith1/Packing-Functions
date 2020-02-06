#include "B_Poly.h"

B_Poly::B_Poly ( Polyhedron const& p, double d, int z )
{
    poly = p;
    dist = d;
    zone = z;
}

B_Poly::B_Poly(){}
B_Poly::~B_Poly(){}
