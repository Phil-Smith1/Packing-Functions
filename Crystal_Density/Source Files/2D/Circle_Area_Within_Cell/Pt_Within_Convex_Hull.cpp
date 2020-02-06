#include "Cell.h"

// Returns true if point is within or on boundary of convex hull, else returns false.

bool Pt_Within_Convex_Hull ( Cell const& cell, P2 const& p )
{
    Oriented_side oriented_side = cell.edges[0].line.oriented_side( p );
    
    for (int counter = 0; counter < cell.edges.size(); ++counter)
    {
        Oriented_side orientation = cell.edges[counter].line.oriented_side( p );
        
        if (orientation == ON_ORIENTED_BOUNDARY)
        {
            L2 perp_1 = cell.edges[counter].line.perpendicular( cell.edges[counter].startpt );
            L2 perp_2 = cell.edges[counter].line.perpendicular( cell.edges[counter].endpt );
            
            if (perp_1.oriented_side( p ) == perp_2.oriented_side( p )) return false;
            
            else return true;
        }
        
        else if (orientation != oriented_side) return false;
    }
    
    return true;
}
