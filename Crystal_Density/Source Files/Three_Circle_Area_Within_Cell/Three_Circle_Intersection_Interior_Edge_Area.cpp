#include "Make_Cell.h"
#include "First_Order_Total_Area.h"
#include "Second_Order_Total_Area.h"
#include "Third_Order_Total_Area.h"

double Three_Circle_Intersection_Interior_Edge_Area ( Cell_3Circles const& c3c, Edge const& e )
{
    int index_1 = (e.index + 3) % 4;
    int index_2 = (e.index + 1) % 4;
    
    Cell cell_1 = c3c.cc[0].cell;
    Cell cell_2 = c3c.cc[1].cell;
    Cell cell_3 = c3c.cc[2].cell;
    
    Circle c1 = c3c.cc[0].c, c2 = c3c.cc[1].c, c3 = c3c.cc[2].c;
    
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
    
    vector<double> r = { c1.r, c1.r, c1.r, c1.r, c1.r, c1.r, c1.r };
    
    Cell cell_5 = c3c.cell;
    cell_5.edges[0] = cell_4.edges[0];
    cell_5.edges[1] = cell_4.edges[1];
    cell_5.edges[2] = cell_4.edges[2];
    cell_5.edges[3] = cell_4.edges[3];
    cell_5.vertices[0] = cell_4.vertices[0];
    cell_5.vertices[1] = cell_4.vertices[1];
    cell_5.vertices[2] = cell_4.vertices[2];
    cell_5.vertices[3] = cell_4.vertices[3];
    
    cell_5.pts.clear();
    cell_5.pts.push_back( c1.c );
    cell_5.pts.push_back( c2.c );
    cell_5.pts.push_back( c3.c );
    cell_5.num_pts = 3;
    
    Frame f( cell_5, r );
    
    First_Order_Total_Area( f );
    Second_Order_Total_Area( f );
    Third_Order_Total_Area( f );
    
    return triangle_area_1 + triangle_area_2 + f.c3c[0].area;
}
