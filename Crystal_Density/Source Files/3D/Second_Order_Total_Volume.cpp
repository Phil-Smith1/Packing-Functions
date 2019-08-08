#include "Two_Sphere_Intersection_Volume_Within_Cell.h"

double Second_Order_Total_Volume ( Cell3D const& cell, double r )
{
    double volume = 0;
    
    for (auto it_1 = cell.pts.begin(); it_1 != cell.pts.end(); ++it_1)
    {
        for (auto it_2 = it_1 + 1; it_2 != cell.pts.end(); ++it_2)
        {
            Sphere s1( *it_1, r ), s2( *it_2, r );
            
            volume += Two_Sphere_Intersection_Volume_Within_Cell( cell, s1, s2 );
        }
    }
    
    return volume;
}
