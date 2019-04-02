#include "Input.h"
#include "Make_Cell.h"
#include "Interior_Pts.h"

void Cell_Data ( Input& input, Cell& cell )
{
    if (input.lattice_type == "Square")
    {
        input.pts[0] = P2( 0, 1 );
        input.pts[1] = P2( 1, 0 );
    }
    
    else if (input.lattice_type == "Triangular")
    {
        input.pts[0] = P2( 0.5, 0.5 * sqrt( (double)3 ) );
        input.pts[1] = P2( 1, 0 );
    }
    
    input.pts[0] = P2( input.pts[0].x() * input.scale[0], input.pts[0].y() * input.scale[0] );
    input.pts[1] = P2( input.pts[1].x() * input.scale[1], input.pts[1].y() * input.scale[1] );
    
    Make_Cell( input.pts, cell );
    
    if (input.interior_points) Interior_Pts( cell, input.interior_pts );
    
    else cell.num_pts = 4;
}
