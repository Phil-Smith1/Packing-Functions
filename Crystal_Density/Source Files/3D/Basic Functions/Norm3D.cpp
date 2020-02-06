#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 P3;
typedef K::Vector_3 V3;

double Norm ( P3 const& p )
{
    double length = sqrt( squared_distance( p, P3( 0, 0, 0 ) ) );
    
    return length;
}

double Norm ( P3 const& p1, P3 const& p2 )
{
    double length = sqrt( squared_distance( p1, p2 ) );
    
    return length;
}

double Norm ( V3 const& v )
{
    double length = sqrt( v.squared_length() );
    
    return length;
}
