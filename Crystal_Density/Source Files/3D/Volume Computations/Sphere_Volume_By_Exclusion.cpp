#include "General_Spherical_Cone.h"

using namespace std;

double Sphere_Volume_By_Exclusion ( vector<pair<Pl3, int>>const& planes, Sphere const& s )
{
    double volume = s.vol;
    
    for (auto it = planes.begin(); it != planes.end(); ++it)
    {
        volume -= s.vol - Spherical_Cap( s, (*it).first );
    }
    
    vector<pair<int, int>> coeliminate;
    
    for (auto it_1 = planes.begin(); it_1 != planes.end(); ++it_1)
    {
        for (auto it_2 = it_1 + 1; it_2 != planes.end(); ++it_2)
        {
            if ((*it_1).second == 0 && (*it_2).second == 2) continue;
            if ((*it_1).second == 1 && (*it_2).second == 3) continue;
            if ((*it_1).second == 4 && (*it_2).second == 5) continue;
            
            double wedge = General_Spherical_Wedge( s, (*it_1).first.opposite(), (*it_2).first.opposite() );
            
            if (wedge < tiny_num) coeliminate.push_back( pair<int, int>( (*it_1).second, (*it_2).second ) );
            
            else volume += wedge;
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
                
                volume -= General_Spherical_Cone( s, (*it_1).first.opposite(), (*it_2).first.opposite(), (*it_3).first.opposite() );
            }
        }
    }
    
    return volume;
}
