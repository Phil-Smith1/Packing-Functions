#include "Cell_Circle_Intersections.h"
#include "Num_Vertices_Within_Circle.h"
#include "Pt_Within_Convex_Hull.h"
#include "Area_Excluded_By_Exterior_Edge.h"
#include "Irregular_Sector_Area.h"
#include "Interior_Edge_Area.h"
#include "Concave_Cone_Area.h"

double Zero_Vertices ( Cell_Circle& cc )
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

double One_Vertex ( Cell_Circle& cc )
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

double Two_Vertices ( Cell_Circle& cc )
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

double Three_Vertices ( Cell_Circle& cc )
{
    vector<Edge> key_edges;
    
    for (int counter = 0; counter < cc.cell.edges.size(); ++counter)
    {
        if (cc.cell.edges[counter].intersection_type == 2) key_edges.push_back( cc.cell.edges[counter] );
    }
    
    if (key_edges.size() == 0) return cc.cell.area;
    
    else return cc.cell.area - Concave_Cone_Area( cc.c, key_edges[0], key_edges[1] );
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
        if (cc.num_vertices_within_circle == 0) return Zero_Vertices( cc );
        
        else if (cc.num_vertices_within_circle == 1) return One_Vertex( cc );
        
        else if (cc.num_vertices_within_circle == 2) return Two_Vertices( cc );
        
        else return Three_Vertices( cc );
    }
}
