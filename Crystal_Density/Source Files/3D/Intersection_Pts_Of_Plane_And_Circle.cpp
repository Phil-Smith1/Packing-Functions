#include "Circle.h"
#include "Norm3D.h"

typedef K::Plane_3 Pl3;

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

void Intersection_Pts_Of_Plane_And_Circle ( Pl3 const& p, Circle3D const& c, P3& pt1, P3& pt2 )
{
    P3 pt = p.point();
    V3 v = p.orthogonal_vector() / (double)Norm( p.orthogonal_vector() );
    V3 b1 = c.v1;
    V3 b2 = c.v2;
    
    double k1 = (c.c.x() - pt.x()) * v.x() + (c.c.y() - pt.y()) * v.y() + (c.c.z() - pt.z()) * v.z();
    double k2 = b1.x() * v.x() + b1.y() * v.y() + b1.z() * v.z();
    double k3 = b2.x() * v.x() + b2.y() * v.y() + b2.z() * v.z();
    
    double alpha = acos( k2 / (double)sqrt( k2 * k2 + k3 * k3 ) );
    
    double thetaplusalpha = asin( -k1 / (double)sqrt( k2 * k2 + k3 * k3 ) );
    double theta1 = thetaplusalpha - alpha;
    
    if (abs( k2 * sin( theta1 ) + k3 * cos( theta1 ) + k1 ) > tiny_num)
    {
        alpha *= -1;
        theta1 = thetaplusalpha - alpha;
    }
    
    int n = (thetaplusalpha >= 0) ? 2 : 1;
    
    double theta2 = pow( -1, n ) * PI - thetaplusalpha - alpha;
    
    if (abs( k2 * sin( theta2 ) + k3 * cos( theta2 ) + k1 ) > tiny_num)
    {
        alpha *= -1;
        theta1 = thetaplusalpha - alpha;
        theta2 = pow( -1, n ) * PI - thetaplusalpha - alpha;
    }
    
    pt1 = c.c + sin( theta1 ) * b1 + cos( -theta1 ) * b2;
    pt2 = c.c + sin( theta2 ) * b1 + cos( -theta2 ) * b2;
}
