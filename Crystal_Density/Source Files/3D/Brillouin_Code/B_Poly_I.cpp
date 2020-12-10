#include "B_Poly_I.h"

B_Poly_I::B_Poly_I ( Polyhedron_I const& p, double d, int z )
{
    poly = p;
    dist = d;
    zone = z;
}

B_Poly_I::B_Poly_I(){}
B_Poly_I::~B_Poly_I(){}
