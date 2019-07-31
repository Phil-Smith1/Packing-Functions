#include "Sphere_Volume_Within_Cell.h"

double First_Order_Total_Volume ( Cell3D const& cell, double r )
{
    double volume = 0;
    
    for (auto it = cell.vertices.begin(); it != cell.vertices.end(); ++it)
    {
        Sphere s( *it, r );
        volume += Sphere_Volume_Within_Cell( cell, s );
    }
    
    return volume;
}
