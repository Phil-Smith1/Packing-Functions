#include "Make_Cell3D.h"
#include "Norm3D.h"

#ifndef Pi
#define Pi
const double PI = 3.14159265359;
#endif

void Make_Cells3D ( Input3D& input3D, vector<Cell3D>& cells )
{
    if (input3D.deformation_type != 0)
    {
        cells.reserve( input3D.iterations );
        
        if (input3D.deformation_type == 1)
        {
            for (int counter = 0; counter < input3D.iterations; ++counter)
            {
                double theta = counter * 75 * PI / (double)(180 * (input3D.iterations - 1));
                
                input3D.parallelepiped_vectors[0] = P3( 1, 0, 0 );
                input3D.parallelepiped_vectors[1] = P3( 0, 1, 0 );
                input3D.parallelepiped_vectors[2] = P3( sin( theta ), 0, cos( theta ) );
                
                Cell3D cell;
                
                Make_Cell3D( input3D, cell );
                
                cells.push_back( cell );
                
                double max_radius = Norm( cell.vertices[0], cell.vertices[6] );
                
                if (max_radius > input3D.max_radius) input3D.max_radius = max_radius;
            }
        }
    }
    
    else
    {
        Cell3D cell;
        
        Make_Cell3D( input3D, cell );
        
        cells.push_back( cell );
        
        double max_radius = Norm( cell.vertices[0], cell.vertices[6] );
        
        double dist = Norm( cell.vertices[1], cell.vertices[7] );
        
        if (max_radius < dist) max_radius = dist;
        
        dist = Norm( cell.vertices[2], cell.vertices[4] );
        
        if (max_radius < dist) max_radius = dist;
        
        dist = Norm( cell.vertices[3], cell.vertices[5] );
        
        if (max_radius < dist) max_radius = dist;
        
        if (input3D.auto_max_radius) input3D.max_radius = max_radius;
    }
}
