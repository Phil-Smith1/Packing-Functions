#include "Cell_2Circles.h"
#include "Triangle_Area.h"
#include "Area_Excluded_By_Exterior_Edge.h"

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

double Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge ( Cell_2Circles const& c2c, Edge const& e1, Edge const& e2 )
{
    Circle c1 = c2c.cc[0].c;
    Circle c2 = c2c.cc[1].c;
    P2 i1 = c2c.tc.i1;
    P2 i2 = c2c.tc.i2;
    
    if (squared_distance( e1.line, i1 ) < tiny_num && squared_distance( e1.line, i2 ) < tiny_num)
    {
        if (e1.intersection_type == 3 || e1.intersection_type == 6 || e1.intersection_type == 7)
        {
            double area_1 = Area_Excluded_By_Exterior_Edge( c1, e1, c2c.cell );
            double area_2 = Area_Excluded_By_Exterior_Edge( c1, e2, c2c.cell );
            
            return (area_1 < area_2) ? area_1 : area_2;
        }
    }
    
    else if (squared_distance( e1.line, i1 ) < tiny_num)
    {
        if (e1.intersection_type == 3 || e1.intersection_type == 6 || e1.intersection_type == 7)
        {
            if (Norm( e1.i1, c2.c ) < c2.r - tiny_num || Norm( e1.i2, c2.c ) < c2.r - tiny_num)
            {
                double area = Area_Excluded_By_Exterior_Edge( c1, e1, c2c.cell );
                
                if (Correct_Side_Of_Cell( c2c.cell, e1, i2 )) return area;
                
                else return c2c.tc.intersection_area - c1.area + area;
            }
        }
        
        if (e2.intersection_type == 3 || e2.intersection_type == 6 || e2.intersection_type == 7)
        {
            if (Norm( e2.i1, c1.c ) < c1.r - tiny_num || Norm( e2.i2, c1.c ) < c1.r - tiny_num)
            {
                double area = Area_Excluded_By_Exterior_Edge( c2, e2, c2c.cell );
                
                if (Correct_Side_Of_Cell( c2c.cell, e2, i2 )) return area;
                
                else return c2c.tc.intersection_area - c1.area + area;
            }
        }
    }
    
    else if (squared_distance( e1.line, i2 ) < tiny_num)
    {
        if (e1.intersection_type == 3 || e1.intersection_type == 6 || e1.intersection_type == 7)
        {
            if (Norm( e1.i1, c2.c ) < c2.r - tiny_num || Norm( e1.i2, c2.c ) < c2.r - tiny_num)
            {
                double area = Area_Excluded_By_Exterior_Edge( c1, e1, c2c.cell );
                
                if (Correct_Side_Of_Cell( c2c.cell, e1, i1 )) return area;
                
                else return c2c.tc.intersection_area - c1.area + area;
            }
        }
        
        if (e2.intersection_type == 3 || e2.intersection_type == 6 || e2.intersection_type == 7)
        {
            if (Norm( e2.i1, c1.c ) < c1.r - tiny_num || Norm( e2.i2, c1.c ) < c1.r - tiny_num)
            {
                double area = Area_Excluded_By_Exterior_Edge( c2, e2, c2c.cell );
                
                if (Correct_Side_Of_Cell( c2c.cell, e2, i1 )) return area;
                
                else return c2c.tc.intersection_area - c2.area + area;
            }
        }
    }
    
    else
    {
        if (e1.line.oriented_side( i1 ) != e1.line.oriented_side( i2 ))
        {
            if (!((Norm( e1.startpt, c1.c ) < c1.r - tiny_num && Norm( e1.startpt, c2.c ) < c2.r - tiny_num) || (Norm( e1.endpt, c1.c ) < c1.r - tiny_num && Norm( e1.endpt, c2.c ) < c2.r - tiny_num)))
            {
                if ((e1.intersection_type == 2 || e1.intersection_type == 3 || e1.intersection_type == 4 || e1.intersection_type == 5 || e1.intersection_type == 6 || e1.intersection_type == 7) && (e2.intersection_type == 2 || e2.intersection_type == 3 || e2.intersection_type == 4 || e2.intersection_type == 5 || e2.intersection_type == 6 || e2.intersection_type == 7))
                {
                    P2 i3, i4, i5;
                    
                    if (Norm( e1.i1, c2.c ) < c2.r) i3 = e1.i1;
                    else i3 = e1.i2;
                    
                    if (Norm( e2.i1, c1.c ) < c1.r) i4 = e2.i1;
                    else i4 = e2.i2;
                    
                    if (Correct_Side_Of_Cell( c2c.cell, e1, i1 )) i5 = i2;
                    else i5 = i1;
                    
                    double triangle_area = Triangle_Area( i3, i4, i5 );
                    double segment_area_1 = Segment_Area( c1, i3, i5 );
                    
                    L2 l1( i3, i5 );
                    
                    if (!Same_Side( l1, i4, c1.c )) segment_area_1 = c1.area - segment_area_1;
                    
                    double segment_area_2 = Segment_Area( c2, i4, i5 );
                    
                    L2 l2( i4, i5 );
                    
                    if (!Same_Side( l2, i3, c2.c )) segment_area_2 = c2.area - segment_area_2;
                    
                    return triangle_area + segment_area_1 + segment_area_2;
                }
            }
        }
        
        else
        {
            if (e1.intersection_type == 3 || e1.intersection_type == 6 || e1.intersection_type == 7)
            {
                if (Norm( e1.i1, c2.c ) < c2.r - tiny_num && Norm( e1.i2, c2.c ) < c2.r - tiny_num)
                {
                    double area = Area_Excluded_By_Exterior_Edge( c1, e1, c2c.cell );
                    
                    if (Correct_Side_Of_Cell( c2c.cell, e1, i1 )) return area;
                    
                    else return c2c.tc.intersection_area - c1.area + area;
                }
            }
            
            if (e2.intersection_type == 3 || e2.intersection_type == 6 || e2.intersection_type == 7)
            {
                if (Norm( e2.i1, c1.c ) < c1.r - tiny_num && Norm( e2.i2, c1.c ) < c1.r - tiny_num)
                {
                    double area = Area_Excluded_By_Exterior_Edge( c2, e2, c2c.cell );
                    
                    if (Correct_Side_Of_Cell( c2c.cell, e2, i1 )) return area;
                    
                    else return c2c.tc.intersection_area - c2.area + area;
                }
            }
        }
    }
    
    return 0;
}
