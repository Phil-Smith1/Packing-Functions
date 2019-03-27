#include "Cell_Circle_Intersections.h"
#include "Num_Vertices_Within_Circle.h"
#include "Pt_Within_Convex_Hull.h"
#include "Area_Excluded_By_Exterior_Edge.h"
#include "Irregular_Sector_Area.h"
#include "Interior_Edge_Area.h"
#include "Concave_Cone_Area.h"

double Circle_Area_Within_Cell ( Cell& cell, Circle const& circle )
{
    bool intersection = Cell_Circle_Intersections( cell, circle );
    
    int num_vertices_within_circle = Num_Vertices_Within_Circle( cell, circle );
    
    bool centre_within_cell = Pt_Within_Convex_Hull( cell, circle.c );
    
    if (!intersection)
    {
        if (num_vertices_within_circle == 4) return cell.area;
        
        else if (centre_within_cell) return circle.area;
        
        else return 0;
    }
    
    else
    {
        if (num_vertices_within_circle == 0)
        {
            double area = circle.area;
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                area -= Area_Excluded_By_Exterior_Edge( circle, cell.edges[counter], cell );
            }
            
            if (area == circle.area)
            {
                if (Pt_Within_Convex_Hull( cell, circle.c )) return area;
                
                else return 0;
            }
            
            else return area;
        }
        
        else if (num_vertices_within_circle == 1)
        {
            vector<Edge> key_edges;
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                if (cell.edges[counter].intersection_type == 2 || cell.edges[counter].intersection_type == 5)
                {
                    key_edges.push_back( cell.edges[counter] );
                }
            }
            
            double area = Irregular_Sector_Area( circle, key_edges[0], key_edges[1] );
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                area -= Area_Excluded_By_Exterior_Edge( circle, cell.edges[counter], cell );
            }
            
            return area;
        }
        
        else if (num_vertices_within_circle == 2)
        {
            bool type_1_edge = false;
            Edge key_edge;
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                if (cell.edges[counter].intersection_type == 1)
                {
                    key_edge = cell.edges[counter];
                    type_1_edge = true;
                }
            }
            
            if (type_1_edge)
            {
                int index_1 = (key_edge.index + 3) % 4;
                int index_2 = (key_edge.index + 1) % 4;
                
                double area = Interior_Edge_Area( circle, cell.edges[index_1], key_edge, cell.edges[index_2] );
                
                for (int counter = 0; counter < cell.edges.size(); ++counter)
                {
                    area -= Area_Excluded_By_Exterior_Edge( circle, cell.edges[counter], cell );
                }
                
                return area;
            }
            
            else
            {
                double area_1, area_2;
                
                if (Norm( cell.edges[0].startpt, circle.c ) < circle.r - tiny_num)
                {
                    area_1 = Irregular_Sector_Area( circle, cell.edges[0], cell.edges[3] );
                    area_2 = Irregular_Sector_Area( circle, cell.edges[1], cell.edges[2] );
                }
                
                else
                {
                    area_1 = Irregular_Sector_Area( circle, cell.edges[0], cell.edges[1] );
                    area_2 = Irregular_Sector_Area( circle, cell.edges[2], cell.edges[3] );
                }
                
                return area_1 + area_2 - circle.area;
            }
        }
        
        else
        {
            vector<Edge> key_edges;
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                if (cell.edges[counter].intersection_type == 2) key_edges.push_back( cell.edges[counter] );
            }
            
            if (key_edges.size() == 0) return cell.area;
            
            else return cell.area - Concave_Cone_Area( circle, key_edges[0], key_edges[1] );
        }
    }
}

double Circle_Area_Within_Cell ( Cell_Circle& cc )
{
    Cell_Circle_Intersections( cc );
    
    Num_Vertices_Within_Circle( cc );
    
    cc.centre_within_cell = Pt_Within_Convex_Hull( cc.cell, cc.c.c );
    
    if (!cc.intersection)
    {
        if (cc.num_vertices_within_circle == 4) return cc.cell.area;
        
        else if (cc.centre_within_cell) return cc.c.area;
        
        else return 0;
    }
    
    else
    {
        if (cc.num_vertices_within_circle == 0)
        {
            double area = cc.c.area;
            
            for (int counter = 0; counter < cc.cell.edges.size(); ++counter)
            {
                area -= Area_Excluded_By_Exterior_Edge( cc.c, cc.cell.edges[counter], cc.cell );
            }
            
            if (area == cc.c.area)
            {
                if (Pt_Within_Convex_Hull( cc.cell, cc.c.c )) return area;
                
                else return 0;
            }
            
            else return area;
        }
        
        else if (cc.num_vertices_within_circle == 1)
        {
            vector<Edge> key_edges;
            
            for (int counter = 0; counter < cc.cell.edges.size(); ++counter)
            {
                if (cc.cell.edges[counter].intersection_type == 2 || cc.cell.edges[counter].intersection_type == 5)
                {
                    key_edges.push_back( cc.cell.edges[counter] );
                }
            }
            
            double area = Irregular_Sector_Area( cc.c, key_edges[0], key_edges[1] );
            
            for (int counter = 0; counter < cc.cell.edges.size(); ++counter)
            {
                area -= Area_Excluded_By_Exterior_Edge( cc.c, cc.cell.edges[counter], cc.cell );
            }
            
            return area;
        }
        
        else if (cc.num_vertices_within_circle == 2)
        {
            bool type_1_edge = false;
            Edge key_edge;
            
            for (int counter = 0; counter < cc.cell.edges.size(); ++counter)
            {
                if (cc.cell.edges[counter].intersection_type == 1)
                {
                    key_edge = cc.cell.edges[counter];
                    type_1_edge = true;
                }
            }
            
            if (type_1_edge)
            {
                int index_1 = (key_edge.index + 3) % 4;
                int index_2 = (key_edge.index + 1) % 4;
                
                double area = Interior_Edge_Area( cc.c, cc.cell.edges[index_1], key_edge, cc.cell.edges[index_2] );
                
                for (int counter = 0; counter < cc.cell.edges.size(); ++counter)
                {
                    area -= Area_Excluded_By_Exterior_Edge( cc.c, cc.cell.edges[counter], cc.cell );
                }
                
                return area;
            }
            
            else
            {
                double area_1, area_2;
                
                if (Norm( cc.cell.edges[0].startpt, cc.c.c ) < cc.c.r - tiny_num)
                {
                    area_1 = Irregular_Sector_Area( cc.c, cc.cell.edges[0], cc.cell.edges[3] );
                    area_2 = Irregular_Sector_Area( cc.c, cc.cell.edges[1], cc.cell.edges[2] );
                }
                
                else
                {
                    area_1 = Irregular_Sector_Area( cc.c, cc.cell.edges[0], cc.cell.edges[1] );
                    area_2 = Irregular_Sector_Area( cc.c, cc.cell.edges[2], cc.cell.edges[3] );
                }
                
                return area_1 + area_2 - cc.c.area;
            }
        }
        
        else
        {
            vector<Edge> key_edges;
            
            for (int counter = 0; counter < cc.cell.edges.size(); ++counter)
            {
                if (cc.cell.edges[counter].intersection_type == 2) key_edges.push_back( cc.cell.edges[counter] );
            }
            
            if (key_edges.size() == 0) return cc.cell.area;
            
            else return cc.cell.area - Concave_Cone_Area( cc.c, key_edges[0], key_edges[1] );
        }
    }
}
