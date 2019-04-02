#include "Cell3D.h"

void Cell_Volume ( Cell3D& cell )
{
    double volume = cell.vertices[1].y() * cell.vertices[3].z() * cell.vertices[4].x() - cell.vertices[1].x() * cell.vertices[3].z() * cell.vertices[4].y() + cell.vertices[1].x() * cell.vertices[3].y() * cell.vertices[4].z();
    
    if (volume < 0) volume *= -1;
    
    cell.vol = volume;
}
