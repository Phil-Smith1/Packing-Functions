#include "Cell3D.h"
#include "Sphere_Five_Plane_Intersection_Volume.h"

double Wedge_Volume_By_Exclusion2 ( vector<pair<Pl3, int>>const& planes, Pl3 const& p1, Pl3 const& p2, Sphere const& s )
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
    
    volume -= s.vol - Spherical_Cap( s, p1 );
    volume -= s.vol - Spherical_Cap( s, p2 );
    
    for (auto it = planes.begin(); it != planes.end(); ++it)
    {
        volume += General_Spherical_Wedge( s, p1.opposite(), (*it).first.opposite() );
    }
    
    for (auto it = planes.begin(); it != planes.end(); ++it)
    {
        volume += General_Spherical_Wedge( s, p2.opposite(), (*it).first.opposite() );
    }
    
    volume += General_Spherical_Wedge( s, p1.opposite(), p2.opposite() );
    
    for (auto it_1 = planes.begin(); it_1 != planes.end(); ++it_1)
    {
        for (auto it_2 = it_1 + 1; it_2 != planes.end(); ++it_2)
        {
            if ((*it_1).second == 0 && (*it_2).second == 2) continue;
            if ((*it_1).second == 1 && (*it_2).second == 3) continue;
            if ((*it_1).second == 4 && (*it_2).second == 5) continue;
            
            volume -= General_Spherical_Cone( s, p1.opposite(), (*it_1).first.opposite(), (*it_2).first.opposite() );
        }
    }
    
    for (auto it_1 = planes.begin(); it_1 != planes.end(); ++it_1)
    {
        for (auto it_2 = it_1 + 1; it_2 != planes.end(); ++it_2)
        {
            if ((*it_1).second == 0 && (*it_2).second == 2) continue;
            if ((*it_1).second == 1 && (*it_2).second == 3) continue;
            if ((*it_1).second == 4 && (*it_2).second == 5) continue;
            
            volume -= General_Spherical_Cone( s, p2.opposite(), (*it_1).first.opposite(), (*it_2).first.opposite() );
        }
    }
    
    for (auto it = planes.begin(); it != planes.end(); ++it)
    {
        volume -= General_Spherical_Cone( s, p1.opposite(), p2.opposite(), (*it).first.opposite() );
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
                
                volume += Sphere_Four_Plane_Intersection_Volume( s, p1.opposite(), planes[counter_1].first.opposite(), planes[counter_2].first.opposite(), planes[counter_3].first.opposite() );
            }
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
                
                volume += Sphere_Four_Plane_Intersection_Volume( s, p2.opposite(), planes[counter_1].first.opposite(), planes[counter_2].first.opposite(), planes[counter_3].first.opposite() );
            }
        }
    }
    
    for (auto it_1 = planes.begin(); it_1 != planes.end(); ++it_1)
    {
        for (auto it_2 = it_1 + 1; it_2 != planes.end(); ++it_2)
        {
            if ((*it_1).second == 0 && (*it_2).second == 2) continue;
            if ((*it_1).second == 1 && (*it_2).second == 3) continue;
            if ((*it_1).second == 4 && (*it_2).second == 5) continue;
            
            volume += Sphere_Four_Plane_Intersection_Volume( s, p1.opposite(), p2.opposite(), (*it_1).first.opposite(), (*it_2).first.opposite() );
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
                
                volume -= Sphere_Five_Plane_Intersection_Volume( s, p1.opposite(), p2.opposite(), (*it_1).first.opposite(), (*it_2).first.opposite(), (*it_3).first.opposite() );
            }
        }
    }
    
    return volume;
}

double Wedge_Volume_By_Exclusion ( vector<pair<Pl3, int>>& planes, Pl3 const& p1, Pl3 const& p2, Sphere const& s )
{
    double volume = General_Spherical_Wedge( s, p1, p2 );
    
    int eliminate_size = 0;
    vector<int> eliminate;
    
    for (int counter = 0; counter < planes.size(); ++counter)
    {
        double cone = General_Spherical_Cone( s, p1, p2, planes[counter].first.opposite() );
        
        if (cone < tiny_num)
        {
            eliminate.push_back( counter - eliminate_size );
            ++eliminate_size;
        }
        
        else volume -= cone;
    }
    
    if (eliminate.size() > 0)
    {
        for (auto it = eliminate.begin(); it != eliminate.end(); ++it) planes.erase( planes.begin() + *it );
    }
    
    vector<pair<int, int>> coeliminate;
    
    for (auto it_1 = planes.begin(); it_1 != planes.end(); ++it_1)
    {
        for (auto it_2 = it_1 + 1; it_2 != planes.end(); ++it_2)
        {
            if ((*it_1).second == 0 && (*it_2).second == 2) continue;
            if ((*it_1).second == 1 && (*it_2).second == 3) continue;
            if ((*it_1).second == 4 && (*it_2).second == 5) continue;
            
            double four_plane = Sphere_Four_Plane_Intersection_Volume( s, p1, p2, (*it_1).first.opposite(), (*it_2).first.opposite() );
            
            if (four_plane < tiny_num) coeliminate.push_back( pair<int, int>( (*it_1).second, (*it_2).second ) );
            
            else volume += four_plane;
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
                
                bool match = false;
                
                for (auto it_4 = coeliminate.begin(); it_4 != coeliminate.end(); ++it_4)
                {
                    if (((*it_1).second == (*it_4).first || (*it_2).second == (*it_4).first) && ((*it_2).second == (*it_4).second || (*it_3).second == (*it_4).second))
                    {
                        match = true;
                        break;
                    }
                }
                
                if (match) continue;
                
                volume -= Sphere_Five_Plane_Intersection_Volume( s, p1, p2, (*it_1).first.opposite(), (*it_2).first.opposite(), (*it_3).first.opposite() );
            }
        }
    }
    
    return volume;
}

double Spherical_Wedge_Volume_Within_Cell ( Cell3D const& cell, Sphere const& s, Pl3 const& p1, Pl3 const& p2 )
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
    
    return Wedge_Volume_By_Exclusion( planes, p1, p2, s );
}
