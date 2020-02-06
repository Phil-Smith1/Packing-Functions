#include "Cell3D.h"

#ifndef Pi
#define Pi
const double PI = 3.14159265359;
#endif

void Cell_Volume ( Cell3D& cell )
{
    double volume = cell.vertices[1].y() * cell.vertices[3].z() * cell.vertices[4].x() - cell.vertices[1].z() * cell.vertices[3].y() * cell.vertices[4].x() + cell.vertices[1].z() * cell.vertices[3].x() * cell.vertices[4].y() - cell.vertices[1].x() * cell.vertices[3].z() * cell.vertices[4].y() + cell.vertices[1].x() * cell.vertices[3].y() * cell.vertices[4].z() - cell.vertices[1].y() * cell.vertices[3].x() * cell.vertices[4].z();
    
    if (volume < 0) volume *= -1;
    
    cell.vol = volume;
}

double Cell_Volume ( vector<pair<string, double>>const& cell_shape )
{
    double volume = cell_shape[0].second * cell_shape[1].second * cell_shape[2].second * sqrt( 1 - pow( cos( PI * cell_shape[3].second / (double)180 ), 2 ) - pow( cos( PI * cell_shape[4].second / (double)180 ), 2 ) - pow( cos( PI * cell_shape[5].second / (double)180 ), 2 ) + 2 * cos( PI * cell_shape[3].second / (double)180 ) * cos( PI * cell_shape[4].second / (double)180 ) * cos( PI * cell_shape[5].second / (double)180 ) );
    
    return volume;
}
