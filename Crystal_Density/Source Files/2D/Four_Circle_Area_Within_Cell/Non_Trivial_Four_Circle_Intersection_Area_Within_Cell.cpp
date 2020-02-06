#include "Pt_Within_Convex_Hull.h"
#include "Non_Trivial_Four_Circle_Intersection_Pts.h"
#include "Non_Trivial_Four_Circle_Intersection_Area.h"
#include "Four_Circle_Intersection_Area_Excluded_By_Exterior_Edge.h"

double Non_Trivial_Four_Circle_Intersection_Area_Within_Cell ( Cell_4Circles& c4c )
{
    Circle c1 = c4c.cc[0].c, c2 = c4c.cc[1].c, c3 = c4c.cc[2].c, c4 = c4c.cc[3].c;
    
    double intersection_area = Non_Trivial_Four_Circle_Intersection_Area( c1, c2, c3, c4 );
    
    c4c.fc.intersection_area = intersection_area;
    
    vector<int> arc_order;
    P2 i1, i2, i3, i4;
    
    Non_Trivial_Four_Circle_Intersection_Pts( c1, c2, c3, c4, i1, i2, i3, i4, arc_order );
    
    c4c.fc.i1 = i1;
    c4c.fc.i2 = i2;
    c4c.fc.i3 = i3;
    c4c.fc.i4 = i4;
    c4c.fc.arc_order = arc_order;
    
    Cell cell_1 = c4c.cc[0].cell, cell_2 = c4c.cc[1].cell, cell_3 = c4c.cc[2].cell, cell_4 = c4c.cc[3].cell;
    
    if (!c4c.cc[0].intersection && !c4c.cc[1].intersection && !c4c.cc[2].intersection && !c4c.cc[3].intersection)
    {
        if (c4c.cc[0].num_vertices_within_circle == 4 && c4c.cc[1].num_vertices_within_circle == 4 && c4c.cc[2].num_vertices_within_circle == 4 && c4c.cc[3].num_vertices_within_circle == 4) return c4c.cell.area;
        
        else if (c4c.cc[0].num_vertices_within_circle == 4 || c4c.cc[1].num_vertices_within_circle == 4 || c4c.cc[2].num_vertices_within_circle == 4 || c4c.cc[3].num_vertices_within_circle == 4) return 0;
        
        else if (c4c.cc[0].centre_within_cell) return intersection_area;
        
        else return 0;
    }
    
    else if (!c4c.cc[0].intersection)
    {
        if (c4c.cc[0].num_vertices_within_circle == 4) return c4c.c3c[3].area;
        
        else if (c4c.cc[0].centre_within_cell) return intersection_area;
        
        else return 0;
    }
    
    else if (!c4c.cc[1].intersection)
    {
        if (c4c.cc[1].num_vertices_within_circle == 4) return c4c.c3c[2].area;
        
        else if (c4c.cc[1].centre_within_cell) return intersection_area;
        
        else return 0;
    }
    
    else if (!c4c.cc[2].intersection)
    {
        if (c4c.cc[2].num_vertices_within_circle == 4) return c4c.c3c[1].area;
        
        else if (c4c.cc[2].centre_within_cell) return intersection_area;
        
        else return 0;
    }
    
    else if (!c4c.cc[3].intersection)
    {
        if (c4c.cc[3].num_vertices_within_circle == 4) return c4c.c3c[0].area;
        
        else if (c4c.cc[3].centre_within_cell) return intersection_area;
        
        else return 0;
    }
    
    else
    {
        int num_vertices_within_all_circles = 0;
        
        for (int counter = 0; counter < c4c.cell.vertices.size(); ++counter)
        {
            if (Norm( c1.c, c4c.cell.vertices[counter] ) < c1.r - tiny_num && Norm( c2.c, c4c.cell.vertices[counter] ) < c2.r - tiny_num && Norm( c3.c, c4c.cell.vertices[counter] ) < c3.r - tiny_num && Norm( c4.c, c4c.cell.vertices[counter] ) < c4.r) ++num_vertices_within_all_circles;
        }
        
        if (num_vertices_within_all_circles == 0)
        {
            double area = intersection_area;
            
            for (int counter = 0; counter < c4c.cell.edges.size(); ++counter)
            {
                area -= Four_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c4c, cell_1.edges[counter], cell_2.edges[counter], cell_3.edges[counter], cell_4.edges[counter] );
            }
            
            if (area == intersection_area)
            {
                V2 v1 = i1 - ORIGIN, v2 = i2 - ORIGIN;
                
                P2 p = ORIGIN + 0.5 * v1 + 0.5 * v2;
                
                if (Pt_Within_Convex_Hull( c4c.cell, p )) return area;
                
                else return 0;
            }
            
            else return area;
        }
        
        else return intersection_area;
    }
}
