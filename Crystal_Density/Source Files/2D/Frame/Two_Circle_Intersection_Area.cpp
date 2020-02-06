#include "Intersection_Of_Two_Circles.h"
#include "Segment_Area.h"

typedef K::Line_2 L2;

double Two_Circle_Intersection_Area ( Circle const& c1, Circle const& c2 )
{
    P2 i1, i2;
    
    bool intersection = Intersection_Of_Two_Circles( c1, c2, i1, i2 );
    
    if (!intersection)
    {
        Circle smaller_circle = c1.r < c2.r ? c1 : c2;
        
        if (Norm( c1.c, c2.c ) < abs( (double)(c1.r - c2.r) )) return smaller_circle.area;
        
        else return 0;
    }
    
    else
    {
        double segment_area_1 = Segment_Area( c1, i1, i2 );
        double segment_area_2 = Segment_Area( c2, i1, i2 );
        
        L2 l( i1, i2 );
        
        if (l.oriented_side( c1.c ) == l.oriented_side( c2.c ))
        {
            if (squared_distance( c1.c, l ) < squared_distance( c2.c, l ))
            {
                segment_area_1 = c1.area - segment_area_1;
            }
            
            else segment_area_2 = c2.area - segment_area_2;
        }
        
        return segment_area_1 + segment_area_2;
    }
}

double Two_Circle_Intersection_Area ( Circle const& c1, Circle const& c2, P2& i1, P2& i2, bool& intersection )
{
    intersection = Intersection_Of_Two_Circles( c1, c2, i1, i2 );
    
    if (!intersection)
    {
        Circle smaller_circle = c1.r < c2.r ? c1 : c2;
        
        if (Norm( c1.c, c2.c ) < abs( (double)(c1.r - c2.r) )) return smaller_circle.area;
        
        else return 0;
    }
    
    else
    {
        double segment_area_1 = Segment_Area( c1, i1, i2 );
        double segment_area_2 = Segment_Area( c2, i1, i2 );
        
        L2 l( i1, i2 );
        
        if (l.oriented_side( c1.c ) == l.oriented_side( c2.c ))
        {
            if (squared_distance( c1.c, l ) < squared_distance( c2.c, l ))
            {
                segment_area_1 = c1.area - segment_area_1;
            }
            
            else segment_area_2 = c2.area - segment_area_2;
        }
        
        return segment_area_1 + segment_area_2;
    }
}
