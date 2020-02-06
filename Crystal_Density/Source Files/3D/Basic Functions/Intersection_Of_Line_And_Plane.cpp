#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 P3;
typedef K::Vector_3 V3;
typedef K::Line_3 L3;
typedef K::Plane_3 Pl3;

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

bool Intersection_Of_Line_And_Plane ( Pl3 const& p, L3 const& l, P3& pt )
{
    V3 n = p.orthogonal_vector(), d = l.to_vector();
    
    double dot_product = n.x() * d.x() + n.y() * d.y() + n.z() * d.z();
    
    if (abs( dot_product ) < tiny_num) return false; // Decreased tiny_num by 2 orders of magnitude.
    
    else
    {
        P3 pt1 = p.point();
        P3 pt2 = l.point( 0 );
        
        V3 w = pt2 - pt1;
        
        double s = -1 * (n.x() * w.x() + n.y() * w.y() + n.z() * w.z()) / (double)dot_product;
        
        pt = pt2 + s * d;
        
        return true;
    }
}
