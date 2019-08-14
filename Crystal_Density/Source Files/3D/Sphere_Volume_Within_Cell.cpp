#include "Cell3D.h"
#include "General_Spherical_Cone.h"

double New_Function ( vector<Pl3>const& planes, Sphere const& s )
{
    double volume = s.vol;
    
    for (auto it = planes.begin(); it != planes.end(); ++it)
    {
        volume -= s.vol - Spherical_Cap( s, *it );
    }
    
    for (auto it_1 = planes.begin(); it_1 != planes.end(); ++it_1)
    {
        for (auto it_2 = it_1 + 1; it_2 != planes.end(); ++it_2)
        {
            volume += General_Spherical_Wedge( s, (*it_1).opposite(), (*it_2).opposite() );
        }
    }
    
    for (auto it_1 = planes.begin(); it_1 != planes.end(); ++it_1)
    {
        for (auto it_2 = it_1 + 1; it_2 != planes.end(); ++it_2)
        {
            for (auto it_3 = it_2 + 1; it_3 != planes.end(); ++it_3)
            {
                volume -= General_Spherical_Cone( s, (*it_1).opposite(), (*it_2).opposite(), (*it_3).opposite() );
            }
        }
    }
    
    return volume;
}

double Sphere_Volume_Within_Cell ( Cell3D const& cell, Sphere const& s )
{
    int num_vertices_contained = 0;
    
    for (auto it = cell.vertices.begin(); it != cell.vertices.end(); ++it)
    {
        if (Norm( s.c, *it ) < s.r + tiny_num) ++num_vertices_contained;
    }
    
    if (num_vertices_contained == 8) return cell.vol;
    
    double volume;
    
    if (num_vertices_contained == 0)
    {
        volume = s.vol;
        
        for (auto it = cell.planes.begin(); it != cell.planes.end(); ++it)
        {
            volume -= s.vol - Spherical_Cap( s, *it );
        }
        
        volume += General_Spherical_Wedge( s, cell.planes[0].opposite(), cell.planes[1].opposite() );
        volume += General_Spherical_Wedge( s, cell.planes[1].opposite(), cell.planes[2].opposite() );
        volume += General_Spherical_Wedge( s, cell.planes[2].opposite(), cell.planes[3].opposite() );
        volume += General_Spherical_Wedge( s, cell.planes[3].opposite(), cell.planes[0].opposite() );
        volume += General_Spherical_Wedge( s, cell.planes[4].opposite(), cell.planes[0].opposite() );
        volume += General_Spherical_Wedge( s, cell.planes[4].opposite(), cell.planes[1].opposite() );
        volume += General_Spherical_Wedge( s, cell.planes[4].opposite(), cell.planes[2].opposite() );
        volume += General_Spherical_Wedge( s, cell.planes[4].opposite(), cell.planes[3].opposite() );
        volume += General_Spherical_Wedge( s, cell.planes[5].opposite(), cell.planes[0].opposite() );
        volume += General_Spherical_Wedge( s, cell.planes[5].opposite(), cell.planes[1].opposite() );
        volume += General_Spherical_Wedge( s, cell.planes[5].opposite(), cell.planes[2].opposite() );
        volume += General_Spherical_Wedge( s, cell.planes[5].opposite(), cell.planes[3].opposite() );
        
        return volume;
    }
    
    vector<Pl3> planes;
    
    planes.reserve( 6 );
    
    for (auto it = cell.planes.begin(); it != cell.planes.end(); ++it)
    {
        if (sqrt( squared_distance( s.c, cell.planes[0] ) ) > s.r - tiny_num)
        {
            if (cell.planes[0].oriented_side( s.c ) == ON_NEGATIVE_SIDE) return 0;
        }
        
        else planes.push_back( *it );
    }
    
    return New_Function( planes, s );
    
    /*volume = s.vol;
    
    for (auto it = cell.planes.begin(); it != cell.planes.end(); ++it)
    {
        volume -= s.vol - Spherical_Cap( s, *it );
    }
    
    volume += General_Spherical_Wedge( s, cell.planes[0].opposite(), cell.planes[1].opposite() );
    volume += General_Spherical_Wedge( s, cell.planes[1].opposite(), cell.planes[2].opposite() );
    volume += General_Spherical_Wedge( s, cell.planes[2].opposite(), cell.planes[3].opposite() );
    volume += General_Spherical_Wedge( s, cell.planes[3].opposite(), cell.planes[0].opposite() );
    volume += General_Spherical_Wedge( s, cell.planes[4].opposite(), cell.planes[0].opposite() );
    volume += General_Spherical_Wedge( s, cell.planes[4].opposite(), cell.planes[1].opposite() );
    volume += General_Spherical_Wedge( s, cell.planes[4].opposite(), cell.planes[2].opposite() );
    volume += General_Spherical_Wedge( s, cell.planes[4].opposite(), cell.planes[3].opposite() );
    volume += General_Spherical_Wedge( s, cell.planes[5].opposite(), cell.planes[0].opposite() );
    volume += General_Spherical_Wedge( s, cell.planes[5].opposite(), cell.planes[1].opposite() );
    volume += General_Spherical_Wedge( s, cell.planes[5].opposite(), cell.planes[2].opposite() );
    volume += General_Spherical_Wedge( s, cell.planes[5].opposite(), cell.planes[3].opposite() );
    
    volume -= General_Spherical_Cone( s, cell.planes[0].opposite(), cell.planes[1].opposite(), cell.planes[4].opposite() );
    volume -= General_Spherical_Cone( s, cell.planes[0].opposite(), cell.planes[1].opposite(), cell.planes[5].opposite() );
    volume -= General_Spherical_Cone( s, cell.planes[1].opposite(), cell.planes[2].opposite(), cell.planes[4].opposite() );
    volume -= General_Spherical_Cone( s, cell.planes[1].opposite(), cell.planes[2].opposite(), cell.planes[5].opposite() );
    volume -= General_Spherical_Cone( s, cell.planes[2].opposite(), cell.planes[3].opposite(), cell.planes[4].opposite() );
    volume -= General_Spherical_Cone( s, cell.planes[2].opposite(), cell.planes[3].opposite(), cell.planes[5].opposite() );
    volume -= General_Spherical_Cone( s, cell.planes[3].opposite(), cell.planes[0].opposite(), cell.planes[4].opposite() );
    volume -= General_Spherical_Cone( s, cell.planes[3].opposite(), cell.planes[0].opposite(), cell.planes[5].opposite() );
    
    return volume;*/
}
