#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 P3;

void Frac_To_Cart_Coords ( double ** matrix, P3& p )
{
    double cart_coords_x = matrix[0][0] * p.x() + matrix[0][1] * p.y() + matrix[0][2] * p.z();
    double cart_coords_y = matrix[1][0] * p.x() + matrix[1][1] * p.y() + matrix[1][2] * p.z();
    double cart_coords_z = matrix[2][0] * p.x() + matrix[2][1] * p.y() + matrix[2][2] * p.z();
    
    p = P3( cart_coords_x, cart_coords_y, cart_coords_z );
}
