#include "Non_Trivial_Three_Circle_Intersection_Area.h"
#include "Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge.h"
#include "Cell_4Circles.h"

double Four_Circle_Intersection_Area_Excluded_By_Exterior_Edge ( Cell_4Circles const& c4c, Edge const& e1, Edge const& e2, Edge const& e3, Edge const& e4 )
{
    Circle c1 = c4c.cc[0].c, c2 = c4c.cc[1].c, c3 = c4c.cc[2].c, c4 = c4c.cc[3].c;
    
    Cell cell = c4c.cell;
    
    double intersection_area = c4c.fc.intersection_area;
    
    P2 i1 = c4c.fc.i1, i2 = c4c.fc.i2, i3 = c4c.fc.i3, i4 = c4c.fc.i4;
    vector<int> arc_order = c4c.fc.arc_order;
    
    if (squared_distance( e1.line, i1 ) < tiny_num && squared_distance( e1.line, i2 ) < tiny_num)
    {
        if (e1.intersection_type == 3 || e1.intersection_type == 6 || e1.intersection_type == 7)
        {
            double area = Area_Excluded_By_Exterior_Edge( c1, e1, cell );
            
            if (Correct_Side_Of_Cell( cell, e1, i3 )) return area;
            
            else return intersection_area - c1.area + area;
        }
    }
    
    else if (squared_distance( e1.line, i1 ) < tiny_num && squared_distance( e1.line, i3 ) < tiny_num)
    {
        double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c4c.c3c[0], e1, e2, e3 );
        
        if (area > tiny_num)
        {
            if (arc_order[1] == 4)
            {
                if (Correct_Side_Of_Cell( cell, e1, i2 )) return area;
                
                else return intersection_area - c4c.c3c[0].thc.intersection_area + area;
            }
            
            else
            {
                if (Correct_Side_Of_Cell( cell, e1, i4 )) return area;
                
                else return intersection_area - c4c.c3c[0].thc.intersection_area + area;
            }
        }
    }
    
    else if (squared_distance( e1.line, i1 ) < tiny_num && squared_distance( e1.line, i4 ) < tiny_num)
    {
        if (arc_order[3] == 2)
        {
            if (e2.intersection_type == 3 || e2.intersection_type == 6 || e2.intersection_type == 7)
            {
                double area = Area_Excluded_By_Exterior_Edge( c2, e2, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i2 )) return area;
                
                else return intersection_area - c2.area + area;
            }
        }
        
        else
        {
            if (e3.intersection_type == 3 || e3.intersection_type == 6 || e3.intersection_type == 7)
            {
                double area = Area_Excluded_By_Exterior_Edge( c3, e3, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i2 )) return area;
                
                else return intersection_area - c3.area + area;
            }
        }
    }
    
    else if (squared_distance( e1.line, i2 ) < tiny_num && squared_distance( e1.line, i3 ) < tiny_num)
    {
        if (arc_order[1] == 3)
        {
            if (e3.intersection_type == 3 || e3.intersection_type == 6 || e3.intersection_type == 7)
            {
                double area = Area_Excluded_By_Exterior_Edge( c3, e3, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - c3.area + area;
            }
        }
        
        else
        {
            if (e4.intersection_type == 3 || e4.intersection_type == 6 || e4.intersection_type == 7)
            {
                double area = Area_Excluded_By_Exterior_Edge( c4, e4, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - c4.area + area;
            }
        }
    }
    
    else if (squared_distance( e1.line, i2 ) < tiny_num && squared_distance( e1.line, i4 ) < tiny_num)
    {
        double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c4c.c3c[0], e1, e2, e3 );
        
        if (area > tiny_num)
        {
            if (Correct_Side_Of_Cell( cell, e1, i3 )) return area;
            
            else return intersection_area - c4c.c3c[0].thc.intersection_area + area;
        }
    }
    
    else if (squared_distance( e1.line, i3 ) < tiny_num && squared_distance( e1.line, i4 ) < tiny_num)
    {
        if (arc_order[2] == 2)
        {
            if (e2.intersection_type == 3 || e2.intersection_type == 6 || e2.intersection_type == 7)
            {
                double area = Area_Excluded_By_Exterior_Edge( c2, e2, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i2 )) return area;
                
                else return intersection_area - c2.area + area;
            }
        }
        
        else if (arc_order[2] == 3)
        {
            if (e3.intersection_type == 3 || e3.intersection_type == 6 || e3.intersection_type == 7)
            {
                double area = Area_Excluded_By_Exterior_Edge( c3, e3, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i2 )) return area;
                
                else return intersection_area - c3.area + area;
            }
        }
        
        else
        {
            if (e4.intersection_type == 3 || e4.intersection_type == 6 || e4.intersection_type == 7)
            {
                double area = Area_Excluded_By_Exterior_Edge( c4, e4, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i2 )) return area;
                
                else return intersection_area - c4.area + area;
            }
        }
    }
    
    else if (squared_distance( e1.line, i1 ) < tiny_num)
    {
        if (e4.intersection_type > 1)
        {
            if ((Norm( e4.i1, c1.c ) < c1.r - tiny_num && Norm( e4.i1, c2.c ) < c2.r - tiny_num && Norm( e4.i1, c3.c ) < c3.r - tiny_num) || (Norm( e4.i2, c1.c ) < c1.r - tiny_num && Norm( e4.i2, c2.c ) < c2.r - tiny_num && Norm( e4.i2, c3.c ) < c3.r - tiny_num))
            {
                if (arc_order[3] == 2)
                {
                    double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c4c.c3c[1], e1, e2, e4 );
                    
                    if (area > tiny_num)
                    {
                        if (Correct_Side_Of_Cell( cell, e1, i3 )) return area;
                        
                        else return intersection_area - c4c.c3c[1].thc.intersection_area + area;
                    }
                }
                
                else
                {
                    double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c4c.c3c[2], e1, e3, e4 );
                    
                    if (area > tiny_num)
                    {
                        if (Correct_Side_Of_Cell( cell, e1, i3 )) return area;
                        
                        else return intersection_area - c4c.c3c[2].thc.intersection_area + area;
                    }
                }
            }
        }
        
        else
        {
            double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c4c.c3c[0], e1, e2, e3 );
            
            if (area > tiny_num)
            {
                if (Correct_Side_Of_Cell( cell, e1, i3 )) return area;
                
                else return intersection_area - c4c.c3c[0].thc.intersection_area + area;
            }
        }
    }
    
    else if (squared_distance( e1.line, i2 ) < tiny_num)
    {
        if (arc_order[1] == 4)
        {
            if (e2.intersection_type > 1)
            {
                if ((Norm( e2.i1, c1.c ) < c1.r - tiny_num && Norm( e2.i1, c3.c ) < c3.r - tiny_num && Norm( e2.i1, c4.c ) < c4.r - tiny_num) || (Norm( e2.i2, c1.c ) < c1.r - tiny_num && Norm( e2.i2, c3.c ) < c3.r - tiny_num && Norm( e2.i2, c4.c ) < c4.r - tiny_num))
                {
                    double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c4c.c3c[1], e1, e2, e4 );
                    
                    if (area > tiny_num)
                    {
                        if (Correct_Side_Of_Cell( cell, e1, i4 )) return area;
                        
                        else return intersection_area - c4c.c3c[1].thc.intersection_area + area;
                    }
                }
            }
            
            else
            {
                double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c4c.c3c[2], e1, e3, e4 );
                
                if (area > tiny_num)
                {
                    if (Correct_Side_Of_Cell( cell, e1, i4 )) return area;
                    
                    else return intersection_area - c4c.c3c[2].thc.intersection_area + area;
                }
            }
        }
        
        else
        {
            if (e4.intersection_type > 1)
            {
                if ((Norm( e4.i1, c1.c ) < c1.r - tiny_num && Norm( e4.i1, c2.c ) < c2.r - tiny_num && Norm( e4.i1, c3.c ) < c3.r - tiny_num) || (Norm( e4.i2, c1.c ) < c1.r - tiny_num && Norm( e4.i2, c2.c ) < c2.r - tiny_num && Norm( e4.i2, c3.c ) < c3.r - tiny_num))
                {
                    double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c4c.c3c[1], e1, e3, e4 );
                    
                    if (area > tiny_num)
                    {
                        if (Correct_Side_Of_Cell( cell, e1, i4 )) return area;
                        
                        else return intersection_area - c4c.c3c[1].thc.intersection_area + area;
                    }
                }
            }
            
            else
            {
                double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c4c.c3c[0], e1, e2, e3 );
                
                if (area > tiny_num)
                {
                    if (Correct_Side_Of_Cell( cell, e1, i4 )) return area;
                    
                    else return intersection_area - c4c.c3c[0].thc.intersection_area + area;
                }
            }
        }
    }
    
    else if (squared_distance( e1.line, i3 ) < tiny_num)
    {
        if (arc_order[3] == 2)
        {
            if (e2.intersection_type > 1)
            {
                if ((Norm( e2.i1, c1.c ) < c1.r - tiny_num && Norm( e2.i1, c3.c ) < c3.r - tiny_num && Norm( e2.i1, c4.c ) < c4.r - tiny_num) || (Norm( e2.i2, c1.c ) < c1.r - tiny_num && Norm( e2.i2, c3.c ) < c3.r - tiny_num && Norm( e2.i2, c4.c ) < c4.r - tiny_num))
                {
                    double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c4c.c3c[3], e2, e3, e4 );
                    
                    if (area > tiny_num)
                    {
                        if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                        
                        else return intersection_area - c4c.c3c[3].thc.intersection_area + area;
                    }
                }
            }
            
            else
            {
                double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c4c.c3c[2], e1, e3, e4 );
                
                if (area > tiny_num)
                {
                    if (Correct_Side_Of_Cell( cell, e1, i4 )) return area;
                    
                    else return intersection_area - c4c.c3c[2].thc.intersection_area + area;
                }
            }
        }
        
        else
        {
            if (e3.intersection_type > 1)
            {
                if ((Norm( e3.i1, c1.c ) < c1.r - tiny_num && Norm( e3.i1, c2.c ) < c2.r - tiny_num && Norm( e3.i1, c4.c ) < c4.r - tiny_num) || (Norm( e4.i2, c1.c ) < c1.r - tiny_num && Norm( e4.i2, c2.c ) < c2.r - tiny_num && Norm( e4.i2, c4.c ) < c4.r - tiny_num))
                {
                    double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c4c.c3c[3], e2, e3, e4 );
                    
                    if (area > tiny_num)
                    {
                        if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                        
                        else return intersection_area - c4c.c3c[3].thc.intersection_area + area;
                    }
                }
            }
            
            else
            {
                double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c4c.c3c[1], e1, e2, e4 );
                
                if (area > tiny_num)
                {
                    if (Correct_Side_Of_Cell( cell, e1, i4 )) return area;
                    
                    else return intersection_area - c4c.c3c[1].thc.intersection_area + area;
                }
            }
        }
    }
    
    else if (squared_distance( e1.line, i4 ) < tiny_num)
    {
        if (arc_order[1] == 3)
        {
            if (e3.intersection_type > 1)
            {
                if ((Norm( e3.i1, c1.c ) < c1.r - tiny_num && Norm( e3.i1, c2.c ) < c2.r - tiny_num && Norm( e3.i1, c4.c ) < c4.r - tiny_num) || (Norm( e3.i2, c1.c ) < c1.r - tiny_num && Norm( e3.i2, c2.c ) < c2.r - tiny_num && Norm( e3.i2, c4.c ) < c4.r - tiny_num))
                {
                    double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c4c.c3c[3], e2, e3, e4 );
                    
                    if (area > tiny_num)
                    {
                        if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                        
                        else return intersection_area - c4c.c3c[3].thc.intersection_area + area;
                    }
                }
            }
            
            else
            {
                double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c4c.c3c[1], e1, e2, e4 );
                
                if (area > tiny_num)
                {
                    if (Correct_Side_Of_Cell( cell, e1, i2 )) return area;
                    
                    else return intersection_area - c4c.c3c[1].thc.intersection_area + area;
                }
            }
        }
        
        else
        {
            if ((Norm( e4.i1, c1.c ) < c1.r - tiny_num && Norm( e4.i1, c2.c ) < c2.r - tiny_num && Norm( e4.i1, c3.c ) < c3.r - tiny_num) || (Norm( e4.i2, c1.c ) < c1.r - tiny_num && Norm( e4.i2, c2.c ) < c2.r - tiny_num && Norm( e4.i2, c3.c ) < c3.r - tiny_num))
            {
                double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c4c.c3c[3], e2, e3, e4 );
                
                if (area > tiny_num)
                {
                    if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                    
                    else return intersection_area - c4c.c3c[3].thc.intersection_area + area;
                }
            }
            
            else
            {
                double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c4c.c3c[0], e1, e2, e3 );
                
                if (area > tiny_num)
                {
                    if (Correct_Side_Of_Cell( cell, e1, i2 )) return area;
                    
                    else return intersection_area - c4c.c3c[0].thc.intersection_area + area;
                }
            }
        }
    }
    
    else
    {
        vector<int> ints;
        
        if (e1.intersection_type > 1 && ((Norm( e1.i1, c2.c ) < c2.r && Norm( e1.i1, c3.c ) < c3.r && Norm( e1.i1, c4.c ) < c4.r) || (Norm( e1.i2, c2.c ) < c2.r && Norm( e1.i2, c3.c ) < c3.r && Norm( e1.i2, c4.c ) < c4.r)))
        {
            ints.push_back( 1 );
        }
        
        if (e2.intersection_type > 1 && ((Norm( e2.i1, c1.c ) < c1.r && Norm( e2.i1, c3.c ) < c3.r && Norm( e2.i1, c4.c ) < c4.r) || (Norm( e2.i2, c1.c ) < c1.r && Norm( e2.i2, c3.c ) < c3.r && Norm( e2.i2, c4.c ) < c4.r)))
        {
            ints.push_back( 2 );
        }
        
        if (e3.intersection_type > 1 && ((Norm( e3.i1, c1.c ) < c1.r && Norm( e3.i1, c2.c ) < c2.r && Norm( e3.i1, c4.c ) < c4.r) || (Norm( e3.i2, c1.c ) < c1.r && Norm( e3.i2, c2.c ) < c2.r && Norm( e3.i2, c4.c ) < c4.r)))
        {
            ints.push_back( 3 );
        }
        
        if (e4.intersection_type > 1 && ((Norm( e4.i1, c1.c ) < c1.r && Norm( e4.i1, c2.c ) < c2.r && Norm( e4.i1, c3.c ) < c3.r) || (Norm( e4.i2, c1.c ) < c1.r && Norm( e4.i2, c2.c ) < c2.r && Norm( e4.i2, c3.c ) < c3.r)))
        {
            ints.push_back( 4 );
        }
        
        if (ints.size() == 0) return 0;
        
        else if (ints.size() == 1)
        {
            if (ints[0] == 1)
            {
                double area = Area_Excluded_By_Exterior_Edge( c1, e1, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - c1.area + area;
            }
            
            if (ints[0] == 2)
            {
                double area = Area_Excluded_By_Exterior_Edge( c2, e2, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - c2.area + area;
            }
            
            if (ints[0] == 3)
            {
                double area = Area_Excluded_By_Exterior_Edge( c3, e3, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - c3.area + area;
            }
            
            if (ints[0] == 4)
            {
                double area = Area_Excluded_By_Exterior_Edge( c4, e4, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - c4.area + area;
            }
        }
        
        else
        {
            bool adj1_2 = false, adj1_3 = false, adj1_4 = false, adj2_3 = false, adj2_4 = false, adj3_4 = false;
            
            if (arc_order[2] == 2)
            {
                adj1_3 = true;
                adj1_4 = true;
                adj2_3 = true;
                adj2_4 = true;
            }
            
            else if (arc_order[2] == 3)
            {
                adj1_2 = true;
                adj1_4 = true;
                adj2_3 = true;
                adj3_4 = true;
            }
            
            else
            {
                adj1_2 = true;
                adj1_3 = true;
                adj2_4 = true;
                adj3_4 = true;
            }
            
            if (adj1_2 && (ints[0] == 1 || ints[0] == 2) && (ints[1] == 1 || ints[1] == 2))
            {
                double area = Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c4c.c2c[0], e1, e2 );
                
                if (Correct_Side_Of_Cell( cell, e1, i3 )) return area;
                
                else return intersection_area - c4c.c2c[0].tc.intersection_area + area;
            }
            
            else if (adj1_3 && (ints[0] == 1 || ints[0] == 3) && (ints[1] == 1 || ints[1] == 3))
            {
                double area = Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c4c.c2c[1], e1, e3 );
                
                if (Correct_Side_Of_Cell( cell, e1, i3 )) return area;
                
                else return intersection_area - c4c.c2c[1].tc.intersection_area + area;
            }
            
            else if (adj1_4 && (ints[0] == 1 || ints[0] == 4) && (ints[1] == 1 || ints[1] == 4))
            {
                double area = Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c4c.c2c[2], e1, e4 );
                
                if (Correct_Side_Of_Cell( cell, e1, i3 )) return area;
                
                else return intersection_area - c4c.c2c[2].tc.intersection_area + area;
            }
            
            else if (adj2_3 && (ints[0] == 2 || ints[0] == 3) && (ints[1] == 2 || ints[1] == 3))
            {
                double area = Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c4c.c2c[3], e2, e3 );
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - c4c.c2c[3].tc.intersection_area + area;
            }
            
            else if (adj2_4 && (ints[0] == 2 || ints[0] == 4) && (ints[1] == 2 || ints[1] == 4))
            {
                double area = Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c4c.c2c[4], e2, e4 );
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - c4c.c2c[4].tc.intersection_area + area;
            }
            
            else if (adj3_4 && (ints[0] == 3 || ints[0] == 4) && (ints[1] == 3 || ints[1] == 4))
            {
                double area = Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c4c.c2c[5], e3, e4 );
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - c4c.c2c[5].tc.intersection_area + area;
            }
        }
    }
    
    return 0;
}
