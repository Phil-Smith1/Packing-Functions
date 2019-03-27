#include "Cell_Circle.h"
#include "Edge_Circle_Intersections.h"

bool Cell_Circle_Intersections ( Cell& cell, Circle const& circle )
{
    bool intersection = false;
    
    for (int counter = 0; counter < cell.edges.size(); ++counter)
    {
        Edge_Circle_Intersections( circle, cell.edges[counter] );
        
        if (cell.edges[counter].intersection_type > 1) intersection = true;
    }
    
    return intersection;
}

void Cell_Circle_Intersections ( Cell_Circle& cc )
{
    for (int counter = 0; counter < cc.cell.edges.size(); ++counter)
    {
        Edge_Circle_Intersections( cc.c, cc.cell.edges[counter] );
        
        if (cc.cell.edges[counter].intersection_type > 1) cc.intersection = true;
    }
}
