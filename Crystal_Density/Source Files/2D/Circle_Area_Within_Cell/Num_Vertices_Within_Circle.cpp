#include "Cell_Circle.h"
#include "Norm.h"

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

int Num_Vertices_Within_Circle ( Cell const& cell, Circle const& circle )
{
    int num_vertices_within_circle = 0;
    
    for (auto v : cell.vertices)
    {
        if (Norm( v, circle.c ) < circle.r - tiny_num) ++num_vertices_within_circle;
    }
    
    return num_vertices_within_circle;
}

void Num_Vertices_Within_Circle ( Cell_Circle& cc )
{
    for (auto v : cc.cell.vertices)
    {
        if (Norm( v, cc.c.c ) < cc.c.r - tiny_num) ++cc.num_vertices_within_circle;
    }
}
