#include "Non_Trivial_Three_Circle_Intersection_Area_Within_Cell.h"

double Non_Inclusion_Three_Circle_Intersection_Area_Within_Cell ( Cell_3Circles& c3c )
{
    int j = 0, k = 0, l = 0;
    
    if (Norm( c3c.thc.c[2].c, c3c.thc.tc[2].i1 ) < c3c.thc.c[2].r + tiny_num) ++j;
    if (Norm( c3c.thc.c[2].c, c3c.thc.tc[2].i2 ) < c3c.thc.c[2].r + tiny_num) ++j;
    
    if (Norm( c3c.thc.c[1].c, c3c.thc.tc[1].i1 ) < c3c.thc.c[1].r + tiny_num) ++k;
    if (Norm( c3c.thc.c[1].c, c3c.thc.tc[1].i2 ) < c3c.thc.c[1].r + tiny_num) ++k;
    
    if (Norm( c3c.thc.c[0].c, c3c.thc.tc[0].i1 ) < c3c.thc.c[0].r + tiny_num) ++l;
    if (Norm( c3c.thc.c[0].c, c3c.thc.tc[0].i2 ) < c3c.thc.c[0].r + tiny_num) ++l;
    
    if (j == 1 && k == 1 && l == 1) return Non_Trivial_Three_Circle_Intersection_Area_Within_Cell( c3c );
    
    else if (j == 0 && k == 0 && l == 0) return 0;
    
    else
    {
        int d = 0;
        
        if (j == 2) ++d;
        if (k == 2) ++d;
        if (l == 2) ++d;
        
        if (d == 1)
        {
            if (j == 2) return c3c.c2c[0].area;
            else if (k == 2) return c3c.c2c[1].area;
            else return c3c.c2c[2].area;
        }
        
        else
        {
            double a, b;
            
            a = c3c.c2c[0].area;
            b = c3c.c2c[1].area;
            
            return a + b - c3c.thc.c[0].area;
        }
    }
}
