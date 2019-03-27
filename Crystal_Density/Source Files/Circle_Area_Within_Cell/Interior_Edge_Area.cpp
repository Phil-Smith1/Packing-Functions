#include "Edge.h"
#include "Same_Side.h"
#include "Triangle_Area.h"
#include "Segment_Area.h"

double Interior_Edge_Area ( Circle const& circle, Edge const& e1, Edge const& e2, Edge const& e3 )
{
    double segment_area = Segment_Area( circle, e1.i1, e3.i1 );
    
    double triangle_area_1 = Triangle_Area( e2.startpt, e1.i1, e3.i1 );
    
    double triangle_area_2 = Triangle_Area( e2.startpt, e2.endpt, e3.i1 );
    
    L2 l( e1.i1, e3.i1 );
    
    if (Same_Side( l, circle.c, e2.startpt )) return triangle_area_1 + triangle_area_2 + segment_area;
    
    else return triangle_area_1 + triangle_area_2 + circle.area - segment_area;
}
