#include "Cell.h"

typedef K::Vector_2 V2;

void Interior_Pts ( Cell& cell, vector<P2>const& interior_pts )
{
    for (int counter = 0; counter < interior_pts.size(); ++counter)
    {
        V2 v1 = cell.vertices[3] - ORIGIN;
        v1 = interior_pts[counter].x() * v1;
        
        V2 v2 = cell.vertices[1] - ORIGIN;
        v2 = interior_pts[counter].y() * v2;
        
        V2 v3 = v1 + v2;
        
        P2 p = ORIGIN + v3;
        
        cell.pts.push_back( p );
    }
    
    cell.num_pts = (int)cell.pts.size();
    
    if (cell.num_pts > 4) cell.interior_pts = true;
}
