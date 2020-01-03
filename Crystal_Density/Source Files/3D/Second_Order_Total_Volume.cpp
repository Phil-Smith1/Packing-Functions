#include "Two_Sphere_Intersection_Volume_Within_Cell.h"

double Second_Order_Total_Volume ( Cell3D const& cell, double r, bool parallelepiped )
{
    vector<double> volumes;
    
    volumes.reserve( cell.pts.size() * (cell.pts.size() - 1) * 0.5 );
    
    if (parallelepiped)
    {
        double angle1 = Angle_Between_Vectors( P3( 0, 0, 0 ) + cell.planes[0].orthogonal_vector(), P3( 0, 0, 0 ) + cell.planes[1].orthogonal_vector() );
        double angle2 = Angle_Between_Vectors( P3( 0, 0, 0 ) + cell.planes[0].orthogonal_vector(), P3( 0, 0, 0 ) + cell.planes[4].orthogonal_vector() );
        double angle3 = Angle_Between_Vectors( P3( 0, 0, 0 ) + cell.planes[1].orthogonal_vector(), P3( 0, 0, 0 ) + cell.planes[4].orthogonal_vector() );
        
        bool orthogonal1 = false;
        bool orthogonal2 = false;
        bool orthogonal3 = false;
        
        if (abs( angle1 - 0.5 * PI ) < tiny_num && abs( angle2 - 0.5 * PI ) < tiny_num) orthogonal1 = true;
        if (abs( angle1 - 0.5 * PI ) < tiny_num && abs( angle3 - 0.5 * PI ) < tiny_num) orthogonal2 = true;
        if (abs( angle2 - 0.5 * PI ) < tiny_num && abs( angle3 - 0.5 * PI ) < tiny_num) orthogonal3 = true;
        
        for (int counter_1 = 0; counter_1 < cell.pts.size(); ++counter_1)
        {
            for (int counter_2 = counter_1 + 1; counter_2 < cell.pts.size(); ++counter_2)
            {
                if (counter_1 == 4 && counter_2 == 5) {volumes.push_back( volumes[13] ); continue;}
                if (counter_1 == 5 && counter_2 == 6) {volumes.push_back( volumes[2] ); continue;}
                if (counter_1 == 6 && counter_2 == 7) {volumes.push_back( volumes[0] ); continue;}
                if (counter_1 == 4 && counter_2 == 7) {volumes.push_back( volumes[7] ); continue;}
                if (counter_1 == 2 && counter_2 == 6) {volumes.push_back( volumes[3] ); continue;}
                if (counter_1 == 3 && counter_2 == 7) {volumes.push_back( volumes[10] ); continue;}
                
                if (orthogonal1)
                {
                    if (counter_1 == 2 && counter_2 == 3) {volumes.push_back( volumes[0] ); continue;}
                }
                
                if (orthogonal2)
                {
                    if (counter_1 == 1 && counter_2 == 2) {volumes.push_back( volumes[2] ); continue;}
                }
                
                if (orthogonal3)
                {
                    if (counter_1 == 1 && counter_2 == 5) {volumes.push_back( volumes[3] ); continue;}
                }
                
                Sphere s1( cell.pts[counter_1], r ), s2( cell.pts[counter_2], r );
                
                volumes.push_back( Two_Sphere_Intersection_Volume_Within_Cell( cell, s1, s2 ) );
            }
        }
    }
    
    else
    {
        for (int counter_1 = 0; counter_1 < cell.pts.size(); ++counter_1)
        {
            for (int counter_2 = counter_1 + 1; counter_2 < cell.pts.size(); ++counter_2)
            {
                Sphere s1( cell.pts[counter_1], r ), s2( cell.pts[counter_2], r );
                
                volumes.push_back( Two_Sphere_Intersection_Volume_Within_Cell( cell, s1, s2 ) );
            }
        }
    }
    
    double volume = 0;
    
    for (auto it = volumes.begin(); it != volumes.end(); ++it) volume += *it;
    
    return volume;
}
