#include "Input3D.h"
#include "Cell_Volume.h"

void Make_Cell3D ( Input3D const& input, Cell3D& cell )
{
    cell.vertices.reserve( 8 );
    
    cell.vertices.push_back( P3( 0, 0, 0 ) );
    cell.vertices.push_back( input.pts[0] );
    cell.vertices.push_back( P3( input.pts[0].x() + input.pts[1].x(), input.pts[0].y() + input.pts[1].y(), input.pts[0].z() + input.pts[1].z() ) );
    cell.vertices.push_back( input.pts[1] );
    cell.vertices.push_back( input.pts[2] );
    cell.vertices.push_back( P3( input.pts[0].x() + input.pts[2].x(), input.pts[0].y() + input.pts[2].y(), input.pts[0].z() + input.pts[2].z() ) );
    cell.vertices.push_back( P3( input.pts[0].x() + input.pts[1].x() + input.pts[2].x(), input.pts[0].y() + input.pts[1].y() + input.pts[2].y(), input.pts[0].z() + input.pts[1].z() + input.pts[2].z() ) );
    cell.vertices.push_back( P3( input.pts[1].x() + input.pts[2].x(), input.pts[1].y() + input.pts[2].y(), input.pts[1].z() + input.pts[2].z() ) );
    
    cell.pts.reserve( 8 );
    
    cell.pts = cell.vertices;
    
    cell.edges.reserve( 12 );
    
    cell.edges.push_back( Edge3D( L3( cell.vertices[0], cell.vertices[1] ), cell.vertices[0], cell.vertices[1], 0 ) );
    cell.edges.push_back( Edge3D( L3( cell.vertices[1], cell.vertices[2] ), cell.vertices[1], cell.vertices[2], 1 ) );
    cell.edges.push_back( Edge3D( L3( cell.vertices[2], cell.vertices[3] ), cell.vertices[2], cell.vertices[3], 2 ) );
    cell.edges.push_back( Edge3D( L3( cell.vertices[3], cell.vertices[0] ), cell.vertices[3], cell.vertices[0], 3 ) );
    cell.edges.push_back( Edge3D( L3( cell.vertices[4], cell.vertices[5] ), cell.vertices[4], cell.vertices[5], 4 ) );
    cell.edges.push_back( Edge3D( L3( cell.vertices[5], cell.vertices[6] ), cell.vertices[5], cell.vertices[6], 5 ) );
    cell.edges.push_back( Edge3D( L3( cell.vertices[6], cell.vertices[7] ), cell.vertices[6], cell.vertices[7], 6 ) );
    cell.edges.push_back( Edge3D( L3( cell.vertices[7], cell.vertices[4] ), cell.vertices[7], cell.vertices[4], 7 ) );
    cell.edges.push_back( Edge3D( L3( cell.vertices[0], cell.vertices[4] ), cell.vertices[0], cell.vertices[4], 8 ) );
    cell.edges.push_back( Edge3D( L3( cell.vertices[1], cell.vertices[5] ), cell.vertices[1], cell.vertices[5], 9 ) );
    cell.edges.push_back( Edge3D( L3( cell.vertices[2], cell.vertices[6] ), cell.vertices[2], cell.vertices[6], 10 ) );
    cell.edges.push_back( Edge3D( L3( cell.vertices[3], cell.vertices[7] ), cell.vertices[3], cell.vertices[7], 11 ) );
    
    cell.planes.reserve( 8 );
    
    cell.planes.push_back( Plane( cell.vertices[0], cell.vertices[1], cell.vertices[2] ) );
    cell.planes.push_back( Plane( cell.vertices[0], cell.vertices[1], cell.vertices[4] ) );
    cell.planes.push_back( Plane( cell.vertices[4], cell.vertices[5], cell.vertices[6] ) );
    cell.planes.push_back( Plane( cell.vertices[2], cell.vertices[3], cell.vertices[6] ) );
    cell.planes.push_back( Plane( cell.vertices[0], cell.vertices[3], cell.vertices[4] ) );
    cell.planes.push_back( Plane( cell.vertices[1], cell.vertices[2], cell.vertices[5] ) );
    
    Cell_Volume( cell );
}
