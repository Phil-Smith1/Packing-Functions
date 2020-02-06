#include "Triangle_Area.h"
#include "Segment_Area.h"
#include "Intersection_Of_Two_Circles.h"

double Non_Trivial_Three_Circle_Intersection_Area ( Circle const& c1, Circle const& c2, Circle const& c3 )
{
    P2 i1, i2, i3, p1, p2;
    
    Intersection_Of_Two_Circles( c2, c3, p1, p2 );
    
    if (Norm( c1.c, p1 ) < c1.r) i1 = p1;
    
    else if (Norm( c1.c, p2 ) < c1.r) i1 = p2;
    
    Intersection_Of_Two_Circles( c1, c3, p1, p2 );
    
    if (Norm( c2.c, p1 ) < c2.r) i2 = p1;
    
    else if (Norm( c2.c, p2 ) < c2.r) i2 = p2;
    
    Intersection_Of_Two_Circles( c1, c2, p1, p2 );
    
    if (Norm( c3.c, p1 ) < c3.r) i3 = p1;
    
    else if (Norm( c3.c, p2 ) < c3.r) i3 = p2;
    
    double triangle_area = Triangle_Area( i1, i2, i3 );
    
    double segment_area_1 = Segment_Area( c1, i2, i3 );
    double segment_area_2 = Segment_Area( c2, i1, i3 );
    double segment_area_3 = Segment_Area( c3, i1, i2 );
    
    return triangle_area + segment_area_1 + segment_area_2 + segment_area_3;
}
