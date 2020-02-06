#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 P3;
typedef K::Vector_3 V3;
typedef K::Line_3 L3;

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

P3 Intersection_Of_Two_Lines3D ( L3 const& l1, L3 const& l2 )
{
    V3 v1 = l1.to_vector();
    P3 p1 = l1.point( 0 );
    V3 v2 = l2.to_vector();
    P3 p2 = l2.point( 0 );
    
    double multiplier = 1;
    
    while (multiplier > 1e-20)
    {
        if (abs( v1.x() ) > tiny_num * 1e-5 && abs( v1.y() * v2.x() / (double)v1.x() - v2.y() ) > tiny_num * multiplier) //* 1e-4 for T2 experimental dataset, changed to * 1e-3 for T2_dataset No. 38.
        {
            double t = (p2.y() - p1.y() + p1.x() * v1.y() / (double)v1.x() - p2.x() * v1.y() / (double)v1.x()) / (double)(v1.y() * v2.x() / (double)v1.x() - v2.y());
            
            double x = p2.x() + t * v2.x();
            double y = p2.y() + t * v2.y();
            double z = p2.z() + t * v2.z();
            
            return P3( x, y, z );
        }
        
        else if (abs( v1.x() ) > tiny_num * 1e-5 && abs( v1.z() * v2.x() / (double)v1.x() - v2.z() ) > tiny_num * multiplier)
        {
            double t = (p2.z() - p1.z() + p1.x() * v1.z() / (double)v1.x() - p2.x() * v1.z() / (double)v1.x()) / (double)(v1.z() * v2.x() / (double)v1.x() - v2.z());
            
            double x = p2.x() + t * v2.x();
            double y = p2.y() + t * v2.y();
            double z = p2.z() + t * v2.z();
            
            return P3( x, y, z );
        }
        
        else if (abs( v1.y() ) > tiny_num * 1e-5 && abs( v1.x() * v2.y() / (double)v1.y() - v2.x() ) > tiny_num * multiplier)
        {
            double t = (p2.x() - p1.x() + p1.y() * v1.x() / (double)v1.y() - p2.y() * v1.x() / (double)v1.y()) / (double)(v1.x() * v2.y() / (double)v1.y() - v2.x());
            
            double x = p2.x() + t * v2.x();
            double y = p2.y() + t * v2.y();
            double z = p2.z() + t * v2.z();
            
            return P3( x, y, z );
        }
        
        else if (abs( v1.y() ) > tiny_num * 1e-5 && abs( v1.z() * v2.y() / (double)v1.y() - v2.z() ) > tiny_num * multiplier)
        {
            double t = (p2.z() - p1.z() + p1.y() * v1.z() / (double)v1.y() - p2.y() * v1.z() / (double)v1.y()) / (double)(v1.z() * v2.y() / (double)v1.y() - v2.z());
            
            double x = p2.x() + t * v2.x();
            double y = p2.y() + t * v2.y();
            double z = p2.z() + t * v2.z();
            
            return P3( x, y, z );
        }
        
        else if (abs( v1.z() ) > tiny_num * 1e-5 && abs( v1.x() * v2.z() / (double)v1.z() - v2.x() ) > tiny_num * multiplier)
        {
            double t = (p2.x() - p1.x() + p1.z() * v1.x() / (double)v1.z() - p2.z() * v1.x() / (double)v1.z()) / (double)(v1.x() * v2.z() / (double)v1.z() - v2.x());
            
            double x = p2.x() + t * v2.x();
            double y = p2.y() + t * v2.y();
            double z = p2.z() + t * v2.z();
            
            return P3( x, y, z );
        }
        
        else if (abs( v1.z() ) > tiny_num * 1e-5 && abs( v1.y() * v2.z() / (double)v1.z() - v2.y() ) > tiny_num * multiplier)
        {
            double t = (p2.y() - p1.y() + p1.z() * v1.y() / (double)v1.z() - p2.z() * v1.y() / (double)v1.z()) / (double)(v1.y() * v2.z() / (double)v1.z() - v2.y());
            
            double x = p2.x() + t * v2.x();
            double y = p2.y() + t * v2.y();
            double z = p2.z() + t * v2.z();
            
            return P3( x, y, z );
        }
        
        multiplier *= 1e-1;
    }
    
    return P3( 0, 0, 0 );
}
