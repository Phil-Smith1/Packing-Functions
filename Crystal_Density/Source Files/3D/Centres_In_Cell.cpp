#include "Distance_To_Cell.h"

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

bool Centres_In_Cell ( Cell3D const& cell )
{
    for (int counter = 0; counter < cell.pts.size(); ++counter)
    {
        double dist = Distance_To_Cell( cell, cell.pts[counter] );
        
        if (dist < tiny_num) return true;
    }
    
    return false;
}
