#include "Circle.h"
#include "Norm.h"

bool Intersection_Of_Two_Circles ( Circle const& c1, Circle const& c2, P2& i1, P2& i2 )
{
    double dist = Norm( c1.c, c2.c );
    
    if (c1.r + c2.r <= dist) return false;
    
    else if (dist < abs( (double)(c1.r - c2.r) )) return false;
    
    else
    {
        double a = (c1.r * c1.r + dist * dist - c2.r * c2.r) / (double)(2 * dist);
        
        double h = sqrt( c1.r * c1.r - a * a );
        
        V2 v1 = c1.c - ORIGIN;
        V2 v2 = c2.c - ORIGIN;
        
        V2 v3 = v1 + a * (v2 - v1) / (double)dist;
        
        double x = v3.x() + h * (v2.y() - v1.y()) / (double)dist;
        double y = v3.y() - h * (v2.x() - v1.x()) / (double)dist;
        
        i1 = P2( x, y );
        
        x = v3.x() - h * (v2.y() - v1.y()) / (double)dist;
        y = v3.y() + h * (v2.x() - v1.x()) / (double)dist;
        
        i2 = P2( x, y );
        
        return true;
    }
}
