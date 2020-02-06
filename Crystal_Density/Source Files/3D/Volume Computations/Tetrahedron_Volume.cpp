#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 P3;
typedef K::Vector_3 V3;

double Tetrahedron_Volume ( P3 const& p1, P3 const& p2, P3 const& p3, P3 const& p4 )
{
    V3 v1 = p2 - p1;
    V3 v2 = p3 - p1;
    V3 v3 = p4 - p1;
    
    double volume = v1.y() * v2.z() * v3.x() - v1.z() * v2.y() * v3.x() + v1.z() * v2.x() * v3.y() - v1.x() * v2.z() * v3.y() + v1.x() * v2.y() * v3.z() - v1.y() * v2.x() * v3.z();
    
    volume = abs( volume / (double)6 );
    
    return volume;
}
