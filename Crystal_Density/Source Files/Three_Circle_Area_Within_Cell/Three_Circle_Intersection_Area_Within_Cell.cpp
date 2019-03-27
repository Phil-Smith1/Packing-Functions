#include "Two_Circle_Intersection_Area_Within_Cell.h"
#include "Order_Circles.h"
#include "Non_Inclusion_Three_Circle_Intersection_Area_Within_Cell.h"

double Three_Circle_Intersection_Area_Within_Cell ( Cell& cell, Circle const& c1, Circle const& c2, Circle const& c3 )
{
    double area_1, area_2, area_3;
    
    area_1 = Two_Circle_Intersection_Area( c2, c3 );
    area_2 = Two_Circle_Intersection_Area( c1, c3 );
    area_3 = Two_Circle_Intersection_Area( c1, c2 );
    
    if (area_1 == 0 || area_2 == 0 || area_3 == 0) return 0;
    
    else
    {
        vector<Circle> circles;
        
        circles.push_back( c1 );
        circles.push_back( c2 );
        circles.push_back( c3 );
        
        Order_Circles( circles );
        
        bool inside0_1 = false, inside0_2 = false, inside1_2 = false;
        
        if (Norm( circles[0].c, circles[1].c ) < circles[1].r - circles[0].r ) inside0_1 = true;
        if (Norm( circles[0].c, circles[2].c ) < circles[2].r - circles[0].r ) inside0_2 = true;
        if (Norm( circles[1].c, circles[2].c ) < circles[2].r - circles[1].r ) inside1_2 = true;
        
        if (inside0_1 && inside0_2 && inside1_2) return circles[0].area;
        
        else if (!inside0_1 && inside0_2 && inside1_2) return Two_Circle_Intersection_Area_Within_Cell( cell, circles[0], circles[1] );
        
        else if (inside0_1 && inside0_2 && !inside1_2) return Circle_Area_Within_Cell( cell, circles[0] );
        
        else if (inside0_1 && !inside0_2 && !inside1_2) return Two_Circle_Intersection_Area_Within_Cell( cell, circles[0], circles[2] );
        
        else if (!inside0_1 && inside0_2 && !inside1_2) return Two_Circle_Intersection_Area_Within_Cell( cell, circles[0], circles[1] );
        
        else if (!inside0_1 && !inside0_2 && inside1_2) return Two_Circle_Intersection_Area_Within_Cell( cell, circles[0], circles[1] );
        
        else
        {
            return Non_Inclusion_Three_Circle_Intersection_Area_Within_Cell( cell, circles[0], circles[1], circles[2] );
        }
    }
}

double Three_Circle_Intersection_Area_Within_Cell ( Cell_3Circles& c3c )
{
    if (c3c.thc.non_trivial_intersection) return Non_Trivial_Three_Circle_Intersection_Area_Within_Cell( c3c );
    
    else if (c3c.thc.non_inclusion_intersection) return Non_Inclusion_Three_Circle_Intersection_Area_Within_Cell( c3c );
    
    else if (c3c.c2c[0].area == 0 || c3c.c2c[1].area == 0 || c3c.c2c[2].area == 0) return 0;
    
    else
    {
        bool inside0_1 = false, inside0_2 = false, inside1_2 = false;
        
        if (Norm( c3c.thc.c[0].c, c3c.thc.c[1].c ) < c3c.thc.c[1].r - c3c.thc.c[0].r ) inside0_1 = true;
        if (Norm( c3c.thc.c[0].c, c3c.thc.c[2].c ) < c3c.thc.c[2].r - c3c.thc.c[0].r ) inside0_2 = true;
        if (Norm( c3c.thc.c[1].c, c3c.thc.c[2].c ) < c3c.thc.c[2].r - c3c.thc.c[1].r ) inside1_2 = true;
        
        if (inside0_1 && inside0_2 && inside1_2) return c3c.thc.c[0].area;
        
        else if (!inside0_1 && inside0_2 && inside1_2) return c3c.c2c[2].area;
        
        else if (inside0_1 && inside0_2 && !inside1_2) return c3c.thc.c[0].area;
        
        else if (inside0_1 && !inside0_2 && !inside1_2) return c3c.c2c[1].area;
        
        else if (!inside0_1 && inside0_2 && !inside1_2) return c3c.c2c[2].area;
        
        else return c3c.c2c[2].area;
    }
}
