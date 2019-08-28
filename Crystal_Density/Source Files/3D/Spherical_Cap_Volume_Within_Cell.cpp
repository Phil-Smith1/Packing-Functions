#include "Cell3D.h"
#include "Cap_Volume_By_Exclusion.h"

double Spherical_Cap_Volume_Within_Cell ( Cell3D const& cell, Sphere const& s, Pl3 const& p )
{
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
    
    return Cap_Volume_By_Exclusion( planes, p, s );
}
