#include "Non_Inclusion_Three_Circle_Intersection_Area_Within_Cell.h"

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
