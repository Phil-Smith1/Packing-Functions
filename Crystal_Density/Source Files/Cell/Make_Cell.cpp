#include "Cell_Area.h"

void Make_Cell ( vector<P2>const& pts, Cell& cell )
{
    cell.vertices.reserve( 4 );
    
    cell.vertices.push_back( P2( 0, 0 ) );
    cell.vertices.push_back( pts[0] );
    cell.vertices.push_back( P2( pts[0].x() + pts[1].x(), pts[0].y() + pts[1].y() ) );
    cell.vertices.push_back( pts[1] );
    
    cell.pts.reserve( 4 );
    
    cell.pts = cell.vertices;
    
    cell.edges.reserve( 4 );
    
    cell.edges.push_back( Edge( L2( cell.vertices[0], cell.vertices[1] ), cell.vertices[0], cell.vertices[1], 0 ) );
    cell.edges.push_back( Edge( L2( cell.vertices[1], cell.vertices[2] ), cell.vertices[1], cell.vertices[2], 1 ) );
    cell.edges.push_back( Edge( L2( cell.vertices[2], cell.vertices[3] ), cell.vertices[2], cell.vertices[3], 2 ) );
    cell.edges.push_back( Edge( L2( cell.vertices[3], cell.vertices[0] ), cell.vertices[3], cell.vertices[0], 3 ) );
    
    cell.area = Cell_Area( cell );
}

void Make_Cell ( P2 const& p1, P2 const& p2, P2 const& p3, P2 const& p4, Cell& cell )
{
    cell.vertices.reserve( 4 );
    
    cell.vertices.push_back( p1 );
    cell.vertices.push_back( p2 );
    cell.vertices.push_back( p3 );
    cell.vertices.push_back( p4 );
    
    cell.pts.reserve( 4 );
    
    cell.pts = cell.vertices;
    
    cell.edges.reserve( 4 );
    
    cell.edges.push_back( Edge( L2( p1, p2 ), p1, p2, 0 ) );
    cell.edges.push_back( Edge( L2( p2, p3 ), p2, p3, 1 ) );
    cell.edges.push_back( Edge( L2( p3, p4 ), p3, p4, 2 ) );
    cell.edges.push_back( Edge( L2( p4, p1 ), p4, p1, 3 ) );
    
    cell.area = Cell_Area( cell );
}
