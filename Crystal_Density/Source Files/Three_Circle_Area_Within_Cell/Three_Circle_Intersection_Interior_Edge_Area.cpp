#include "Make_Cell.h"
#include "Three_Circle_Intersection_Area_Within_Cell.h"

double Three_Circle_Intersection_Interior_Edge_Area ( Circle const& c1, Circle const& c2, Circle const& c3, Edge const& e, Cell const& cell_1, Cell const& cell_2, Cell const& cell_3 )
{
    int index_1 = (e.index + 3) % 4;
    int index_2 = (e.index + 1) % 4;
    
    P2 p1, p2, p3, p4;
    
    p2 = e.startpt;
    p3 = e.endpt;
    
    if (cell_1.edges[index_1].intersection_type != 1 && Norm( cell_1.edges[index_1].i1, c2.c ) < c2.r && Norm( cell_1.edges[index_1].i1, c3.c ) < c3.r) p1 = cell_1.edges[index_1].i1;
    
    else if (cell_2.edges[index_1].intersection_type != 1 && Norm( cell_2.edges[index_1].i1, c1.c ) < c1.r && Norm( cell_2.edges[index_1].i1, c3.c ) < c3.r) p1 = cell_2.edges[index_1].i1;
    
    else if (cell_3.edges[index_1].intersection_type != 1 && Norm( cell_3.edges[index_1].i1, c1.c ) < c1.r && Norm( cell_3.edges[index_1].i1, c2.c ) < c2.r) p1 = cell_3.edges[index_1].i1;
    
    else if (cell_1.edges[index_1].intersection_type != 1 && Norm( cell_1.edges[index_1].i1, c3.c ) < c3.r) p1 = cell_1.edges[index_1].i1;
    
    else p1 = cell_3.edges[index_1].i1;
    
    if (cell_1.edges[index_2].intersection_type != 1 && Norm( cell_1.edges[index_2].i1, c2.c ) < c2.r && Norm( cell_1.edges[index_2].i1, c3.c ) < c3.r) p4 = cell_1.edges[index_2].i1;
    
    else if (cell_2.edges[index_2].intersection_type != 1 && Norm( cell_2.edges[index_2].i1, c1.c ) < c1.r && Norm( cell_2.edges[index_2].i1, c3.c ) < c3.r) p4 = cell_2.edges[index_2].i1;
    
    else if (cell_3.edges[index_2].intersection_type != 1 && Norm( cell_3.edges[index_2].i1, c1.c ) < c1.r && Norm( cell_3.edges[index_2].i1, c2.c ) < c2.r) p4 = cell_3.edges[index_2].i1;
    
    else if (cell_1.edges[index_2].intersection_type != 1 && Norm( cell_1.edges[index_2].i1, c3.c ) < c3.r) p4 = cell_1.edges[index_2].i1;
    
    else p4 = cell_3.edges[index_2].i1;
    
    double triangle_area_1 = Triangle_Area( p1, p2, p3 );
    double triangle_area_2 = Triangle_Area( p1, p3, p4 );
    
    Cell cell_4;
    
    if (e.index == 0) Make_Cell( p1, p4, cell_1.vertices[2], cell_1.vertices[3], cell_4 );
    
    else if (e.index == 1) Make_Cell( cell_1.vertices[0], p1, p4, cell_1.vertices[3], cell_4 );
    
    else if (e.index == 2) Make_Cell( cell_1.vertices[0], cell_1.vertices[1], p1, p4, cell_4 );
    
    else if (e.index == 3) Make_Cell( p4, cell_1.vertices[1], cell_1.vertices[2], p1, cell_4 );
    
    return triangle_area_1 + triangle_area_2 + Three_Circle_Intersection_Area_Within_Cell( cell_4, c1, c2, c3 );
}
