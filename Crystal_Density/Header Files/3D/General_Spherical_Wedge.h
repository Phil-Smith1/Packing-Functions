#include "Spherical_Wedge.h"
#include "Regularised_Spherical_Wedge.h"

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

double General_Spherical_Wedge ( Sphere const& s, Pl3 const& p1, Pl3 const& p2 );
