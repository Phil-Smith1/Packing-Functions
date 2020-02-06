#include "Non_Trivial_Four_Circle_Intersection_Area_Within_Cell.h"

double Non_Inclusion_Four_Circle_Intersection_Area_Within_Cell ( Cell_4Circles& c4c )
{
    Circle c1 = c4c.cc[0].c, c2 = c4c.cc[1].c, c3 = c4c.cc[2].c, c4 = c4c.cc[3].c;
    
    P2 p1 = c4c.c2c[0].tc.i1, p2 = c4c.c2c[0].tc.i2, p3;
    
    if (Norm( c3.c, p1 ) < c3.r + tiny_num && Norm( c3.c, p2 ) < c3.r + tiny_num) return c4c.c3c[1].area;
    
    else if (Norm( c4.c, p1 ) < c4.r + tiny_num && Norm( c4.c, p2 ) < c4.r + tiny_num) return c4c.c3c[0].area;
    
    p1 = c4c.c2c[1].tc.i1;
    p2 = c4c.c2c[1].tc.i2;
    
    if (Norm( c2.c, p1 ) < c2.r + tiny_num && Norm( c2.c, p2 ) < c2.r + tiny_num) return c4c.c3c[2].area;
    
    else if (Norm( c4.c, p1 ) < c4.r + tiny_num && Norm( c4.c, p2 ) < c4.r + tiny_num) return c4c.c3c[0].area;
    
    p1 = c4c.c2c[2].tc.i1;
    p2 = c4c.c2c[2].tc.i2;
    
    if (Norm( c2.c, p1 ) < c2.r + tiny_num && Norm( c2.c, p2 ) < c2.r + tiny_num) return c4c.c3c[2].area;
    
    else if (Norm( c3.c, p1 ) < c3.r + tiny_num && Norm( c3.c, p2 ) < c3.r + tiny_num) return c4c.c3c[1].area;
    
    p1 = c4c.c2c[3].tc.i1;
    p2 = c4c.c2c[3].tc.i2;
    
    if (Norm( c1.c, p1 ) < c1.r + tiny_num && Norm( c1.c, p2 ) < c1.r + tiny_num) return c4c.c3c[3].area;
    
    else if (Norm( c4.c, p1 ) < c4.r + tiny_num && Norm( c4.c, p2 ) < c4.r + tiny_num) return c4c.c3c[0].area;
    
    p1 = c4c.c2c[4].tc.i1;
    p2 = c4c.c2c[4].tc.i2;
    
    if (Norm( c1.c, p1 ) < c1.r + tiny_num && Norm( c1.c, p2 ) < c1.r + tiny_num) return c4c.c3c[3].area;
    
    else if (Norm( c3.c, p1 ) < c3.r + tiny_num && Norm( c3.c, p2 ) < c3.r + tiny_num) return c4c.c3c[1].area;
    
    p1 = c4c.c2c[5].tc.i1;
    p2 = c4c.c2c[5].tc.i2;
    
    if (Norm( c1.c, p1 ) < c1.r + tiny_num && Norm( c1.c, p2 ) < c1.r + tiny_num) return c4c.c3c[3].area;
    
    else if (Norm( c2.c, p1 ) < c2.r + tiny_num && Norm( c2.c, p2 ) < c2.r + tiny_num) return c4c.c3c[2].area;
    
    p1 = c4c.c3c[0].thc.i1;
    p2 = c4c.c3c[0].thc.i2;
    p3 = c4c.c3c[0].thc.i3;
    
    if (Norm( c4.c, p1 ) < c4.r + tiny_num && Norm( c4.c, p2 ) < c4.r + tiny_num && Norm( c4.c, p3 ) < c4.r + tiny_num) return c4c.c3c[0].area;
    
    if (Norm( c4.c, p1 ) > c4.r - tiny_num && Norm( c4.c, p2 ) > c4.r - tiny_num && Norm( c4.c, p3 ) > c4.r - tiny_num)
    {
        return c4c.c2c[2].area + c4c.c2c[4].area + c4c.c2c[5].area - 2 * c4c.cc[3].area;
    }
    
    p1 = c4c.c3c[1].thc.i1;
    p2 = c4c.c3c[1].thc.i2;
    p3 = c4c.c3c[1].thc.i3;
    
    if (Norm( c3.c, p1 ) < c3.r + tiny_num && Norm( c3.c, p2 ) < c3.r + tiny_num && Norm( c3.c, p3 ) < c3.r + tiny_num) return c4c.c3c[1].area;
    
    if (Norm( c3.c, p1 ) > c3.r - tiny_num && Norm( c3.c, p2 ) > c3.r - tiny_num && Norm( c3.c, p3 ) > c3.r - tiny_num)
    {
        return c4c.c2c[1].area + c4c.c2c[3].area + c4c.c2c[5].area - 2 * c4c.cc[2].area;
    }
    
    p1 = c4c.c3c[2].thc.i1;
    p2 = c4c.c3c[2].thc.i2;
    p3 = c4c.c3c[2].thc.i3;
    
    if (Norm( c2.c, p1 ) < c2.r + tiny_num && Norm( c2.c, p2 ) < c2.r + tiny_num && Norm( c2.c, p3 ) < c2.r + tiny_num) return c4c.c3c[2].area;
    
    if (Norm( c2.c, p1 ) > c2.r - tiny_num && Norm( c2.c, p2 ) > c2.r - tiny_num && Norm( c2.c, p3 ) > c2.r - tiny_num)
    {
        return c4c.c2c[0].area + c4c.c2c[3].area + c4c.c2c[4].area - 2 * c4c.cc[1].area;
    }
    
    p1 = c4c.c3c[3].thc.i1;
    p2 = c4c.c3c[3].thc.i2;
    p3 = c4c.c3c[3].thc.i3;
    
    if (Norm( c1.c, p1 ) < c1.r + tiny_num && Norm( c1.c, p2 ) < c1.r + tiny_num && Norm( c1.c, p3 ) < c1.r + tiny_num) return c4c.c3c[3].area;
    
    if (Norm( c1.c, p1 ) > c1.r - tiny_num && Norm( c1.c, p2 ) > c1.r - tiny_num && Norm( c1.c, p3 ) > c1.r - tiny_num)
    {
        return c4c.c2c[0].area + c4c.c2c[1].area + c4c.c2c[2].area - 2 * c4c.cc[0].area;
    }
    
    return Non_Trivial_Four_Circle_Intersection_Area_Within_Cell( c4c );
}
