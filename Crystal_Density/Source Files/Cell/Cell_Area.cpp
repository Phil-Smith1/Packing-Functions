#include "Cell.h"

double Cell_Area ( Cell& cell )
{
    double z = cell.vertices[1].x() * cell.vertices[3].y() - cell.vertices[1].y() * cell.vertices[3].x();
    
    if (z < 0) z *= -1;
    
    return z;
}
