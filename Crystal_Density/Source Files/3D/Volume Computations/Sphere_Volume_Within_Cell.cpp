#include "Cell3D.h"
#include "Sphere_Volume_By_Exclusion.h"

double Sphere_Volume_Within_Cell ( Cell3D const& cell, Sphere const& s )
{
    int num_vertices_contained = 0;
    
    for (auto it = cell.vertices.begin(); it != cell.vertices.end(); ++it)
    {
        if (Norm( s.c, *it ) < s.r + tiny_num) ++num_vertices_contained;
    }
    
    if (num_vertices_contained == 8) return cell.vol;
    
    vector<pair<Pl3, int>> planes;
    
    planes.reserve( 6 );
    
    for (int counter = 0; counter < cell.planes.size(); ++counter)
    {
        if (sqrt( squared_distance( s.c, cell.planes[counter] ) ) > s.r - tiny_num)
        {
            if (cell.planes[counter].oriented_side( s.c ) == ON_NEGATIVE_SIDE) return 0;
        }
        
        else planes.push_back( pair<Pl3, int>( cell.planes[counter], counter ) );
    }
    
    return Sphere_Volume_By_Exclusion( planes, s );
}
