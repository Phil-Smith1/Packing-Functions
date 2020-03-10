#include "B_Poly_2D.h"

B_Poly_2D::B_Poly_2D ( Polygon const& p, double d, int z )
{
    poly = p;
    dist = d;
    zone = z;
}

B_Poly_2D::B_Poly_2D(){}
B_Poly_2D::~B_Poly_2D(){}
