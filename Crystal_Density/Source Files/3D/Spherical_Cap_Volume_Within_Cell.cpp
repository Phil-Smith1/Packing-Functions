#include "Cell3D.h"
#include "Sphere_Four_Plane_Intersection_Volume.h"

double Cap_Volume_By_Exclusion3 ( Cell3D const& cell, Pl3 const& p, Sphere const& s )
{
    double volume = s.vol;
    
    for (auto it = cell.planes.begin(); it != cell.planes.end(); ++it)
    {
        volume -= s.vol - Spherical_Cap( s, *it );
    }
    
    volume -= s.vol - Spherical_Cap( s, p );
    
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
    volume += General_Spherical_Wedge( s, p.opposite(), cell.planes[0].opposite() );
    volume += General_Spherical_Wedge( s, p.opposite(), cell.planes[1].opposite() );
    volume += General_Spherical_Wedge( s, p.opposite(), cell.planes[2].opposite() );
    volume += General_Spherical_Wedge( s, p.opposite(), cell.planes[3].opposite() );
    volume += General_Spherical_Wedge( s, p.opposite(), cell.planes[4].opposite() );
    volume += General_Spherical_Wedge( s, p.opposite(), cell.planes[5].opposite() );
    
    volume -= General_Spherical_Cone( s, cell.planes[0].opposite(), cell.planes[1].opposite(), cell.planes[4].opposite() );
    volume -= General_Spherical_Cone( s, cell.planes[0].opposite(), cell.planes[1].opposite(), cell.planes[5].opposite() );
    volume -= General_Spherical_Cone( s, cell.planes[1].opposite(), cell.planes[2].opposite(), cell.planes[4].opposite() );
    volume -= General_Spherical_Cone( s, cell.planes[1].opposite(), cell.planes[2].opposite(), cell.planes[5].opposite() );
    volume -= General_Spherical_Cone( s, cell.planes[2].opposite(), cell.planes[3].opposite(), cell.planes[4].opposite() );
    volume -= General_Spherical_Cone( s, cell.planes[2].opposite(), cell.planes[3].opposite(), cell.planes[5].opposite() );
    volume -= General_Spherical_Cone( s, cell.planes[3].opposite(), cell.planes[0].opposite(), cell.planes[4].opposite() );
    volume -= General_Spherical_Cone( s, cell.planes[3].opposite(), cell.planes[0].opposite(), cell.planes[5].opposite() );
    
    volume -= General_Spherical_Cone( s, p.opposite(), cell.planes[0].opposite(), cell.planes[1].opposite() );
    volume -= General_Spherical_Cone( s, p.opposite(), cell.planes[1].opposite(), cell.planes[2].opposite() );
    volume -= General_Spherical_Cone( s, p.opposite(), cell.planes[2].opposite(), cell.planes[3].opposite() );
    volume -= General_Spherical_Cone( s, p.opposite(), cell.planes[3].opposite(), cell.planes[0].opposite() );
    volume -= General_Spherical_Cone( s, p.opposite(), cell.planes[4].opposite(), cell.planes[0].opposite() );
    volume -= General_Spherical_Cone( s, p.opposite(), cell.planes[4].opposite(), cell.planes[1].opposite() );
    volume -= General_Spherical_Cone( s, p.opposite(), cell.planes[4].opposite(), cell.planes[2].opposite() );
    volume -= General_Spherical_Cone( s, p.opposite(), cell.planes[4].opposite(), cell.planes[3].opposite() );
    volume -= General_Spherical_Cone( s, p.opposite(), cell.planes[5].opposite(), cell.planes[0].opposite() );
    volume -= General_Spherical_Cone( s, p.opposite(), cell.planes[5].opposite(), cell.planes[1].opposite() );
    volume -= General_Spherical_Cone( s, p.opposite(), cell.planes[5].opposite(), cell.planes[2].opposite() );
    volume -= General_Spherical_Cone( s, p.opposite(), cell.planes[5].opposite(), cell.planes[3].opposite() );
    
    volume += Sphere_Four_Plane_Intersection_Volume( s, p.opposite(), cell.planes[0].opposite(), cell.planes[1].opposite(), cell.planes[4].opposite() );
    volume += Sphere_Four_Plane_Intersection_Volume( s, p.opposite(), cell.planes[0].opposite(), cell.planes[1].opposite(), cell.planes[5].opposite() );
    volume += Sphere_Four_Plane_Intersection_Volume( s, p.opposite(), cell.planes[1].opposite(), cell.planes[2].opposite(), cell.planes[4].opposite() );
    volume += Sphere_Four_Plane_Intersection_Volume( s, p.opposite(), cell.planes[1].opposite(), cell.planes[2].opposite(), cell.planes[5].opposite() );
    volume += Sphere_Four_Plane_Intersection_Volume( s, p.opposite(), cell.planes[2].opposite(), cell.planes[3].opposite(), cell.planes[4].opposite() );
    volume += Sphere_Four_Plane_Intersection_Volume( s, p.opposite(), cell.planes[2].opposite(), cell.planes[3].opposite(), cell.planes[5].opposite() );
    volume += Sphere_Four_Plane_Intersection_Volume( s, p.opposite(), cell.planes[3].opposite(), cell.planes[0].opposite(), cell.planes[4].opposite() );
    volume += Sphere_Four_Plane_Intersection_Volume( s, p.opposite(), cell.planes[3].opposite(), cell.planes[0].opposite(), cell.planes[5].opposite() );
    
    return volume;
}

double Cap_Volume_By_Exclusion ( vector<pair<Pl3, int>>const& planes, Pl3 const& p, Sphere const& s )
{
    double volume = s.vol;
    
    for (auto it = planes.begin(); it != planes.end(); ++it)
    {
        volume -= s.vol - Spherical_Cap( s, (*it).first );
    }
    
    for (auto it_1 = planes.begin(); it_1 != planes.end(); ++it_1)
    {
        for (auto it_2 = it_1 + 1; it_2 != planes.end(); ++it_2)
        {
            if ((*it_1).second == 0 && (*it_2).second == 2) continue;
            if ((*it_1).second == 1 && (*it_2).second == 3) continue;
            if ((*it_1).second == 4 && (*it_2).second == 5) continue;
            
            volume += General_Spherical_Wedge( s, (*it_1).first.opposite(), (*it_2).first.opposite() );
        }
    }
    
    for (auto it_1 = planes.begin(); it_1 != planes.end(); ++it_1)
    {
        for (auto it_2 = it_1 + 1; it_2 != planes.end(); ++it_2)
        {
            for (auto it_3 = it_2 + 1; it_3 != planes.end(); ++it_3)
            {
                if ((*it_1).second == 0 && ((*it_2).second == 2 || (*it_3).second == 2)) continue;
                if (((*it_1).second == 1 || (*it_2).second == 1) && ((*it_2).second == 3 || (*it_3).second == 3)) continue;
                if (((*it_1).second == 4 || (*it_2).second == 4 || (*it_3).second == 4) && ((*it_2).second == 5 || (*it_3).second == 5)) continue;
                
                volume -= General_Spherical_Cone( s, (*it_1).first.opposite(), (*it_2).first.opposite(), (*it_3).first.opposite() );
            }
        }
    }
    
    volume -= s.vol - Spherical_Cap( s, p );
    
    for (auto it = planes.begin(); it != planes.end(); ++it)
    {
        volume += General_Spherical_Wedge( s, p.opposite(), (*it).first.opposite() );
    }
    
    for (auto it_1 = planes.begin(); it_1 != planes.end(); ++it_1)
    {
        for (auto it_2 = it_1 + 1; it_2 != planes.end(); ++it_2)
        {
            if ((*it_1).second == 0 && (*it_2).second == 2) continue;
            if ((*it_1).second == 1 && (*it_2).second == 3) continue;
            if ((*it_1).second == 4 && (*it_2).second == 5) continue;
            
            volume -= General_Spherical_Cone( s, p.opposite(), (*it_1).first.opposite(), (*it_2).first.opposite() );
        }
    }
    
    for (int counter_1 = 0; counter_1 != planes.size(); ++counter_1)
    {
        for (int counter_2 = counter_1 + 1; counter_2 != planes.size(); ++counter_2)
        {
            for (int counter_3 = counter_2 + 1; counter_3 != planes.size(); ++counter_3)
            {
                if (planes[counter_1].second == 0 && (planes[counter_2].second == 2 || planes[counter_3].second == 2)) continue;
                if ((planes[counter_1].second == 1 || planes[counter_2].second == 1) && (planes[counter_2].second == 3 || planes[counter_3].second == 3)) continue;
                if ((planes[counter_1].second == 4 || planes[counter_2].second == 4 || planes[counter_3].second == 4) && (planes[counter_2].second == 5 || planes[counter_3].second == 5)) continue;
                
                volume += Sphere_Four_Plane_Intersection_Volume( s, p.opposite(), planes[counter_1].first.opposite(), planes[counter_2].first.opposite(), planes[counter_3].first.opposite() );
            }
        }
    }
    
    return volume;
}

double Cap_Volume_By_Exclusion2 ( vector<pair<Pl3, int>>const& planes, Pl3 const& p, Sphere const& s )
{
    double volume = s.vol;
    
    for (auto it = planes.begin(); it != planes.end(); ++it)
    {
        volume -= s.vol - Spherical_Cap( s, (*it).first );
    }
    
    for (auto it_1 = planes.begin(); it_1 != planes.end(); ++it_1)
    {
        for (auto it_2 = it_1 + 1; it_2 != planes.end(); ++it_2)
        {
            if ((*it_1).second == 0 && (*it_2).second == 2) continue;
            if ((*it_1).second == 1 && (*it_2).second == 3) continue;
            if ((*it_1).second == 4 && (*it_2).second == 5) continue;
            
            volume += General_Spherical_Wedge( s, (*it_1).first.opposite(), (*it_2).first.opposite() );
        }
    }
    
    volume -= s.vol - Spherical_Cap( s, p );
    
    for (auto it = planes.begin(); it != planes.end(); ++it)
    {
        volume += General_Spherical_Wedge( s, p.opposite(), (*it).first.opposite() );
    }
    
    for (auto it_1 = planes.begin(); it_1 != planes.end(); ++it_1)
    {
        for (auto it_2 = it_1 + 1; it_2 != planes.end(); ++it_2)
        {
            if ((*it_1).second == 0 && (*it_2).second == 2) continue;
            if ((*it_1).second == 1 && (*it_2).second == 3) continue;
            if ((*it_1).second == 4 && (*it_2).second == 5) continue;
            
            volume -= General_Spherical_Cone( s, p.opposite(), (*it_1).first.opposite(), (*it_2).first.opposite() );
        }
    }
    
    return volume;
}

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
    
    int num_vertices_contained = 0;
    
    for (auto it = cell.vertices.begin(); it != cell.vertices.end(); ++it)
    {
        if (Norm( s.c, *it ) < s.r + tiny_num) ++num_vertices_contained;
    }
    
    if (num_vertices_contained == 0) return Cap_Volume_By_Exclusion2( planes, p, s );
    
    return Cap_Volume_By_Exclusion( planes, p, s );
}
