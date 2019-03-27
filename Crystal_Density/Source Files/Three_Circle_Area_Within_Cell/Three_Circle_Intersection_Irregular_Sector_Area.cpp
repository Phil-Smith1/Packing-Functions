#include "Cell_3Circles.h"
#include "Two_Circle_Intersection_Irregular_Sector_Area.h"

double Three_Circle_Intersection_Irregular_Sector_Area ( Cell_3Circles const& c3c, Edge const& e1, Edge const& e2, Edge const& e3, Edge const& e4, Edge const& e5, Edge const& e6 )
{
    Circle c1 = c3c.cc[0].c, c2 = c3c.cc[1].c, c3 = c3c.cc[2].c;
    
    P2 v, i1, i2;
    
    if (Norm( e1.startpt, c1.c ) < c1.r - tiny_num && Norm( e1.startpt, c2.c ) < c2.r - tiny_num && Norm( e1.startpt, c3.c ) < c3.r - tiny_num)
    {
        v = e1.startpt;
    }
    
    else v = e1.endpt;
    
    int t1, t2;
    
    if (e1.intersection_type != 1 && Norm( e1.i1, c2.c ) < c2.r - tiny_num && Norm( e1.i1, c3.c ) < c3.r - tiny_num)
    {
        i1 = e1.i1;
        t1 = 1;
    }
    
    else if (e2.intersection_type != 1 && Norm( e2.i1, c1.c ) < c1.r - tiny_num && Norm( e2.i1, c3.c ) < c3.r - tiny_num)
    {
        i1 = e2.i1;
        t1 = 2;
    }
    
    else if (e3.intersection_type != 1 && Norm( e3.i1, c1.c ) < c1.r - tiny_num && Norm( e3.i1, c2.c ) < c2.r - tiny_num)
    {
        i1 = e3.i1;
        t1 = 3;
    }
    
    else if (e2.intersection_type != 1 && Norm( e2.i1, c1.c ) < c1.r - tiny_num)
    {
        i1 = e2.i1;
        t1 = 4;
    }
    
    else if (e1.intersection_type != 1 && Norm( e1.i1, c2.c ) < c2.r - tiny_num)
    {
        i1 = e1.i1;
        t1 = 5;
    }
    
    else
    {
        i1 = e1.i1;
        t1 = 6;
    }
    
    if (e4.intersection_type != 1 && Norm( e4.i1, c2.c ) < c2.r - tiny_num && Norm( e4.i1, c3.c ) < c3.r - tiny_num)
    {
        i2 = e4.i1;
        t2 = 1;
    }
    
    else if (e5.intersection_type != 1 && Norm( e5.i1, c1.c ) < c1.r - tiny_num && Norm( e5.i1, c3.c ) < c3.r - tiny_num)
    {
        i2 = e5.i1;
        t2 = 2;
    }
    
    else if (e6.intersection_type != 1 && Norm( e6.i1, c1.c ) < c1.r - tiny_num && Norm( e6.i1, c2.c ) < c2.r - tiny_num)
    {
        i2 = e6.i1;
        t2 = 3;
    }
    
    else if (e5.intersection_type != 1 && Norm( e5.i1, c1.c ) < c1.r - tiny_num)
    {
        i2 = e5.i1;
        t2 = 4;
    }
    
    else if (e4.intersection_type != 1 && Norm( e4.i1, c2.c ) < c2.r - tiny_num)
    {
        i2 = e4.i1;
        t2 = 5;
    }
    
    else
    {
        i2 = e4.i1;
        t2 = 6;
    }
    
    P2 j1 = c3c.thc.i1, j2 = c3c.thc.i2, j3 = c3c.thc.i3;
    
    double intersection_area = c3c.thc.intersection_area;
    
    L2 l( i1, i2 );
    
    if ((t1 == 4 && t2 == 5) || (t1 == 5 && t2 == 4))
    {
        double area = Irregular_Sector_Area( c3, e3, e6 );
        
        if (Same_Side( l, j3, v )) return area;
        
        else return intersection_area - c3.area + area;
    }
    
    else if ((t1 == 4 && t2 == 6) || (t1 == 6 && t2 == 4))
    {
        double area = Irregular_Sector_Area( c2, e2, e5 );
        
        if (Same_Side( l, j2, v )) return area;
        
        else return intersection_area - c2.area + area;
    }
    
    else if ((t1 == 5 && t2 == 6) || (t1 == 6 && t2 == 5))
    {
        double area = Irregular_Sector_Area( c1, e1, e4 );
        
        if (Same_Side( l, j1, v )) return area;
        
        else return intersection_area - c1.area + area;
    }
    
    else if ((t1 == 4 && t2 == 2) || (t1 == 2 && t2 == 4))
    {
        double area = Irregular_Sector_Area( c2, e2, e5 );
        
        if (Same_Side( l, j2, v )) return area;
        
        else return intersection_area - c2.area + area;
    }
    
    else if ((t1 == 4 && t2 == 3) || (t1 == 3 && t2 == 4))
    {
        double area = Irregular_Sector_Area( c3, e3, e6 );
        
        if (Same_Side( l, j3, v )) return area;
        
        else return intersection_area - c3.area + area;
    }
    
    else if ((t1 == 4 && t2 == 1) || (t1 == 1 && t2 == 4))
    {
        double area = Two_Circle_Intersection_Irregular_Sector_Area( c3c.c2c[0], e1, e2, e4, e5 );
        
        if (!Same_Side( l, j3, v )) return area;
        
        else return intersection_area - c3c.c2c[0].tc.intersection_area + area;
    }
    
    else if ((t1 == 5 && t2 == 1) || (t1 == 1 && t2 == 5))
    {
        double area = Irregular_Sector_Area( c1, e1, e4 );
        
        if (Same_Side( l, j1, v )) return area;
        
        else return intersection_area - c1.area + area;
    }
    
    else if ((t1 == 5 && t2 == 3) || (t1 == 3 && t2 == 5))
    {
        double area = Irregular_Sector_Area( c3, e3, e6 );
        
        if (Same_Side( l, j3, v )) return area;
        
        else return intersection_area - c3.area + area;
    }
    
    else if ((t1 == 5 && t2 == 2) || (t1 == 2 && t2 == 5))
    {
        double area = Two_Circle_Intersection_Irregular_Sector_Area( c3c.c2c[2], e1, e2, e4, e5 );
        
        if (!Same_Side( l, j1, v )) return area;
        
        else return intersection_area - c3c.c2c[0].tc.intersection_area + area;
    }
    
    else if ((t1 == 6 && t2 == 1) || (t1 == 1 && t2 == 6))
    {
        double area = Irregular_Sector_Area( c1, e1, e4 );
        
        if (Same_Side( l, j1, v )) return area;
        
        else return intersection_area - c1.area + area;
    }
    
    else if ((t1 == 6 && t2 == 2) || (t1 == 2 && t2 == 6))
    {
        double area = Irregular_Sector_Area( c2, e2, e5 );
        
        if (Same_Side( l, j2, v )) return area;
        
        else return intersection_area - c2.area + area;
    }
    
    else if ((t1 == 6 && t2 == 3) || (t1 == 3 && t2 == 6))
    {
        double area = Two_Circle_Intersection_Irregular_Sector_Area( c3c.c2c[1], e1, e3, e4, e6 );
        
        if (!Same_Side( l, j2, v )) return area;
        
        else return intersection_area - c3c.c2c[1].tc.intersection_area + area;
    }
    
    else if (t1 == t2)
    {
        if (t1 == 1)
        {
            double area = Irregular_Sector_Area( c1, e1, e4 );
            
            if (Same_Side( l, j1, v )) return area;
            
            else return intersection_area - c1.area + area;
        }
        
        else if (t1 == 2)
        {
            double area = Irregular_Sector_Area( c2, e2, e5 );
            
            if (Same_Side( l, j2, v )) return area;
            
            else return intersection_area - c2.area + area;
        }
        
        else
        {
            double area = Irregular_Sector_Area( c3, e3, e6 );
            
            if (Same_Side( l, j3, v )) return area;
            
            else return intersection_area - c3.area + area;
        }
    }
    
    else if ((t1 == 1 && t2 == 2) || (t1 == 2 && t2 == 1))
    {
        double area = Two_Circle_Intersection_Irregular_Sector_Area( c3c.c2c[0], e1, e2, e4, e5 );
        
        if (!Same_Side( l, j3, v )) return area;
        
        else return intersection_area - c3c.c2c[0].tc.intersection_area + area;
    }
    
    else if ((t1 == 1 && t2 == 3) || (t1 == 3 && t2 == 1))
    {
        double area = Two_Circle_Intersection_Irregular_Sector_Area( c3c.c2c[1], e1, e3, e4, e6 );
        
        if (!Same_Side( l, j2, v )) return area;
        
        else return intersection_area - c3c.c2c[1].tc.intersection_area + area;
    }
    
    else
    {
        double area = Two_Circle_Intersection_Irregular_Sector_Area( c3c.c2c[2], e2, e3, e5, e6 );
        
        if (!Same_Side( l, j1, v )) return area;
        
        else return intersection_area - c3c.c2c[2].tc.intersection_area + area;
    }
}
