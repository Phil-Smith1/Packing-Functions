#include "Edge.h"
#include "Circle.h"

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

int Line_Circle_Intersections ( Circle const& circle, Edge& e )
{
    double a = e.line.a(), b = e.line.b(), c = e.line.c();
    
    if (abs( a ) > tiny_num && abs( b ) > tiny_num)
    {
        double discriminant = circle.r * circle.r * (1 + pow( a / (double)b, 2 )) - pow( circle.c.y() + circle.c.x() * a / (double)b + c / (double)b, 2 );
        
        if (discriminant < 0) return 0;
        
        double x_1 = (circle.c.x() - circle.c.y() * a / (double)b - a * c / (double)(b * b) + sqrt( discriminant )) / (double)(1 + a * a / (double)(b * b));
        double x_2 = (circle.c.x() - circle.c.y() * a / (double)b - a * c / (double)(b * b) - sqrt( discriminant )) / (double)(1 + a * a / (double)(b * b));
        double y_1 = (- a * x_1 - c) / (double)b;
        double y_2 = (- a * x_2 - c) / (double)b;
        
        e.i1 = P2( x_1, y_1 );
        e.i2 = P2( x_2, y_2 );
        
        if (discriminant < tiny_num) return 1;
        
        else return 2;
    }
    
    else if (abs( b ) > tiny_num)
    {
        double discriminant = circle.r * circle.r - pow( c / (double)b + circle.c.y(), 2 );
        
        if (discriminant < 0) return 0;
        
        double x_1 = circle.c.x() + sqrt( discriminant );
        double x_2 = circle.c.x() - sqrt( discriminant );
        double y_1 = - c / (double)b;
        double y_2 = - c / (double)b;
        
        e.i1 = P2( x_1, y_1 );
        e.i2 = P2( x_2, y_2 );
        
        if (discriminant < tiny_num) return 1;
        
        else return 2;
    }
    
    else
    {
        double discriminant = circle.r * circle.r - pow( c / (double)a + circle.c.x(), 2 );
        
        if (discriminant < 0) return 0;
        
        double y_1 = circle.c.y() + sqrt( discriminant );
        double y_2 = circle.c.y() - sqrt( discriminant );
        double x_1 = - c / (double)a;
        double x_2 = - c / (double)a;
        
        e.i1 = P2( x_1, y_1 );
        e.i2 = P2( x_2, y_2 );
        
        if (discriminant < tiny_num) return 1;
        
        else return 2;
    }
}
