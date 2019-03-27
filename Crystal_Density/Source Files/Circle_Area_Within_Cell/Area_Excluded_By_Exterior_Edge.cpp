#include "Correct_Side_Of_Cell.h"
#include "Segment_Area.h"

double Area_Excluded_By_Exterior_Edge ( Circle const& circle, Edge const& e, Cell const& cell )
{
    if (e.intersection_type == 3 || e.intersection_type == 6 || e.intersection_type == 7)
    {
        double segment_area = Segment_Area( circle, e.i1, e.i2 );
        
        if (Correct_Side_Of_Cell( cell, e, circle.c )) return segment_area;
        
        else return circle.area - segment_area;
    }
    
    else return 0;
}
