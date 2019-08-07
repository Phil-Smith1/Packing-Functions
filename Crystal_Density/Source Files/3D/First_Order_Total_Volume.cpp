#include "Sphere_Volume_Within_Cell.h"

double First_Order_Total_Volume ( Cell3D const& cell, double r )
{
    double volume = 0;
    
    for (auto it = cell.pts.begin(); it != cell.pts.end(); ++it)
    {
        Sphere s( *it, r );
        volume += Sphere_Volume_Within_Cell( cell, s );
    }
    
    return volume;
}
