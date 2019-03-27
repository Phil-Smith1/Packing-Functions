#include "Make_Cell.h"
#include "Two_Circle_Intersection_Area_Within_Cell.h"
#include "Cell_2Circles.h"

double Two_Circle_Intersection_Interior_Edge_Area ( Circle const& c1, Circle const& c2, Edge const& e, Cell const& cell_1, Cell const& cell_2 )
{
    int index_1 = (e.index + 3) % 4;
    int index_2 = (e.index + 1) % 4;
    
    P2 p1, p2, p3, p4;
    
    p2 = e.startpt;
    p3 = e.endpt;
    
    if (cell_1.edges[index_1].intersection_type != 1 && Norm( cell_1.edges[index_1].i1, c2.c ) < c2.r)
    {
        p1 = cell_1.edges[index_1].i1;
    }
    
    else p1 = cell_2.edges[index_1].i1;
    
    if (cell_1.edges[index_2].intersection_type != 1 && Norm( cell_1.edges[index_2].i1, c2.c ) < c2.r)
    {
        p4 = cell_1.edges[index_2].i1;
    }
    
    else p4 = cell_2.edges[index_2].i1;
    
    double triangle_area_1 = Triangle_Area( p1, p2, p3 );
    double triangle_area_2 = Triangle_Area( p1, p3, p4 );
    
    Cell cell_3;
    
    if (e.index == 0) Make_Cell( p1, p4, cell_1.vertices[2], cell_1.vertices[3], cell_3 );
    
    else if (e.index == 1) Make_Cell( cell_1.vertices[0], p1, p4, cell_1.vertices[3], cell_3 );
    
    else if (e.index == 2) Make_Cell( cell_1.vertices[0], cell_1.vertices[1], p1, p4, cell_3 );
    
    else if (e.index == 3) Make_Cell( p4, cell_1.vertices[1], cell_1.vertices[2], p1, cell_3 );
    
    return triangle_area_1 + triangle_area_2 + Two_Circle_Intersection_Area_Within_Cell( cell_3, c1, c2 );
}

double Two_Circle_Intersection_Interior_Edge_Area ( Cell_2Circles const& c2c, Edge const& e )
{
    Circle c1 = c2c.tc.c[0], c2 = c2c.tc.c[1];
    Cell cell_1 = c2c.cc[0].cell, cell_2 = c2c.cc[1].cell;
    
    int index_1 = (e.index + 3) % 4;
    int index_2 = (e.index + 1) % 4;
    
    if (cell_1.edges[index_1].intersection_type == 5 && Norm( cell_1.edges[index_1].i1, c2.c ) < c2.r)
    {
        int index_3 = (index_1 + 1) % 4;
        int index_4 = (index_1 + 2) % 4;
        
        return Two_Circle_Intersection_Concave_Cone_Area( c2c, cell_1.edges[index_3], cell_2.edges[index_3], cell_1.edges[index_4], cell_2.edges[index_4]);
    }
    
    else if (cell_1.edges[index_2].intersection_type == 5 && Norm( cell_1.edges[index_2].i1, c2.c ) < c2.r)
    {
        int index_3 = (index_2 + 1) % 4;
        int index_4 = (index_2 + 2) % 4;
        
        return Two_Circle_Intersection_Concave_Cone_Area( c2c, cell_1.edges[index_3], cell_2.edges[index_3], cell_1.edges[index_4], cell_2.edges[index_4]);
    }
    
    else if (cell_2.edges[index_1].intersection_type == 5 && Norm( cell_2.edges[index_1].i1, c1.c ) < c1.r)
    {
        int index_3 = (index_1 + 1) % 4;
        int index_4 = (index_1 + 2) % 4;
        
        return Two_Circle_Intersection_Concave_Cone_Area( c2c, cell_1.edges[index_3], cell_2.edges[index_3], cell_1.edges[index_4], cell_2.edges[index_4]);
    }
    
    else if (cell_2.edges[index_2].intersection_type == 5 && Norm( cell_2.edges[index_2].i1, c1.c ) < c1.r)
    {
        int index_3 = (index_2 + 1) % 4;
        int index_4 = (index_2 + 2) % 4;
        
        return Two_Circle_Intersection_Concave_Cone_Area( c2c, cell_1.edges[index_3], cell_2.edges[index_3], cell_1.edges[index_4], cell_2.edges[index_4]);
    }
    
    P2 p1, p2, p3, p4;
    
    p2 = e.startpt;
    p3 = e.endpt;
    
    if (cell_1.edges[index_1].intersection_type != 1 && Norm( cell_1.edges[index_1].i1, c2.c ) < c2.r)
    {
        p1 = cell_1.edges[index_1].i1;
    }
    
    else p1 = cell_2.edges[index_1].i1;
    
    if (cell_1.edges[index_2].intersection_type != 1 && Norm( cell_1.edges[index_2].i1, c2.c ) < c2.r)
    {
        p4 = cell_1.edges[index_2].i1;
    }
    
    else p4 = cell_2.edges[index_2].i1;
    
    double triangle_area_1 = Triangle_Area( p1, p2, p3 );
    double triangle_area_2 = Triangle_Area( p1, p3, p4 );
    
    Cell cell_3;
    
    if (e.index == 0) Make_Cell( p1, p4, cell_1.vertices[2], cell_1.vertices[3], cell_3 );
    
    else if (e.index == 1) Make_Cell( cell_1.vertices[0], p1, p4, cell_1.vertices[3], cell_3 );
    
    else if (e.index == 2) Make_Cell( cell_1.vertices[0], cell_1.vertices[1], p1, p4, cell_3 );
    
    else if (e.index == 3) Make_Cell( p4, cell_1.vertices[1], cell_1.vertices[2], p1, cell_3 );
    
    return triangle_area_1 + triangle_area_2 + Two_Circle_Intersection_Area_Within_Cell( cell_3, c1, c2 );
}

