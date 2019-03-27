#include "Three_Circle_Intersection_Area_Within_Cell.h"
#include "Non_Trivial_Three_Circle_Intersection_Pts.h"
#include "Non_Trivial_Four_Circle_Intersection_Area_Within_Cell.h"

/*double Non_Inclusion_Four_Circle_Intersection_Area_Within_Cell ( Cell& cell, Circle const& c1, Circle const& c2, Circle const& c3, Circle const& c4 )
{
    P2 p1, p2, p3;
    
    Intersection_Of_Two_Circles( c1, c2, p1, p2 );
    
    if (Norm( c3.c, p1 ) < c3.r + tiny_num && Norm( c3.c, p2 ) < c3.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c2, c4 );
    
    else if (Norm( c4.c, p1 ) < c4.r + tiny_num && Norm( c4.c, p2 ) < c4.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c2, c3 );
    
    Intersection_Of_Two_Circles( c1, c3, p1, p2 );
    
    if (Norm( c2.c, p1 ) < c2.r + tiny_num && Norm( c2.c, p2 ) < c2.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c3, c4 );
    
    else if (Norm( c4.c, p1 ) < c4.r + tiny_num && Norm( c4.c, p2 ) < c4.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c2, c3 );
    
    Intersection_Of_Two_Circles( c1, c4, p1, p2 );
    
    if (Norm( c2.c, p1 ) < c2.r + tiny_num && Norm( c2.c, p2 ) < c2.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c3, c4 );
    
    else if (Norm( c3.c, p1 ) < c3.r + tiny_num && Norm( c3.c, p2 ) < c3.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c2, c4 );
    
    Intersection_Of_Two_Circles( c2, c3, p1, p2 );
    
    if (Norm( c1.c, p1 ) < c1.r + tiny_num && Norm( c1.c, p2 ) < c1.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c2, c3, c4 );
    
    else if (Norm( c4.c, p1 ) < c4.r + tiny_num && Norm( c4.c, p2 ) < c4.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c2, c3 );
    
    Intersection_Of_Two_Circles( c2, c4, p1, p2 );
    
    if (Norm( c1.c, p1 ) < c1.r + tiny_num && Norm( c1.c, p2 ) < c1.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c2, c3, c4 );
    
    else if (Norm( c3.c, p1 ) < c3.r + tiny_num && Norm( c3.c, p2 ) < c3.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c2, c4 );
    
    Intersection_Of_Two_Circles( c3, c4, p1, p2 );
    
    if (Norm( c1.c, p1 ) < c1.r + tiny_num && Norm( c1.c, p2 ) < c1.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c2, c3, c4 );
    
    else if (Norm( c2.c, p1 ) < c2.r + tiny_num && Norm( c2.c, p2 ) < c2.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c3, c4 );
    
    Non_Trivial_Three_Circle_Intersection_Pts( c1, c2, c3, p1, p2, p3 );
    
    if (Norm( c4.c, p1 ) < c4.r + tiny_num && Norm( c4.c, p2 ) < c4.r + tiny_num && Norm( c4.c, p3 ) < c4.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c2, c3 );
    
    if (Norm( c4.c, p1 ) > c4.r - tiny_num && Norm( c4.c, p2 ) > c4.r - tiny_num && Norm( c4.c, p3 ) > c4.r - tiny_num)
    {
        double area_1, area_2, area_3;
        
        area_1 = Two_Circle_Intersection_Area_Within_Cell( cell, c1, c4 );
        area_2 = Two_Circle_Intersection_Area_Within_Cell( cell, c2, c4 );
        area_3 = Two_Circle_Intersection_Area_Within_Cell( cell, c3, c4 );
        
        return area_1 + area_2 + area_3 - 2 * Circle_Area_Within_Cell( cell, c4 );
    }
    
    Non_Trivial_Three_Circle_Intersection_Pts( c1, c2, c4, p1, p2, p3 );
    
    if (Norm( c3.c, p1 ) < c3.r + tiny_num && Norm( c3.c, p2 ) < c3.r + tiny_num && Norm( c3.c, p3 ) < c3.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c2, c4 );
    
    if (Norm( c3.c, p1 ) > c3.r - tiny_num && Norm( c3.c, p2 ) > c3.r - tiny_num && Norm( c3.c, p3 ) > c3.r - tiny_num)
    {
        double area_1, area_2, area_3;
        
        area_1 = Two_Circle_Intersection_Area_Within_Cell( cell, c1, c3 );
        area_2 = Two_Circle_Intersection_Area_Within_Cell( cell, c2, c3 );
        area_3 = Two_Circle_Intersection_Area_Within_Cell( cell, c3, c4 );
        
        return area_1 + area_2 + area_3 - 2 * Circle_Area_Within_Cell( cell, c3 );
    }
    
    Non_Trivial_Three_Circle_Intersection_Pts( c1, c3, c4, p1, p2, p3 );
    
    if (Norm( c2.c, p1 ) < c2.r + tiny_num && Norm( c2.c, p2 ) < c2.r + tiny_num && Norm( c2.c, p3 ) < c2.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c3, c4 );
    
    if (Norm( c2.c, p1 ) > c2.r - tiny_num && Norm( c2.c, p2 ) > c2.r - tiny_num && Norm( c2.c, p3 ) > c2.r - tiny_num)
    {
        double area_1, area_2, area_3;
        
        area_1 = Two_Circle_Intersection_Area_Within_Cell( cell, c1, c2 );
        area_2 = Two_Circle_Intersection_Area_Within_Cell( cell, c2, c3 );
        area_3 = Two_Circle_Intersection_Area_Within_Cell( cell, c2, c4 );
        
        return area_1 + area_2 + area_3 - 2 * Circle_Area_Within_Cell( cell, c2 );
    }
    
    Non_Trivial_Three_Circle_Intersection_Pts( c2, c3, c4, p1, p2, p3 );
    
    if (Norm( c1.c, p1 ) < c1.r + tiny_num && Norm( c1.c, p2 ) < c1.r + tiny_num && Norm( c1.c, p3 ) < c1.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c2, c3, c4 );
    
    if (Norm( c1.c, p1 ) > c1.r - tiny_num && Norm( c1.c, p2 ) > c1.r - tiny_num && Norm( c1.c, p3 ) > c1.r - tiny_num)
    {
        double area_1, area_2, area_3;
        
        area_1 = Two_Circle_Intersection_Area_Within_Cell( cell, c1, c2 );
        area_2 = Two_Circle_Intersection_Area_Within_Cell( cell, c1, c3 );
        area_3 = Two_Circle_Intersection_Area_Within_Cell( cell, c1, c4 );
        
        return area_1 + area_2 + area_3 - 2 * Circle_Area_Within_Cell( cell, c1 );
    }
    
    return Non_Trivial_Four_Circle_Intersection_Area_Within_Cell( cell, c1, c2, c3, c4 );
}*/

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
