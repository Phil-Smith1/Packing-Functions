#include <string>

#include "Make_Cell.h"
#include "Interior_Pts.h"

void Cell_Data ( string const& lattice_type, P2 const& pt1, P2 const& pt2, P2 const& pt3, P2 const& pt4, bool interior_points, vector<P2>const& interior_pts, Cell& cell )
{
    P2 p1, p2, p3, p4;
    
    if (lattice_type == "Square")
    {
        p1 = P2( 0, 0 );
        p2 = P2( 0, 1 );
        p3 = P2( 1, 1 );
        p4 = P2( 1, 0 );
    }
    
    else if (lattice_type == "Triangular")
    {
        p1 = P2( 0, 0 );
        p2 = P2( 0.5, 0.5 * sqrt( (double)3 ) );
        p3 = P2( 1.5, 0.5 * sqrt( (double)3 ) );
        p4 = P2( 1, 0 );
    }
    
    else
    {
        p1 = pt1;
        p2 = pt2;
        p3 = pt3;
        p4 = pt4;
    }
    
    Make_Cell( p1, p2, p3, p4, cell );
    
    if (interior_points) Interior_Pts( cell, interior_pts );
    
    else cell.num_pts = 4;
}
