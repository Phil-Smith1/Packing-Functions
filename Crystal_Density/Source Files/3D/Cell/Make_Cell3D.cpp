#include "Input3D.h"
#include "Cell_Volume.h"

typedef K::Vector_3 V3;

void Make_Cell3D ( Input3D const& input, Cell3D& cell )
{
    cell.vertices.reserve( 8 );
    
    cell.vertices.push_back( P3( 0, 0, 0 ) );
    cell.vertices.push_back( input.parallelepiped_vectors[0] );
    cell.vertices.push_back( P3( input.parallelepiped_vectors[0].x() + input.parallelepiped_vectors[1].x(), input.parallelepiped_vectors[0].y() + input.parallelepiped_vectors[1].y(), input.parallelepiped_vectors[0].z() + input.parallelepiped_vectors[1].z() ) );
    cell.vertices.push_back( input.parallelepiped_vectors[1] );
    cell.vertices.push_back( input.parallelepiped_vectors[2] );
    cell.vertices.push_back( P3( input.parallelepiped_vectors[0].x() + input.parallelepiped_vectors[2].x(), input.parallelepiped_vectors[0].y() + input.parallelepiped_vectors[2].y(), input.parallelepiped_vectors[0].z() + input.parallelepiped_vectors[2].z() ) );
    cell.vertices.push_back( P3( input.parallelepiped_vectors[0].x() + input.parallelepiped_vectors[1].x() + input.parallelepiped_vectors[2].x(), input.parallelepiped_vectors[0].y() + input.parallelepiped_vectors[1].y() + input.parallelepiped_vectors[2].y(), input.parallelepiped_vectors[0].z() + input.parallelepiped_vectors[1].z() + input.parallelepiped_vectors[2].z() ) );
    cell.vertices.push_back( P3( input.parallelepiped_vectors[1].x() + input.parallelepiped_vectors[2].x(), input.parallelepiped_vectors[1].y() + input.parallelepiped_vectors[2].y(), input.parallelepiped_vectors[1].z() + input.parallelepiped_vectors[2].z() ) );
    
    if (input.pts_at_vertices)
    {
        cell.pts.reserve( 8 );
        
        cell.pts = cell.vertices;
    }
    
    if (input.interior_points)
    {
        if (input.pts_at_vertices) cell.pts.reserve( 8 + input.interior_pts.size() );
        
        else cell.pts.reserve( input.interior_pts.size() );
        
        for (int counter = 0; counter < input.interior_pts.size(); ++counter)
        {
            V3 v1 = input.parallelepiped_vectors[0] - P3( 0, 0, 0 );
            V3 v2 = input.parallelepiped_vectors[1] - P3( 0, 0, 0 );
            V3 v3 = input.parallelepiped_vectors[2] - P3( 0, 0, 0 );
            
            v1 *= input.interior_pts[counter].x();
            v2 *= input.interior_pts[counter].y();
            v3 *= input.interior_pts[counter].z();
            
            cell.pts.push_back( P3( v1.x() + v2.x() + v3.x(), v1.y() + v2.y() + v3.y(), v1.z() + v2.z() + v3.z() ) );
        }
    }
    
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
