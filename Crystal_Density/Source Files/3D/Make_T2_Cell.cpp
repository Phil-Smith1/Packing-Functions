#include "Cell_Volume.h"
#include "Frac_To_Cart_Coords.h"

void Make_T2_Cell ( vector<pair<string, double>>const& cell_shape, double ** matrix, Cell3D& cell )
{
    P3 p1 = P3( 1, 0, 0 );
    P3 p2 = P3( 0, 1, 0 );
    P3 p3 = P3( 0, 0, 1 );
    
    Frac_To_Cart_Coords( matrix, p1 );
    Frac_To_Cart_Coords( matrix, p2 );
    Frac_To_Cart_Coords( matrix, p3 );
    
    cell.vertices.reserve( 8 );
    
    cell.vertices.push_back( P3( 0, 0, 0 ) );
    cell.vertices.push_back( p1 );
    cell.vertices.push_back( P3( p1.x() + p2.x(), p1.y() + p2.y(), p1.z() + p2.z() ) );
    cell.vertices.push_back( p2 );
    cell.vertices.push_back( p3 );
    cell.vertices.push_back( P3( p1.x() + p3.x(), p1.y() + p3.y(), p1.z() + p3.z() ) );
    cell.vertices.push_back( P3( p1.x() + p2.x() + p3.x(), p1.y() + p2.y() + p3.y(), p1.z() + p2.z() + p3.z() ) );
    cell.vertices.push_back( P3( p2.x() + p3.x(), p2.y() + p3.y(), p2.z() + p3.z() ) );
    
    cell.planes.reserve( 6 );
    
    cell.planes.push_back( Pl3( cell.vertices[0], cell.vertices[1], cell.vertices[2] ) );
    if (cell.planes[0].oriented_side( cell.vertices[4] ) == ON_NEGATIVE_SIDE) cell.planes[0] = cell.planes[0].opposite();
    cell.planes.push_back( Pl3( cell.vertices[0], cell.vertices[1], cell.vertices[4] ) );
    if (cell.planes[1].oriented_side( cell.vertices[3] ) == ON_NEGATIVE_SIDE) cell.planes[1] = cell.planes[1].opposite();
    cell.planes.push_back( Pl3( cell.vertices[4], cell.vertices[5], cell.vertices[6] ) );
    if (cell.planes[2].oriented_side( cell.vertices[0] ) == ON_NEGATIVE_SIDE) cell.planes[2] = cell.planes[2].opposite();
    cell.planes.push_back( Pl3( cell.vertices[2], cell.vertices[3], cell.vertices[6] ) );
    if (cell.planes[3].oriented_side( cell.vertices[0] ) == ON_NEGATIVE_SIDE) cell.planes[3] = cell.planes[3].opposite();
    cell.planes.push_back( Pl3( cell.vertices[0], cell.vertices[3], cell.vertices[4] ) );
    if (cell.planes[4].oriented_side( cell.vertices[1] ) == ON_NEGATIVE_SIDE) cell.planes[4] = cell.planes[4].opposite();
    cell.planes.push_back( Pl3( cell.vertices[1], cell.vertices[2], cell.vertices[5] ) );
    if (cell.planes[5].oriented_side( cell.vertices[0] ) == ON_NEGATIVE_SIDE) cell.planes[5] = cell.planes[5].opposite();
    
    Cell_Volume( cell );
}
