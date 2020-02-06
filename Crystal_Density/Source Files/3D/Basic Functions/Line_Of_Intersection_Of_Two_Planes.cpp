#include "Norm3D.h"

typedef K::Line_3 L3;
typedef K::Plane_3 Pl3;

L3 Line_Of_Intersection_Of_Two_Planes ( Pl3 const& p1, Pl3 const& p2 )
{
    double a, b, c;
    
    a = p1.b() * p2.c() - p1.c() * p2.b();
    b = p1.c() * p2.a() - p1.a() * p2.c();
    c = p1.a() * p2.b() - p1.b() * p2.a();
    
    V3 v( a, b, c );
    
    if (abs( v.z() ) >= abs( v.y() ) && abs( v.z() ) >= abs( v.x() ))
    {
        a = (p1.b() * p2.d() - p2.b() * p1.d()) / (double)(p1.a() * p2.b() - p2.a() * p1.b());
        b = (p1.d() * p2.a() - p2.d() * p1.a()) / (double)(p1.a() * p2.b() - p2.a() * p1.b());
        
        P3 p( a, b, 0 );
        
        v = v / (double)Norm( v );
        
        L3 l( p, v );
        
        return l;
    }
    
    else if (abs( v.y() ) >= abs( v.z() ) && abs( v.y() ) >= abs( v.x() ))
    {
        a = (p1.c() * p2.d() - p2.c() * p1.d()) / (double)(p1.a() * p2.c() - p2.a() * p1.c());
        c = (p1.d() * p2.a() - p2.d() * p1.a()) / (double)(p1.a() * p2.c() - p2.a() * p1.c());
        
        P3 p( a, 0, c );
        
        v = v / (double)Norm( v );
        
        L3 l( p, v );
        
        return l;
    }
    
    else
    {
        b = (p1.c() * p2.d() - p2.c() * p1.d()) / (double)(p1.b() * p2.c() - p2.b() * p1.c());
        c = (p1.d() * p2.b() - p2.d() * p1.b()) / (double)(p1.b() * p2.c() - p2.b() * p1.c());
        
        P3 p( 0, b, c );
        
        v = v / (double)Norm( v );
        
        L3 l( p, v );
        
        return l;
    }
}
