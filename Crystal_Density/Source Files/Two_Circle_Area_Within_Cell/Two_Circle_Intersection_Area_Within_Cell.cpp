#include "Circle_Area_Within_Cell.h"
#include "Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge.h"
#include "Two_Circle_Intersection_Irregular_Sector_Area.h"
#include "Two_Circle_Intersection_Interior_Edge_Area.h"
#include "Two_Circle_Intersection_Concave_Cone_Area.h"

double Two_Circle_Intersection_Area_Within_Cell ( Cell& cell, Circle const& c1, Circle const& c2 )
{
    double intersection_area = Two_Circle_Intersection_Area( c1, c2 );
    
    if (intersection_area < 0 + tiny_num) return 0;
    
    P2 i1, i2;
    
    bool non_trivial_intersection = Intersection_Of_Two_Circles( c1, c2, i1, i2 );
    
    if (!non_trivial_intersection)
    {
        Circle min_circle = (c1.r < c2.r) ? c1 : c2;
        
        return Circle_Area_Within_Cell( cell, min_circle );
    }
    
    Cell cell_1 = cell, cell_2 = cell;
    
    bool cell_c1_intersection = Cell_Circle_Intersections( cell_1, c1 );
    bool cell_c2_intersection = Cell_Circle_Intersections( cell_2, c2 );
    
    int num_vertices_within_c1 = Num_Vertices_Within_Circle( cell, c1 );
    int num_vertices_within_c2 = Num_Vertices_Within_Circle( cell, c2 );
    
    bool c1_centre_within_cell = Pt_Within_Convex_Hull( cell, c1.c );
    bool c2_centre_within_cell = Pt_Within_Convex_Hull( cell, c2.c );
    
    if (!cell_c1_intersection && !cell_c2_intersection)
    {
        if (num_vertices_within_c1 == 4 && num_vertices_within_c2 == 4) return cell.area;
        
        else if (num_vertices_within_c1 == 4 || num_vertices_within_c2 == 4) return 0;
        
        else if (c1_centre_within_cell) return intersection_area;
        
        else return 0;
    }
    
    else if (!cell_c1_intersection && cell_c2_intersection)
    {
        if (num_vertices_within_c1 == 4) return Circle_Area_Within_Cell( cell, c2 );
        
        else if (c1_centre_within_cell) return intersection_area;
        
        else return 0;
    }
    
    else if (cell_c1_intersection && !cell_c2_intersection)
    {
        if (num_vertices_within_c2 == 4) return Circle_Area_Within_Cell( cell, c1 );
        
        else if (c2_centre_within_cell) return intersection_area;
        
        else return 0;
    }
    
    else
    {
        int num_vertices_within_both_circles = 0;
        
        for (int counter = 0; counter < cell.vertices.size(); ++counter)
        {
            if (Norm( c1.c, cell.vertices[counter] ) < c1.r - tiny_num && Norm( c2.c, cell.vertices[counter] ) < c2.r - tiny_num) ++num_vertices_within_both_circles;
        }
        
        if (num_vertices_within_both_circles == 0)
        {
            double area = intersection_area;
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                area -= Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c2, cell_1.edges[counter], cell_2.edges[counter], cell );
            }
            
            if (area == intersection_area)
            {
                V2 v1 = i1 - ORIGIN, v2 = i2 - ORIGIN;
                
                P2 p = ORIGIN + 0.5 * v1 + 0.5 * v2;
                
                if (Pt_Within_Convex_Hull( cell, p )) return area;
                
                else return 0;
            }
            
            else return area;
        }
        
        else if (num_vertices_within_both_circles == 1)
        {
            vector<int> key_edges;
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                if ((cell_1.edges[counter].intersection_type == 1 || cell_1.edges[counter].intersection_type == 2 || cell_1.edges[counter].intersection_type == 5) && (cell_2.edges[counter].intersection_type == 1 || cell_2.edges[counter].intersection_type == 2 || cell_2.edges[counter].intersection_type == 5))
                {
                    key_edges.push_back( counter );
                }
            }
            
            double area = Two_Circle_Intersection_Irregular_Sector_Area( c1, c2, cell_1.edges[key_edges[0]], cell_2.edges[key_edges[0]], cell_1.edges[key_edges[1]], cell_2.edges[key_edges[1]] );
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                area -= Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c2, cell_1.edges[counter], cell_2.edges[counter], cell );
            }
            
            return area;
        }
        
        else if (num_vertices_within_both_circles == 2)
        {
            bool type_1_edge = false;
            Edge key_edge;
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                if (cell_1.edges[counter].intersection_type == 1 && cell_2.edges[counter].intersection_type == 1)
                {
                    key_edge = cell.edges[counter];
                    type_1_edge = true;
                }
            }
            
            if (type_1_edge)
            {
                return Two_Circle_Intersection_Interior_Edge_Area( c1, c2, key_edge, cell_1, cell_2 );
            }
            
            else
            {
                double area_1, area_2;
                
                if (Norm( cell.edges[0].startpt, c1.c ) < c1.r - tiny_num && Norm( cell.edges[0].startpt, c2.c ) < c2.r - tiny_num)
                {
                    area_1 = Two_Circle_Intersection_Irregular_Sector_Area( c1, c2, cell_1.edges[0], cell_2.edges[0], cell_1.edges[3], cell_2.edges[3] );
                    
                    area_2 = Two_Circle_Intersection_Irregular_Sector_Area( c1, c2, cell_1.edges[1], cell_2.edges[1], cell_1.edges[2], cell_2.edges[2] );
                }
                
                else
                {
                    area_1 = Two_Circle_Intersection_Irregular_Sector_Area( c1, c2, cell_1.edges[0], cell_2.edges[0], cell_1.edges[1], cell_2.edges[1] );
                    
                    area_2 = Two_Circle_Intersection_Irregular_Sector_Area( c1, c2, cell_1.edges[2], cell_2.edges[2], cell_1.edges[3], cell_2.edges[3] );
                }
                
                return area_1 + area_2 - intersection_area;
            }
        }
        
        else
        {
            vector<int> key_edges;
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                if ((cell_1.edges[counter].intersection_type == 2 && (cell_2.edges[counter].intersection_type == 1 || cell_2.edges[counter].intersection_type == 2 || cell_2.edges[counter].intersection_type == 5)) || (cell_2.edges[counter].intersection_type == 2 && (cell_1.edges[counter].intersection_type == 1 || cell_1.edges[counter].intersection_type == 2 || cell_1.edges[counter].intersection_type == 5)))
                {
                    key_edges.push_back( counter );
                }
            }
            
            if (key_edges.size() == 0) return cell.area;
            
            else
            {
                return cell.area - Two_Circle_Intersection_Concave_Cone_Area( c1, c2, cell_1.edges[key_edges[0]], cell_2.edges[key_edges[0]], cell_1.edges[key_edges[1]], cell_2.edges[key_edges[1]] );
            }
        }
    }
}

double Two_Circle_Intersection_Area_Within_Cell ( Cell_2Circles& c2c )
{
    if (c2c.tc.intersection_area < 0 + tiny_num) return 0;
    
    if (!c2c.tc.non_trivial_intersection) return c2c.cc[0].area;
    
    if (!c2c.cc[0].intersection && !c2c.cc[1].intersection)
    {
        if (c2c.cc[0].num_vertices_within_circle == 4 && c2c.cc[1].num_vertices_within_circle == 4) return c2c.cell.area;
        
        else if (c2c.cc[0].num_vertices_within_circle == 4 || c2c.cc[1].num_vertices_within_circle == 4) return 0;
        
        else if (c2c.cc[0].centre_within_cell) return c2c.tc.intersection_area;
        
        else return 0;
    }
    
    else if (!c2c.cc[0].intersection && c2c.cc[1].intersection)
    {
        if (c2c.cc[0].num_vertices_within_circle == 4) return c2c.cc[1].area;
        
        else if (c2c.cc[0].centre_within_cell) return c2c.tc.intersection_area;
        
        else return 0;
    }
    
    else if (c2c.cc[0].intersection && !c2c.cc[1].intersection)
    {
        if (c2c.cc[1].num_vertices_within_circle == 4) return c2c.cc[0].area;
        
        else if (c2c.cc[1].centre_within_cell) return c2c.tc.intersection_area;
        
        else return 0;
    }
    
    else
    {
        int num_vertices_within_both_circles = 0;
        
        for (int counter = 0; counter < c2c.cell.vertices.size(); ++counter)
        {
            if (Norm( c2c.tc.c[0].c, c2c.cell.vertices[counter] ) < c2c.tc.c[0].r - tiny_num && Norm( c2c.tc.c[1].c, c2c.cell.vertices[counter] ) < c2c.tc.c[1].r - tiny_num) ++num_vertices_within_both_circles;
        }
        
        if (num_vertices_within_both_circles == 0)
        {
            double area = c2c.tc.intersection_area;
            
            for (int counter = 0; counter < c2c.cell.edges.size(); ++counter)
            {
                area -= Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c2c, c2c.cc[0].cell.edges[counter], c2c.cc[1].cell.edges[counter] );
            }
            
            if (area == c2c.tc.intersection_area)
            {
                V2 v1 = c2c.tc.i1 - ORIGIN, v2 = c2c.tc.i2 - ORIGIN;
                
                P2 p = ORIGIN + 0.5 * v1 + 0.5 * v2;
                
                if (Pt_Within_Convex_Hull( c2c.cell, p )) return area;
                
                else return 0;
            }
            
            else return area;
        }
        
        else if (num_vertices_within_both_circles == 1)
        {
            vector<int> key_edges;
            
            for (int counter = 0; counter < c2c.cell.edges.size(); ++counter)
            {
                if ((c2c.cc[0].cell.edges[counter].intersection_type == 1 || c2c.cc[0].cell.edges[counter].intersection_type == 2 || c2c.cc[0].cell.edges[counter].intersection_type == 5) && (c2c.cc[1].cell.edges[counter].intersection_type == 1 || c2c.cc[1].cell.edges[counter].intersection_type == 2 || c2c.cc[1].cell.edges[counter].intersection_type == 5))
                {
                    key_edges.push_back( counter );
                }
            }
            
            double area = Two_Circle_Intersection_Irregular_Sector_Area( c2c, c2c.cc[0].cell.edges[key_edges[0]], c2c.cc[1].cell.edges[key_edges[0]], c2c.cc[0].cell.edges[key_edges[1]], c2c.cc[1].cell.edges[key_edges[1]] );
            
            for (int counter = 0; counter < c2c.cell.edges.size(); ++counter)
            {
                area -= Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c2c, c2c.cc[0].cell.edges[counter], c2c.cc[1].cell.edges[counter] );
            }
            
            return area;
        }
        
        else if (num_vertices_within_both_circles == 2)
        {
            bool type_1_edge = false;
            Edge key_edge;
            
            for (int counter = 0; counter < c2c.cell.edges.size(); ++counter)
            {
                if (c2c.cc[0].cell.edges[counter].intersection_type == 1 && c2c.cc[1].cell.edges[counter].intersection_type == 1)
                {
                    key_edge = c2c.cell.edges[counter];
                    type_1_edge = true;
                }
            }
            
            if (type_1_edge) return Two_Circle_Intersection_Interior_Edge_Area( c2c, key_edge );
            
            else
            {
                double area_1, area_2;
                
                if (Norm( c2c.cell.edges[0].startpt, c2c.tc.c[0].c ) < c2c.tc.c[0].r - tiny_num && Norm( c2c.cell.edges[0].startpt, c2c.tc.c[1].c ) < c2c.tc.c[1].r - tiny_num)
                {
                    area_1 = Two_Circle_Intersection_Irregular_Sector_Area( c2c, c2c.cc[0].cell.edges[0], c2c.cc[1].cell.edges[0], c2c.cc[0].cell.edges[3], c2c.cc[1].cell.edges[3] );
                    
                    area_2 = Two_Circle_Intersection_Irregular_Sector_Area( c2c, c2c.cc[0].cell.edges[1], c2c.cc[1].cell.edges[1], c2c.cc[0].cell.edges[2], c2c.cc[1].cell.edges[2] );
                }
                
                else
                {
                    area_1 = Two_Circle_Intersection_Irregular_Sector_Area( c2c, c2c.cc[0].cell.edges[0], c2c.cc[1].cell.edges[0], c2c.cc[0].cell.edges[1], c2c.cc[1].cell.edges[1] );
                    
                    area_2 = Two_Circle_Intersection_Irregular_Sector_Area( c2c, c2c.cc[0].cell.edges[2], c2c.cc[1].cell.edges[2], c2c.cc[0].cell.edges[3], c2c.cc[1].cell.edges[3] );
                }
                
                return area_1 + area_2 - c2c.tc.intersection_area;
            }
        }
        
        else
        {
            vector<int> key_edges;
            
            for (int counter = 0; counter < c2c.cell.edges.size(); ++counter)
            {
                if ((c2c.cc[0].cell.edges[counter].intersection_type == 2 && (c2c.cc[1].cell.edges[counter].intersection_type == 1 || c2c.cc[1].cell.edges[counter].intersection_type == 2 || c2c.cc[1].cell.edges[counter].intersection_type == 5)) || (c2c.cc[1].cell.edges[counter].intersection_type == 2 && (c2c.cc[0].cell.edges[counter].intersection_type == 1 || c2c.cc[0].cell.edges[counter].intersection_type == 2 || c2c.cc[0].cell.edges[counter].intersection_type == 5)))
                {
                    key_edges.push_back( counter );
                }
            }
            
            if (key_edges.size() == 0) return c2c.cell.area;
            
            else
            {
                return c2c.cell.area - Two_Circle_Intersection_Concave_Cone_Area( c2c, c2c.cc[0].cell.edges[key_edges[0]], c2c.cc[1].cell.edges[key_edges[0]], c2c.cc[0].cell.edges[key_edges[1]], c2c.cc[1].cell.edges[key_edges[1]] );
            }
        }
    }
}
