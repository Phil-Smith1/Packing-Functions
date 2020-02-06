#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;
typedef K::Line_2 L2;

P2 Triangle_Circumcentre ( P2 const& p1, P2 const& p2, P2 const& p3 )
{
    P2 p4;
    
    L2 l1 = CGAL::bisector( p1, p2 );
    L2 l2 = CGAL::bisector( p2, p3 );
    
    CGAL::cpp11::result_of<K::Intersect_2(L2, L2)>::type intersection = CGAL::intersection( l1, l2 );
    
    if (intersection)
    {
        P2 * p = boost::get<P2>( &*intersection );
        p4 = *p;
        
        return p4;
    }
    
    else
    {
        L2 l3 = L2( p1, p2 );
        L2 l4 = l3.perpendicular( p1 );
        L2 l5 = l3.perpendicular( p2 );
        
        if (l4.oriented_side( p2 ) != l4.oriented_side( p3 )) p4 = P2( 0.5 * (p2.x() + p3.x()), 0.5 * (p2.y() + p3.y()) );
        
        else if (l5.oriented_side( p1 ) != l5.oriented_side( p3 )) p4 = P2( 0.5 * (p1.x() + p3.x()), 0.5 * (p1.y() + p3.y()) );
        
        else p4 = P2( 0.5 * (p1.x() + p2.x()), 0.5 * (p1.y() + p2.y()) );
        
        return p4;
    }
}
