#include "Sphere_Volume_Within_Cell.h"

double First_Order_Total_Volume ( Cell3D const& cell, double r )
{
    vector<double> volumes;
    
    volumes.reserve( cell.pts.size() );
    
    double angle1 = Angle_Between_Vectors( P3( 0, 0, 0 ) + cell.planes[0].orthogonal_vector(), P3( 0, 0, 0 ) + cell.planes[1].orthogonal_vector() );
    double angle2 = Angle_Between_Vectors( P3( 0, 0, 0 ) + cell.planes[0].orthogonal_vector(), P3( 0, 0, 0 ) + cell.planes[4].orthogonal_vector() );
    
    bool orthogonal = false;
    
    if (angle1 - 0.5 * PI < tiny_num && angle2 - 0.5 * PI < tiny_num) orthogonal = true;
    
    for (int counter = 0; counter < cell.pts.size(); ++counter)
    {
        if (counter == 4) {volumes.push_back( volumes[2] ); continue;}
        if (counter == 5) {volumes.push_back( volumes[3] ); continue;}
        if (counter == 6) {volumes.push_back( volumes[0] ); continue;}
        if (counter == 7) {volumes.push_back( volumes[1] ); continue;}
        
        if (orthogonal)
        {
            if (counter == 2) {volumes.push_back( volumes[0] ); continue;}
            if (counter == 3) {volumes.push_back( volumes[1] ); continue;}
        }
        
        Sphere s( cell.pts[counter], r );
        
        volumes.push_back( Sphere_Volume_Within_Cell( cell, s ) );
    }
    
    double volume = 0;
    
    for (auto it = volumes.begin(); it != volumes.end(); ++it) volume += *it;
    
    return volume;
}
