#include "Three_Sphere_Intersection_Volume_Within_Cell.h"

double Third_Order_Total_Volume ( Cell3D const& cell, double r )
{
    vector<double> volumes;
    
    volumes.reserve( cell.pts.size() * (cell.pts.size() - 1) * (cell.pts.size() - 2) / (double)6 );
    
    for (int counter_1 = 0; counter_1 < cell.pts.size(); ++counter_1)
    {
        for (int counter_2 = counter_1 + 1; counter_2 < cell.pts.size(); ++counter_2)
        {
            for (int counter_3 = counter_2 + 1; counter_3 < cell.pts.size(); ++counter_3)
            {
                Sphere s1( cell.pts[counter_1], r ), s2( cell.pts[counter_2], r ), s3( cell.pts[counter_3], r );
                
                volumes.push_back( Three_Sphere_Intersection_Volume_Within_Cell( cell, s1, s2, s3 ) );
            }
        }
    }
    
    double volume = 0;
    
    for (auto it = volumes.begin(); it != volumes.end(); ++it) volume += *it;
    
    return volume;
}
