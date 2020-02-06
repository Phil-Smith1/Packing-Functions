#include "Non_Inclusion_Four_Circle_Intersection_Area_Within_Cell.h"

double Four_Circle_Intersection_Area_Within_Cell ( Cell_4Circles& c4c )
{
    if (c4c.c3c[0].area == 0 || c4c.c3c[1].area == 0 || c4c.c3c[2].area == 0 || c4c.c3c[3].area == 0) return 0;
    
    else
    {
        vector<Circle> circles;
        
        circles.push_back( c4c.fc.c[0] );
        circles.push_back( c4c.fc.c[1] );
        circles.push_back( c4c.fc.c[2] );
        circles.push_back( c4c.fc.c[3] );
        
        Cell cell = c4c.cell;
        
        bool inside0_1 = false, inside0_2 = false, inside0_3 = false, inside1_2 = false, inside1_3 = false, inside2_3 = false;
        
        if (Norm( circles[0].c, circles[1].c ) < circles[1].r - circles[0].r ) inside0_1 = true;
        if (Norm( circles[0].c, circles[2].c ) < circles[2].r - circles[0].r ) inside0_2 = true;
        if (Norm( circles[0].c, circles[3].c ) < circles[3].r - circles[0].r ) inside0_3 = true;
        if (Norm( circles[1].c, circles[2].c ) < circles[2].r - circles[1].r ) inside1_2 = true;
        if (Norm( circles[1].c, circles[3].c ) < circles[3].r - circles[1].r ) inside1_3 = true;
        if (Norm( circles[2].c, circles[3].c ) < circles[3].r - circles[2].r ) inside2_3 = true;
        
        if (inside0_1 && inside0_2 && inside0_3) return c4c.cc[0].area;
        
        else if (!inside0_1 && inside0_2 && inside0_3) return c4c.c2c[0].area;
        
        else if (inside0_1 && !inside0_2 && inside0_3) return c4c.c2c[1].area;
        
        else if (inside0_1 && inside0_2 && !inside0_3) return c4c.c2c[2].area;
        
        else if (!inside0_1 && !inside0_2 && inside0_3) return c4c.c3c[0].area;
        
        else if (!inside0_1 && inside0_2 && !inside0_3) return c4c.c3c[1].area;
        
        else if (inside0_1 && !inside0_2 && !inside0_3) return c4c.c3c[2].area;
        
        else if (inside1_2 && inside1_3) return c4c.c2c[0].area;
        
        else if (!inside1_2 && inside1_3) return c4c.c3c[0].area;
        
        else if (inside1_2 && !inside1_3) return c4c.c3c[1].area;
        
        else if (inside2_3) return c4c.c3c[0].area;
        
        return Non_Inclusion_Four_Circle_Intersection_Area_Within_Cell( c4c );
    }
}
