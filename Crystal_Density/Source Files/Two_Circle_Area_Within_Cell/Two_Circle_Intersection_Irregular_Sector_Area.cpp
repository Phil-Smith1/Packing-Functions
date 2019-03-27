#include "Irregular_Sector_Area.h"
#include "Cell_2Circles.h"

double Two_Circle_Intersection_Irregular_Sector_Area ( Circle const& c1, Circle const& c2, Edge const& e1, Edge const& e2, Edge const& e3, Edge const& e4 )
{
    P2 v, i1, i2, j1, j2;
    
    if (Norm( e1.startpt, c1.c ) < c1.r - tiny_num && Norm( e1.startpt, c2.c ) < c2.r - tiny_num)
    {
        v = e1.startpt;
    }
    
    else v = e1.endpt;
    
    int t1, t2;
    
    if (e1.intersection_type != 1 && Norm( e1.i1, c2.c ) < c2.r - tiny_num)
    {
        i1 = e1.i1;
        t1 = 1;
    }
    
    else if (e2.intersection_type != 1 && Norm( e2.i1, c1.c ) < c1.r - tiny_num)
    {
        i1 = e2.i1;
        t1 = 2;
    }
    
    else
    {
        i1 = e1.i1;
        t1 = 3;
    }
    
    if (e3.intersection_type != 1 && Norm( e3.i1, c2.c ) < c2.r - tiny_num)
    {
        i2 = e3.i1;
        t2 = 1;
    }
    
    else if (e4.intersection_type != 1 && Norm( e4.i1, c1.c ) < c1.r - tiny_num)
    {
        i2 = e4.i1;
        t2 = 2;
    }
    
    else
    {
        i2 = e3.i1;
        t2 = 3;
    }
    
    Intersection_Of_Two_Circles( c1, c2, j1, j2 );
    
    double intersection_area = Two_Circle_Intersection_Area( c1, c2 );
    
    L2 l( i1, i2 );
    
    if (t1 == 3)
    {
        if (t2 == 3)
        {
            double area_1, area_2;
            
            area_1 = Irregular_Sector_Area( c1, e1, e3 );
            area_2 = Irregular_Sector_Area( c2, e2, e4 );
            
            return (area_1 < area_2) ? area_1 : area_2;
        }
        
        else if (t2 == 1)
        {
            double area = Irregular_Sector_Area( c1, e1, e3 );
            
            int t3;
            
            if (Norm( e1.i1, j1 ) < tiny_num) t3 = 1;
            else t3 = 2;
            
            if (t3 == 1)
            {
                if (Same_Side( l, j2, v )) return area;
                
                else return intersection_area - c1.area + area;
            }
            
            else
            {
                if (Same_Side( l, j1, v )) return area;
                
                else return intersection_area - c1.area + area;
            }
        }
        
        else
        {
            double area = Irregular_Sector_Area( c2, e2, e4 );
            
            int t3;
            
            if (Norm( e2.i1, j1 ) < tiny_num) t3 = 1;
            else t3 = 2;
            
            if (t3 == 1)
            {
                if (Same_Side( l, j2, v )) return area;
                
                else return intersection_area - c2.area + area;
            }
            
            else
            {
                if (Same_Side( l, j1, v )) return area;
                
                else return intersection_area - c2.area + area;
            }
        }
    }
    
    else if (t2 == 3)
    {
        if (t1 == 1)
        {
            double area = Irregular_Sector_Area( c1, e1, e3 );
            
            int t3;
            
            if (Norm( e3.i1, j1 ) < tiny_num) t3 = 1;
            else t3 = 2;
            
            if (t3 == 1)
            {
                if (Same_Side( l, j2, v )) return area;
                
                else return intersection_area - c1.area + area;
            }
            
            else
            {
                if (Same_Side( l, j1, v )) return area;
                
                else return intersection_area - c1.area + area;
            }
        }
        
        else
        {
            double area = Irregular_Sector_Area( c2, e2, e4 );
            
            int t3;
            
            if (Norm( e4.i1, j1 ) < tiny_num) t3 = 1;
            else t3 = 2;
            
            if (t3 == 1)
            {
                if (Same_Side( l, j2, v )) return area;
                
                else return intersection_area - c2.area + area;
            }
            
            else
            {
                if (Same_Side( l, j1, v )) return area;
                
                else return intersection_area - c2.area + area;
            }
        }
    }
    
    else if (t1 == t2)
    {
        if (t1 == 1)
        {
            double area = Irregular_Sector_Area( c1, e1, e3 );
            
            if (Same_Side( l, j1, v )) return area;
            
            else return intersection_area - c1.area + area;
        }
        
        else
        {
            double area = Irregular_Sector_Area( c2, e2, e4 );
            
            if (Same_Side( l, j1, v )) return area;
            
            else return intersection_area - c2.area + area;
        }
    }
    
    else
    {
        if (t1 == 2)
        {
            P2 p = i1;
            i1 = i2;
            i2 = p;
        }
        
        double triangle_area_1 = Triangle_Area( v, i1, i2 );
        
        P2 i3;
        
        if (!Same_Side( l, j1, v )) i3 = j1;
        else i3 = j2;
        
        double triangle_area_2 = Triangle_Area( i1, i2, i3 );
        double segment_area_1 = Segment_Area( c1, i1, i3 );
        
        L2 l1( i1, i3 );
        
        if (!Same_Side( l1, c1.c, v )) segment_area_1 = c1.area - segment_area_1;
        
        double segment_area_2 = Segment_Area( c2, i2, i3 );
        
        L2 l2( i2, i3 );
        
        if (!Same_Side( l2, c2.c, v )) segment_area_2 = c2.area - segment_area_2;
        
        return triangle_area_1 + triangle_area_2 + segment_area_1 + segment_area_2;
    }
}


double Two_Circle_Intersection_Irregular_Sector_Area ( Cell_2Circles const& c2c, Edge const& e1, Edge const& e2, Edge const& e3, Edge const& e4 )
{
    Circle c1 = c2c.tc.c[0], c2 = c2c.tc.c[1];
    P2 v, i1, i2;
    
    if (Norm( e1.startpt, c1.c ) < c1.r - tiny_num && Norm( e1.startpt, c2.c ) < c2.r - tiny_num)
    {
        v = e1.startpt;
    }
    
    else v = e1.endpt;
    
    int t1, t2;
    
    if (e1.intersection_type != 1 && Norm( e1.i1, c2.c ) < c2.r - tiny_num)
    {
        i1 = e1.i1;
        t1 = 1;
    }
    
    else if (e2.intersection_type != 1 && Norm( e2.i1, c1.c ) < c1.r - tiny_num)
    {
        i1 = e2.i1;
        t1 = 2;
    }
    
    else
    {
        i1 = e1.i1;
        t1 = 3;
    }
    
    if (e3.intersection_type != 1 && Norm( e3.i1, c2.c ) < c2.r - tiny_num)
    {
        i2 = e3.i1;
        t2 = 1;
    }
    
    else if (e4.intersection_type != 1 && Norm( e4.i1, c1.c ) < c1.r - tiny_num)
    {
        i2 = e4.i1;
        t2 = 2;
    }
    
    else
    {
        i2 = e3.i1;
        t2 = 3;
    }
    
    double intersection_area = c2c.tc.intersection_area;
    P2 j1 = c2c.tc.i1, j2 = c2c.tc.i2;
    
    L2 l( i1, i2 );
    
    if (t1 == 3)
    {
        if (t2 == 3)
        {
            double area_1, area_2;
            
            area_1 = Irregular_Sector_Area( c1, e1, e3 );
            area_2 = Irregular_Sector_Area( c2, e2, e4 );
            
            return (area_1 < area_2) ? area_1 : area_2;
        }
        
        else if (t2 == 1)
        {
            double area = Irregular_Sector_Area( c1, e1, e3 );
            
            int t3;
            
            if (Norm( e1.i1, j1 ) < tiny_num) t3 = 1;
            else t3 = 2;
            
            if (t3 == 1)
            {
                if (Same_Side( l, j2, v )) return area;
                
                else return intersection_area - c1.area + area;
            }
            
            else
            {
                if (Same_Side( l, j1, v )) return area;
                
                else return intersection_area - c1.area + area;
            }
        }
        
        else
        {
            double area = Irregular_Sector_Area( c2, e2, e4 );
            
            int t3;
            
            if (Norm( e2.i1, j1 ) < tiny_num) t3 = 1;
            else t3 = 2;
            
            if (t3 == 1)
            {
                if (Same_Side( l, j2, v )) return area;
                
                else return intersection_area - c2.area + area;
            }
            
            else
            {
                if (Same_Side( l, j1, v )) return area;
                
                else return intersection_area - c2.area + area;
            }
        }
    }
    
    else if (t2 == 3)
    {
        if (t1 == 1)
        {
            double area = Irregular_Sector_Area( c1, e1, e3 );
            
            int t3;
            
            if (Norm( e3.i1, j1 ) < tiny_num) t3 = 1;
            else t3 = 2;
            
            if (t3 == 1)
            {
                if (Same_Side( l, j2, v )) return area;
                
                else return intersection_area - c1.area + area;
            }
            
            else
            {
                if (Same_Side( l, j1, v )) return area;
                
                else return intersection_area - c1.area + area;
            }
        }
        
        else
        {
            double area = Irregular_Sector_Area( c2, e2, e4 );
            
            int t3;
            
            if (Norm( e4.i1, j1 ) < tiny_num) t3 = 1;
            else t3 = 2;
            
            if (t3 == 1)
            {
                if (Same_Side( l, j2, v )) return area;
                
                else return intersection_area - c2.area + area;
            }
            
            else
            {
                if (Same_Side( l, j1, v )) return area;
                
                else return intersection_area - c2.area + area;
            }
        }
    }
    
    else if (t1 == t2)
    {
        if (t1 == 1)
        {
            double area = Irregular_Sector_Area( c1, e1, e3 );
            
            if (Same_Side( l, j1, v )) return area;
            
            else return intersection_area - c1.area + area;
        }
        
        else
        {
            double area = Irregular_Sector_Area( c2, e2, e4 );
            
            if (Same_Side( l, j1, v )) return area;
            
            else return intersection_area - c1.area + area;
        }
    }
    
    else
    {
        if (t1 == 2)
        {
            P2 p = i1;
            i1 = i2;
            i2 = p;
        }
        
        double triangle_area_1 = Triangle_Area( v, i1, i2 );
        
        P2 i3;
        
        if (!Same_Side( l, j1, v )) i3 = j1;
        else i3 = j2;
        
        double triangle_area_2 = Triangle_Area( i1, i2, i3 );
        double segment_area_1 = Segment_Area( c1, i1, i3 );
        
        L2 l1( i1, i3 );
        
        if (!Same_Side( l1, c1.c, v )) segment_area_1 = c1.area - segment_area_1;
        
        double segment_area_2 = Segment_Area( c2, i2, i3 );
        
        L2 l2( i2, i3 );
        
        if (!Same_Side( l2, c2.c, v )) segment_area_2 = c2.area - segment_area_2;
        
        return triangle_area_1 + triangle_area_2 + segment_area_1 + segment_area_2;
    }
}
