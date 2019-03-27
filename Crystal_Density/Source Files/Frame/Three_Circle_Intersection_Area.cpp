#include "Three_Circles.h"

double Three_Circles::Three_Circle_Intersection_Area ()
{
    if (tc[0].intersection_area < tiny_num || tc[1].intersection_area < tiny_num || tc[2].intersection_area < tiny_num) return 0;
    
    else
    {
        bool inside0_1 = false, inside0_2 = false, inside1_2 = false;
        
        if (Norm( c[0].c, c[1].c ) < c[1].r - c[0].r ) inside0_1 = true;
        if (Norm( c[0].c, c[2].c ) < c[2].r - c[0].r ) inside0_2 = true;
        if (Norm( c[1].c, c[2].c ) < c[2].r - c[1].r ) inside1_2 = true;
        
        if (inside0_1 && inside0_2 && inside1_2) return c[0].area;
        
        else if (!inside0_1 && inside0_2 && inside1_2) return tc[2].intersection_area;
        
        else if (inside0_1 && inside0_2 && !inside1_2) return c[0].area;
        
        else if (inside0_1 && !inside0_2 && !inside1_2) return tc[1].intersection_area;
        
        else if (!inside0_1 && inside0_2 && !inside1_2) return tc[2].intersection_area;
        
        else if (!inside0_1 && !inside0_2 && inside1_2) return tc[2].intersection_area;
        
        else
        {
            non_inclusion_intersection = true;
            
            int j = 0, k = 0, l = 0;
            
            if (Norm( c[2].c, tc[2].i1 ) < c[2].r + tiny_num) ++j;
            if (Norm( c[2].c, tc[2].i2 ) < c[2].r + tiny_num) ++j;
            
            if (Norm( c[1].c, tc[1].i1 ) < c[1].r + tiny_num) ++k;
            if (Norm( c[1].c, tc[1].i2 ) < c[1].r + tiny_num) ++k;
            
            if (Norm( c[0].c, tc[0].i1 ) < c[0].r + tiny_num) ++l;
            if (Norm( c[0].c, tc[0].i2 ) < c[0].r + tiny_num) ++l;
            
            if (j == 1 && k == 1 && l == 1)
            {
                non_trivial_intersection = true;
                
                if (Norm( c[0].c, tc[0].i1 ) < c[0].r) i1 = tc[0].i1;
                
                else if (Norm( c[0].c, tc[0].i2 ) < c[0].r) i1 = tc[0].i2;
                
                if (Norm( c[1].c, tc[1].i1 ) < c[1].r) i2 = tc[1].i1;
                
                else if (Norm( c[1].c, tc[1].i2 ) < c[1].r) i2 = tc[1].i2;
                
                if (Norm( c[2].c, tc[2].i1 ) < c[2].r) i3 = tc[2].i1;
                
                else if (Norm( c[2].c, tc[2].i2 ) < c[2].r) i3 = tc[2].i2;
                
                double triangle_area = Triangle_Area( i1, i2, i3 );
                
                double segment_area_1 = Segment_Area( c[0], i2, i3 );
                double segment_area_2 = Segment_Area( c[1], i1, i3 );
                double segment_area_3 = Segment_Area( c[2], i1, i2 );
                
                return triangle_area + segment_area_1 + segment_area_2 + segment_area_3;
            }
            
            else if (j == 0 && k == 0 && l == 0) return 0;
            
            else
            {
                int d = 0;
                
                if (j == 2) ++d;
                if (k == 2) ++d;
                if (l == 2) ++d;
                
                if (d == 1)
                {
                    if (j == 2) return tc[2].intersection_area;
                    else if (k == 2) return tc[1].intersection_area;
                    else return tc[0].intersection_area;
                }
                
                else
                {
                    double a, b;
                    
                    a = tc[2].intersection_area;
                    b = tc[1].intersection_area;
                    
                    return a + b - c[0].area;
                }
            }
        }
    }
}
