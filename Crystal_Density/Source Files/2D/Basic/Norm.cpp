#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;
typedef K::Vector_2 V2;

double Norm ( P2 const& p )
{
    double length = sqrt( squared_distance( p, P2( 0, 0 ) ) );
    
    return length;
}

double Norm ( P2 const& p1, P2 const& p2 )
{
    double length = sqrt( squared_distance( p1, p2 ) );
    
    return length;
}

double Norm ( V2 const& v )
{
    double length = sqrt( v.squared_length() );
    
    return length;
}
