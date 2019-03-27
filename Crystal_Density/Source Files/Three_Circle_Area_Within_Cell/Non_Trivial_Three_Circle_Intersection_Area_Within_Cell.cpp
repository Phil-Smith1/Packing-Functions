#include "Cell_3Circles.h"
#include "Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge.h"
#include "Three_Circle_Intersection_Irregular_Sector_Area.h"
#include "Three_Circle_Intersection_Interior_Edge_Area.h"
#include "Three_Circle_Intersection_Concave_Cone_Area.h"

double Non_Trivial_Three_Circle_Intersection_Area_Within_Cell ( Cell_3Circles& c3c )
{
    if (!c3c.cc[0].intersection && !c3c.cc[1].intersection && !c3c.cc[2].intersection)
    {
        if (c3c.cc[0].num_vertices_within_circle == 4 && c3c.cc[1].num_vertices_within_circle == 4 && c3c.cc[2].num_vertices_within_circle) return c3c.cell.area;
        
        else if (c3c.cc[0].num_vertices_within_circle == 4 || c3c.cc[1].num_vertices_within_circle == 4 || c3c.cc[2].num_vertices_within_circle == 4) return 0;
        
        else if (c3c.cc[0].centre_within_cell) return c3c.thc.intersection_area;
        
        else return 0;
    }
    
    else if (!c3c.cc[0].intersection)
    {
        if (c3c.cc[0].num_vertices_within_circle == 4) return c3c.c2c[2].area;
        
        else if (c3c.cc[0].centre_within_cell) return c3c.thc.intersection_area;
        
        else return 0;
    }
    
    else if (!c3c.cc[1].intersection)
    {
        if (c3c.cc[1].num_vertices_within_circle == 4) return c3c.c2c[1].area;
        
        else if (c3c.cc[1].centre_within_cell) return c3c.thc.intersection_area;
        
        else return 0;
    }
    
    else if (!c3c.cc[2].intersection)
    {
        if (c3c.cc[2].num_vertices_within_circle == 4) return c3c.c2c[0].area;
        
        else if (c3c.cc[2].centre_within_cell) return c3c.thc.intersection_area;
        
        else return 0;
    }
    
    else
    {
        int num_vertices_within_all_circles = 0;
        
        for (int counter = 0; counter < c3c.cell.vertices.size(); ++counter)
        {
            if (Norm( c3c.thc.c[0].c, c3c.cell.vertices[counter] ) < c3c.thc.c[0].r - tiny_num && Norm( c3c.thc.c[1].c, c3c.cell.vertices[counter] ) < c3c.thc.c[1].r - tiny_num && Norm( c3c.thc.c[2].c, c3c.cell.vertices[counter] ) < c3c.thc.c[2].r - tiny_num) ++num_vertices_within_all_circles;
        }
        
        if (num_vertices_within_all_circles == 0)
        {
            double area = c3c.thc.intersection_area;
            
            for (int counter = 0; counter < c3c.cell.edges.size(); ++counter)
            {
                area -= Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c3c, c3c.cc[0].cell.edges[counter], c3c.cc[1].cell.edges[counter], c3c.cc[2].cell.edges[counter] );
            }
            
            if (area == c3c.thc.intersection_area)
            {
                V2 v1 = c3c.thc.i1 - ORIGIN, v2 = c3c.thc.i2 - ORIGIN;
                
                P2 p = ORIGIN + 0.5 * v1 + 0.5 * v2;
                
                if (Pt_Within_Convex_Hull( c3c.cell, p )) return area;
                
                else return 0;
            }
            
            else return area;
        }
        
        else if (num_vertices_within_all_circles == 1)
        {
            vector<int> key_edges;
            
            for (int counter = 0; counter < c3c.cell.edges.size(); ++counter)
            {
                if ((Norm( c3c.cc[0].cell.edges[counter].startpt, c3c.thc.c[0].c) < c3c.thc.c[0].r - tiny_num && Norm( c3c.cc[0].cell.edges[counter].startpt, c3c.thc.c[1].c) < c3c.thc.c[1].r - tiny_num && Norm( c3c.cc[0].cell.edges[counter].startpt, c3c.thc.c[2].c) < c3c.thc.c[2].r - tiny_num) || (Norm( c3c.cc[0].cell.edges[counter].endpt, c3c.thc.c[0].c) < c3c.thc.c[0].r - tiny_num && Norm( c3c.cc[0].cell.edges[counter].endpt, c3c.thc.c[1].c) < c3c.thc.c[1].r - tiny_num && Norm( c3c.cc[0].cell.edges[counter].endpt, c3c.thc.c[2].c) < c3c.thc.c[2].r - tiny_num))
                {
                    key_edges.push_back( counter );
                }
            }
            
            double area = Three_Circle_Intersection_Irregular_Sector_Area( c3c, c3c.cc[0].cell.edges[key_edges[0]], c3c.cc[1].cell.edges[key_edges[0]], c3c.cc[2].cell.edges[key_edges[0]], c3c.cc[0].cell.edges[key_edges[1]], c3c.cc[1].cell.edges[key_edges[1]], c3c.cc[2].cell.edges[key_edges[1]] );
            
            for (int counter = 0; counter < c3c.cell.edges.size(); ++counter)
            {
                area -= Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c3c, c3c.cc[0].cell.edges[counter], c3c.cc[1].cell.edges[counter], c3c.cc[2].cell.edges[counter] );
            }
            
            return area;
        }
        
        else if (num_vertices_within_all_circles == 2)
        {
            bool type_1_edge = false;
            Edge key_edge;
            
            for (int counter = 0; counter < c3c.cell.edges.size(); ++counter)
            {
                if (c3c.cc[0].cell.edges[counter].intersection_type == 1 && c3c.cc[1].cell.edges[counter].intersection_type == 1 && c3c.cc[2].cell.edges[counter].intersection_type == 1)
                {
                    key_edge = c3c.cell.edges[counter];
                    type_1_edge = true;
                }
            }
            
            if (type_1_edge) return Three_Circle_Intersection_Interior_Edge_Area( c3c, key_edge );
            
            else
            {
                double area_1, area_2;
                
                if (Norm( c3c.cell.edges[0].startpt, c3c.thc.c[0].c ) < c3c.thc.c[0].r - tiny_num && Norm( c3c.cell.edges[0].startpt, c3c.thc.c[1].c ) < c3c.thc.c[1].r - tiny_num && Norm( c3c.cell.edges[0].startpt, c3c.thc.c[2].c ) < c3c.thc.c[2].r - tiny_num)
                {
                    area_1 = Three_Circle_Intersection_Irregular_Sector_Area( c3c, c3c.cc[0].cell.edges[0], c3c.cc[1].cell.edges[0], c3c.cc[2].cell.edges[0], c3c.cc[0].cell.edges[3], c3c.cc[1].cell.edges[3], c3c.cc[2].cell.edges[3] );
                    
                    area_2 = Three_Circle_Intersection_Irregular_Sector_Area( c3c, c3c.cc[0].cell.edges[1], c3c.cc[1].cell.edges[1], c3c.cc[2].cell.edges[1], c3c.cc[0].cell.edges[2], c3c.cc[1].cell.edges[2], c3c.cc[2].cell.edges[2] );
                }
                
                else
                {
                    area_1 = Three_Circle_Intersection_Irregular_Sector_Area( c3c, c3c.cc[0].cell.edges[0], c3c.cc[1].cell.edges[0], c3c.cc[2].cell.edges[0], c3c.cc[0].cell.edges[1], c3c.cc[1].cell.edges[1], c3c.cc[2].cell.edges[1] );
                    
                    area_2 = Three_Circle_Intersection_Irregular_Sector_Area( c3c, c3c.cc[0].cell.edges[2], c3c.cc[1].cell.edges[2], c3c.cc[2].cell.edges[2], c3c.cc[0].cell.edges[3], c3c.cc[1].cell.edges[3], c3c.cc[2].cell.edges[3] );
                }
                
                return area_1 + area_2 - c3c.thc.intersection_area;
            }
        }
        
        else
        {
            vector<int> key_edges;
            
            for (int counter = 0; counter < c3c.cell.edges.size(); ++counter)
            {
                if (!(Norm( c3c.cell.edges[counter].startpt, c3c.thc.c[0].c ) < c3c.thc.c[0].r + tiny_num && Norm( c3c.cell.edges[counter].startpt, c3c.thc.c[1].c ) < c3c.thc.c[1].r + tiny_num && Norm( c3c.cell.edges[counter].startpt, c3c.thc.c[2].c ) < c3c.thc.c[2].r + tiny_num) || !(Norm( c3c.cell.edges[counter].endpt, c3c.thc.c[0].c ) < c3c.thc.c[0].r + tiny_num && Norm( c3c.cell.edges[counter].endpt, c3c.thc.c[1].c ) < c3c.thc.c[1].r + tiny_num && Norm( c3c.cell.edges[counter].endpt, c3c.thc.c[2].c ) < c3c.thc.c[2].r + tiny_num))
                {
                    key_edges.push_back( counter );
                }
            }
            
            if (key_edges.size() == 0) return c3c.cell.area;
            
            else
            {
                return c3c.cell.area - Three_Circle_Intersection_Concave_Cone_Area( c3c, c3c.cc[0].cell.edges[key_edges[0]], c3c.cc[1].cell.edges[key_edges[0]], c3c.cc[2].cell.edges[key_edges[0]], c3c.cc[0].cell.edges[key_edges[1]], c3c.cc[1].cell.edges[key_edges[1]], c3c.cc[2].cell.edges[key_edges[1]] );
            }
        }
    }
}
