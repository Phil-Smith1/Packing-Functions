#include "Cell.h"
#include "Norm.h"
#include "Line_Circle_Intersections.h"

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

void Edge_Circle_Intersections ( Circle const& circle, Edge& e )
{
    int num_intersections = Line_Circle_Intersections( circle, e );
    
    if (num_intersections < 2) e.intersection_type = 0;
    
    else
    {
        L2 perp_1 = e.line.perpendicular( e.startpt );
        L2 perp_2 = e.line.perpendicular( e.endpt );
        
        bool boundary = true;
        
        if (squared_distance( perp_1, e.i1 ) > tiny_num && squared_distance( perp_1, e.i2 ) > tiny_num && squared_distance( perp_2, e.i1 ) > tiny_num && squared_distance( perp_2, e.i2 ) > tiny_num) boundary = false;
        
        if (!boundary)
        {
            if (perp_1.oriented_side( e.i1 ) == perp_2.oriented_side( e.i1 ))
            {
                if (perp_1.oriented_side( e.i2 ) == perp_2.oriented_side( e.i2 ))
                {
                    if (Norm( e.startpt, circle.c ) < circle.r) e.intersection_type = 1;
                    
                    else e.intersection_type = 0;
                }
                
                else
                {
                    e.i1 = e.i2;
                    e.intersection_type = 2;
                }
            }
            
            else if (perp_1.oriented_side( e.i2 ) == perp_2.oriented_side( e.i2 ))
            {
                e.i2 = e.i1;
                e.intersection_type = 2;
            }
            
            else e.intersection_type = 3;
        }
        
        else
        {
            bool i1_on_bdry = false, i2_on_bdry = false;
            
            if (squared_distance( perp_1, e.i1 ) < tiny_num || squared_distance( perp_2, e.i1 ) < tiny_num) i1_on_bdry = true;
            
            if (squared_distance( perp_1, e.i2 ) < tiny_num || squared_distance( perp_2, e.i2 ) < tiny_num) i2_on_bdry = true;
            
            if (i1_on_bdry && i2_on_bdry) e.intersection_type = 7;
            
            else if (i1_on_bdry)
            {
                if (perp_1.oriented_side( e.i2 ) == perp_2.oriented_side( e.i2 ))
                {
                    e.i2 = e.i1;
                    
                    if (Norm( e.startpt, circle.c ) < circle.r - tiny_num || Norm( e.endpt, circle.c ) < circle.r - tiny_num) e.intersection_type = 5;
                    
                    else e.intersection_type = 4;
                }
                
                else e.intersection_type = 6;
            }
            
            else
            {
                if (perp_1.oriented_side( e.i1 ) == perp_2.oriented_side( e.i1 ))
                {
                    e.i1 = e.i2;
                    
                    if (Norm( e.startpt, circle.c ) < circle.r - tiny_num || Norm( e.endpt, circle.c ) < circle.r - tiny_num) e.intersection_type = 5;
                    
                    else e.intersection_type = 4;
                }
                
                else e.intersection_type = 6;
            }
        }
    }
}
