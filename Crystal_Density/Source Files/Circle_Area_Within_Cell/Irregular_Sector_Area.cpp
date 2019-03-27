#include "Edge.h"
#include "Same_Side.h"
#include "Triangle_Area.h"
#include "Segment_Area.h"

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

double Irregular_Sector_Area ( Circle const& circle, Edge const& e1, Edge const& e2 )
{
    P2 v;
    
    if (Norm( e1.startpt, circle.c ) < circle.r - tiny_num) v = e1.startpt;
    
    else v = e1.endpt;
    
    double triangle_area = Triangle_Area( v, e1.i1, e2.i1 );
    double segment_area = Segment_Area( circle, e1.i1, e2.i1 );
    
    L2 l( e1.i1, e2.i1 );
    
    if (Same_Side( l, circle.c, v )) return triangle_area + segment_area;
    
    else return triangle_area + circle.area - segment_area;
}
