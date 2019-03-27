#include "Cell_3Circles.h"
#include "Two_Circle_Intersection_Area_Within_Cell.h"
#include "Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge.h"
#include "Three_Circle_Intersection_Irregular_Sector_Area.h"
#include "Three_Circle_Intersection_Interior_Edge_Area.h"
#include "Three_Circle_Intersection_Concave_Cone_Area.h"

double Non_Trivial_Three_Circle_Intersection_Area_Within_Cell ( Cell& cell, Circle const& c1, Circle const& c2, Circle const& c3 )
{
    double intersection_area = Non_Trivial_Three_Circle_Intersection_Area( c1, c2, c3 );
    
    P2 i1, i2, i3;
    
    Non_Trivial_Three_Circle_Intersection_Pts( c1, c2, c3, i1, i2, i3 );
    
    Cell cell_1 = cell, cell_2 = cell, cell_3 = cell;
    
    bool cell_c1_intersection = Cell_Circle_Intersections( cell_1, c1 );
    bool cell_c2_intersection = Cell_Circle_Intersections( cell_2, c2 );
    bool cell_c3_intersection = Cell_Circle_Intersections( cell_3, c3 );
    
    int num_vertices_within_c1 = Num_Vertices_Within_Circle( cell, c1 );
    int num_vertices_within_c2 = Num_Vertices_Within_Circle( cell, c2 );
    int num_vertices_within_c3 = Num_Vertices_Within_Circle( cell, c3 );
    
    bool c1_centre_within_cell = Pt_Within_Convex_Hull( cell, c1.c );
    bool c2_centre_within_cell = Pt_Within_Convex_Hull( cell, c2.c );
    bool c3_centre_within_cell = Pt_Within_Convex_Hull( cell, c3.c );
    
    if (!cell_c1_intersection && !cell_c2_intersection && !cell_c3_intersection)
    {
        if (num_vertices_within_c1 == 4 && num_vertices_within_c2 == 4 && num_vertices_within_c3 == 4) return cell.area;
        
        else if (num_vertices_within_c1 == 4 || num_vertices_within_c2 == 4 || num_vertices_within_c3 == 4) return 0;
        
        else if (c1_centre_within_cell) return intersection_area;
        
        else return 0;
    }
    
    else if (!cell_c1_intersection)
    {
        if (num_vertices_within_c1 == 4) return Two_Circle_Intersection_Area_Within_Cell( cell, c2, c3 );
        
        else if (c1_centre_within_cell) return intersection_area;
        
        else return 0;
    }
    
    else if (!cell_c2_intersection)
    {
        if (num_vertices_within_c2 == 4) return Two_Circle_Intersection_Area_Within_Cell( cell, c1, c3 );
        
        else if (c2_centre_within_cell) return intersection_area;
        
        else return 0;
    }
    
    else if (!cell_c3_intersection)
    {
        if (num_vertices_within_c3 == 4) return Two_Circle_Intersection_Area_Within_Cell( cell, c1, c2 );
        
        else if (c3_centre_within_cell) return intersection_area;
        
        else return 0;
    }
    
    else
    {
        int num_vertices_within_all_circles = 0;
        
        for (int counter = 0; counter < cell.vertices.size(); ++counter)
        {
            if (Norm( c1.c, cell.vertices[counter] ) < c1.r - tiny_num && Norm( c2.c, cell.vertices[counter] ) < c2.r - tiny_num && Norm( c3.c, cell.vertices[counter] ) < c3.r - tiny_num) ++num_vertices_within_all_circles;
        }
        
        if (num_vertices_within_all_circles == 0)
        {
            double area = intersection_area;
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                area -= Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c2, c3, cell_1.edges[counter], cell_2.edges[counter], cell_3.edges[counter], cell );
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
        
        else if (num_vertices_within_all_circles == 1)
        {
            vector<int> key_edges;
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                if ((Norm( cell_1.edges[counter].startpt, c1.c) < c1.r - tiny_num && Norm( cell_1.edges[counter].startpt, c2.c) < c2.r - tiny_num && Norm( cell_1.edges[counter].startpt, c3.c) < c3.r - tiny_num) || (Norm( cell_1.edges[counter].endpt, c1.c) < c1.r - tiny_num && Norm( cell_1.edges[counter].endpt, c2.c) < c2.r - tiny_num && Norm( cell_1.edges[counter].endpt, c3.c) < c3.r - tiny_num))
                {
                    key_edges.push_back( counter );
                }
            }
            
            double area = Three_Circle_Intersection_Irregular_Sector_Area( c1, c2, c3, cell_1.edges[key_edges[0]], cell_2.edges[key_edges[0]], cell_3.edges[key_edges[0]], cell_1.edges[key_edges[1]], cell_2.edges[key_edges[1]], cell_3.edges[key_edges[1]] );
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                area -= Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c2, c3, cell_1.edges[counter], cell_2.edges[counter], cell_3.edges[counter], cell );
            }
            
            return area;
        }
        
        else if (num_vertices_within_all_circles == 2)
        {
            bool type_1_edge = false;
            Edge key_edge;
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                if (cell_1.edges[counter].intersection_type == 1 && cell_2.edges[counter].intersection_type == 1 && cell_3.edges[counter].intersection_type == 1)
                {
                    key_edge = cell.edges[counter];
                    type_1_edge = true;
                }
            }
            
            if (type_1_edge)
            {
                return Three_Circle_Intersection_Interior_Edge_Area( c1, c2, c3, key_edge, cell_1, cell_2, cell_3 );
            }
            
            else
            {
                double area_1, area_2;
                
                if (Norm( cell.edges[0].startpt, c1.c ) < c1.r - tiny_num && Norm( cell.edges[0].startpt, c2.c ) < c2.r - tiny_num && Norm( cell.edges[0].startpt, c3.c ) < c3.r - tiny_num)
                {
                    area_1 = Three_Circle_Intersection_Irregular_Sector_Area( c1, c2, c3, cell_1.edges[0], cell_2.edges[0], cell_3.edges[0], cell_1.edges[3], cell_2.edges[3], cell_3.edges[3] );
                    
                    area_2 = Three_Circle_Intersection_Irregular_Sector_Area( c1, c2, c3, cell_1.edges[1], cell_2.edges[1], cell_3.edges[1], cell_1.edges[2], cell_2.edges[2], cell_3.edges[2] );
                }
                
                else
                {
                    area_1 = Three_Circle_Intersection_Irregular_Sector_Area( c1, c2, c3, cell_1.edges[0], cell_2.edges[0], cell_3.edges[0], cell_1.edges[1], cell_2.edges[1], cell_3.edges[1] );
                    
                    area_2 = Three_Circle_Intersection_Irregular_Sector_Area( c1, c2, c3, cell_1.edges[2], cell_2.edges[2], cell_3.edges[2], cell_1.edges[3], cell_2.edges[3], cell_3.edges[3] );
                }
                
                return area_1 + area_2 - intersection_area;
            }
        }
        
        else
        {
            vector<int> key_edges;
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                if (!(Norm( cell.edges[counter].startpt, c1.c ) < c1.r + tiny_num && Norm( cell.edges[counter].startpt, c2.c ) < c2.r + tiny_num && Norm( cell.edges[counter].startpt, c3.c ) < c3.r + tiny_num) || !(Norm( cell.edges[counter].endpt, c1.c ) < c1.r + tiny_num && Norm( cell.edges[counter].endpt, c2.c ) < c2.r + tiny_num && Norm( cell.edges[counter].endpt, c3.c ) < c3.r + tiny_num))
                {
                    key_edges.push_back( counter );
                }
            }
            
            if (key_edges.size() == 0) return cell.area;
            
            else
            {
                return cell.area - Three_Circle_Intersection_Concave_Cone_Area( c1, c2, c3, cell_1.edges[key_edges[0]], cell_2.edges[key_edges[0]], cell_3.edges[key_edges[0]], cell_1.edges[key_edges[1]], cell_2.edges[key_edges[1]], cell_3.edges[key_edges[1]] );
            }
        }
    }
}

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
                area -= Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c3c.thc.c[0], c3c.thc.c[1], c3c.thc.c[2], c3c.cc[0].cell.edges[counter], c3c.cc[1].cell.edges[counter], c3c.cc[2].cell.edges[counter], c3c.cell );
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
            
            if (type_1_edge)
            {
                return Three_Circle_Intersection_Interior_Edge_Area( c3c.thc.c[0], c3c.thc.c[1], c3c.thc.c[2], key_edge, c3c.cc[0].cell, c3c.cc[1].cell, c3c.cc[2].cell );
            }
            
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
