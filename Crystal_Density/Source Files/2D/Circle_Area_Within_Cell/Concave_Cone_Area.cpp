#include "Edge.h"
#include "Triangle_Area.h"
#include "Segment_Area.h"

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

double Concave_Cone_Area ( Circle const& circle, Edge const& e1, Edge const& e2 )
{
    P2 v;
    
    if (Norm( e1.startpt, circle.c ) > circle.r + tiny_num) v = e1.startpt;
    
    else v = e1.endpt;
    
    double triangle_area = Triangle_Area( v, e1.i1, e2.i1 );
    
    double segment_area = Segment_Area( circle, e1.i1, e2.i1 );
    
    return triangle_area - segment_area;
}
