#include "Cell_3Circles.h"
#include "Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge.h"

double Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( Cell_3Circles const& c3c, Edge const& e1, Edge const& e2, Edge const& e3 )
{
    double intersection_area = c3c.thc.intersection_area;
    
    P2 i1 = c3c.thc.i1, i2 = c3c.thc.i2, i3 = c3c.thc.i3;
    
    Circle c1 = c3c.thc.c[0], c2 = c3c.thc.c[1], c3 = c3c.thc.c[2];
    
    Cell cell = c3c.cell;
    
    if (squared_distance( e1.line, i1 ) < tiny_num && squared_distance( e1.line, i2 ) < tiny_num)
    {
        if (e3.intersection_type == 3 || e3.intersection_type == 6 || e3.intersection_type == 7)
        {
            double area = Area_Excluded_By_Exterior_Edge( c3, e3, cell );
            
            if (Correct_Side_Of_Cell( cell, e1, i3 )) return area;
            
            else return intersection_area - c3.area + area;
        }
    }
    
    else if (squared_distance( e1.line, i1 ) < tiny_num && squared_distance( e1.line, i3 ) < tiny_num)
    {
        if (e2.intersection_type == 3 || e2.intersection_type == 6 || e2.intersection_type == 7)
        {
            double area = Area_Excluded_By_Exterior_Edge( c2, e2, cell );
            
            if (Correct_Side_Of_Cell( cell, e1, i2 )) return area;
            
            else return intersection_area - c2.area + area;
        }
    }
    
    else if (squared_distance( e1.line, i2 ) < tiny_num && squared_distance( e1.line, i3 ) < tiny_num)
    {
        if (e1.intersection_type == 3 || e1.intersection_type == 6 || e1.intersection_type == 7)
        {
            double area = Area_Excluded_By_Exterior_Edge( c1, e1, cell );
            
            if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
            
            else return intersection_area - c1.area + area;
        }
    }
    
    else if (squared_distance( e1.line, i1 ) < tiny_num)
    {
        if (e2.intersection_type == 3 || e2.intersection_type == 6 || e2.intersection_type == 7)
        {
            if (Norm( e2.i1, c3.c ) < c3.r - tiny_num || Norm( e2.i2, c3.c ) < c3.r - tiny_num)
            {
                double area = Area_Excluded_By_Exterior_Edge( c2, e2, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i2 )) return area;
                
                else return intersection_area - c2.area + area;
            }
        }
        
        if (e3.intersection_type == 3 || e3.intersection_type == 6 || e3.intersection_type == 7)
        {
            if (Norm( e3.i1, c2.c ) < c2.r - tiny_num || Norm( e3.i2, c2.c ) < c2.r - tiny_num)
            {
                double area = Area_Excluded_By_Exterior_Edge( c3, e3, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i3 )) return area;
                
                else return intersection_area - c3.area + area;
            }
        }
        
        if (e1.intersection_type == 2 || e1.intersection_type == 3 || e1.intersection_type == 5 || e1.intersection_type == 6 || e1.intersection_type == 7)
        {
            if ((Norm( e1.i1, c2.c ) < c2.r - tiny_num && Norm( e1.i1, c3.c ) < c3.r - tiny_num) || (Norm( e1.i2, c2.c ) < c2.r - tiny_num && Norm( e1.i2, c3.c ) < c3.r - tiny_num))
            {
                double area = Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c3c.c2c[0], e1, e2 );
                
                if (!Correct_Side_Of_Cell( cell, e1, i3 )) return area;
                
                else return intersection_area - c3c.c2c[0].tc.intersection_area + area;
            }
        }
    }
    
    else if (squared_distance( e1.line, i2 ) < tiny_num)
    {
        if (e1.intersection_type == 3 || e1.intersection_type == 6 || e1.intersection_type == 7)
        {
            if (Norm( e1.i1, c3.c ) < c3.r - tiny_num || Norm( e1.i2, c3.c ) < c3.r - tiny_num)
            {
                double area = Area_Excluded_By_Exterior_Edge( c1, e1, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - c1.area + area;
            }
        }
        
        if (e3.intersection_type == 3 || e3.intersection_type == 6 || e3.intersection_type == 7)
        {
            if (Norm( e3.i1, c1.c ) < c1.r - tiny_num || Norm( e3.i2, c1.c ) < c1.r - tiny_num)
            {
                double area = Area_Excluded_By_Exterior_Edge( c3, e3, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i3 )) return area;
                
                else return intersection_area - c3.area + area;
            }
        }
        
        if (e2.intersection_type == 2 || e2.intersection_type == 3 || e2.intersection_type == 5 || e2.intersection_type == 6 || e2.intersection_type == 7)
        {
            if ((Norm( e2.i1, c1.c ) < c1.r - tiny_num && Norm( e2.i1, c3.c ) < c3.r - tiny_num) || (Norm( e2.i2, c1.c ) < c1.r - tiny_num && Norm( e2.i2, c3.c ) < c3.r - tiny_num))
            {
                double area = Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c3c.c2c[2], e2, e3 );
                
                if (!Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - c3c.c2c[0].tc.intersection_area + area;
            }
        }
    }
    
    else if (squared_distance( e1.line, i3 ) < tiny_num)
    {
        if (e1.intersection_type == 3 || e1.intersection_type == 6 || e1.intersection_type == 7)
        {
            if (Norm( e1.i1, c2.c ) < c2.r - tiny_num || Norm( e1.i2, c2.c ) < c2.r - tiny_num)
            {
                double area = Area_Excluded_By_Exterior_Edge( c1, e1, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - c1.area + area;
            }
        }
        
        if (e2.intersection_type == 3 || e2.intersection_type == 6 || e2.intersection_type == 7)
        {
            if (Norm( e2.i1, c1.c ) < c1.r - tiny_num || Norm( e2.i2, c1.c ) < c1.r - tiny_num)
            {
                double area = Area_Excluded_By_Exterior_Edge( c2, e2, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i2 )) return area;
                
                else return intersection_area - c2.area + area;
            }
        }
        
        if (e3.intersection_type == 2 || e3.intersection_type == 3 || e3.intersection_type == 5 || e3.intersection_type == 6 || e3.intersection_type == 7)
        {
            if ((Norm( e3.i1, c1.c ) < c1.r - tiny_num && Norm( e3.i1, c2.c ) < c2.r - tiny_num) || (Norm( e3.i2, c1.c ) < c1.r - tiny_num && Norm( e3.i2, c2.c ) < c2.r - tiny_num))
            {
                double area = Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c3, e1, e3, cell );
                
                if (!Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - c3c.c2c[1].tc.intersection_area + area;
            }
        }
    }
    
    else
    {
        if (e1.intersection_type == 3 || e1.intersection_type == 6 || e1.intersection_type == 7)
        {
            if (Norm( e1.i1, c2.c ) < c2.r && Norm( e1.i1, c3.c ) < c3.r && Norm( e1.i2, c2.c ) < c2.r && Norm( e1.i2, c3.c ) < c3.r)
            {
                double area = Area_Excluded_By_Exterior_Edge( c1, e1, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - c1.area + area;
            }
        }
        
        if (e2.intersection_type == 3 || e2.intersection_type == 6 || e2.intersection_type == 7)
        {
            if (Norm( e2.i1, c1.c ) < c1.r && Norm( e2.i1, c3.c ) < c3.r && Norm( e2.i2, c1.c ) < c1.r && Norm( e2.i2, c3.c ) < c3.r)
            {
                double area = Area_Excluded_By_Exterior_Edge( c2, e2, cell );
                
                if (Correct_Side_Of_Cell( cell, e2, i2 )) return area;
                
                else return intersection_area - c2.area + area;
            }
        }
        
        if (e3.intersection_type == 3 || e3.intersection_type == 6 || e3.intersection_type == 7)
        {
            if (Norm( e3.i1, c1.c ) < c1.r && Norm( e3.i1, c2.c ) < c2.r && Norm( e3.i2, c1.c ) < c1.r && Norm( e3.i2, c2.c ) < c2.r)
            {
                double area = Area_Excluded_By_Exterior_Edge( c3, e3, cell );
                
                if (Correct_Side_Of_Cell( cell, e3, i3 )) return area;
                
                else return intersection_area - c3.area + area;
            }
        }
        
        if ((e1.intersection_type == 2 || e1.intersection_type == 3 || e1.intersection_type == 5 || e1.intersection_type == 6 || e1.intersection_type == 7) && (e2.intersection_type == 2 || e2.intersection_type == 3 || e2.intersection_type == 5 || e2.intersection_type == 6 || e2.intersection_type == 7))
        {
            if (((Norm( e1.i1, c2.c ) < c2.r - tiny_num && Norm( e1.i1, c3.c ) < c3.r - tiny_num) || (Norm( e1.i2, c2.c ) < c2.r - tiny_num && Norm( e1.i2, c3.c ) < c3.r - tiny_num)) && ((Norm( e2.i1, c1.c ) < c1.r - tiny_num && Norm( e2.i1, c3.c ) < c3.r - tiny_num) || (Norm( e2.i2, c1.c ) < c1.r - tiny_num && Norm( e2.i2, c3.c ) < c3.r - tiny_num)))
            {
                double area = Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c2, e1, e2, cell );
                
                if (!Correct_Side_Of_Cell( cell, e1, i3 )) return area;
                
                else return intersection_area - c3c.c2c[0].tc.intersection_area + area;
            }
        }
        
        if ((e1.intersection_type == 2 || e1.intersection_type == 3 || e1.intersection_type == 5 || e1.intersection_type == 6 || e1.intersection_type == 7) && (e3.intersection_type == 2 || e3.intersection_type == 3 || e3.intersection_type == 5 || e3.intersection_type == 6 || e3.intersection_type == 7))
        {
            if (((Norm( e1.i1, c2.c ) < c2.r - tiny_num && Norm( e1.i1, c3.c ) < c3.r - tiny_num) || (Norm( e1.i2, c2.c ) < c2.r - tiny_num && Norm( e1.i2, c3.c ) < c3.r - tiny_num)) && ((Norm( e3.i1, c1.c ) < c1.r - tiny_num && Norm( e3.i1, c2.c ) < c2.r - tiny_num) || (Norm( e3.i2, c1.c ) < c1.r - tiny_num && Norm( e3.i2, c2.c ) < c2.r - tiny_num)))
            {
                double area = Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c3, e1, e3, cell );
                
                if (!Correct_Side_Of_Cell( cell, e1, i2 )) return area;
                
                else return intersection_area - c3c.c2c[1].tc.intersection_area + area;
            }
        }
        
        if ((e2.intersection_type == 2 || e2.intersection_type == 3 || e2.intersection_type == 5 || e2.intersection_type == 6 || e2.intersection_type == 7) && (e3.intersection_type == 2 || e3.intersection_type == 3 || e3.intersection_type == 5 || e3.intersection_type == 6 || e3.intersection_type == 7))
        {
            if (((Norm( e2.i1, c1.c ) < c1.r - tiny_num && Norm( e2.i1, c3.c ) < c3.r - tiny_num) || (Norm( e2.i2, c1.c ) < c1.r - tiny_num && Norm( e2.i2, c3.c ) < c3.r - tiny_num)) && ((Norm( e3.i1, c1.c ) < c1.r - tiny_num && Norm( e3.i1, c2.c ) < c2.r - tiny_num) || (Norm( e3.i2, c1.c ) < c1.r - tiny_num && Norm( e3.i2, c2.c ) < c2.r - tiny_num)))
            {
                double area = Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c2, c3, e2, e3, cell );
                
                if (!Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - c3c.c2c[2].tc.intersection_area + area;
            }
        }
    }
    
    return 0;
}

