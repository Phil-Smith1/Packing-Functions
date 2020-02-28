#include "Generate_Cube.h"

void Initialise_Cubes ( double cube_size, int num_cubes, P3_E const& centre, vector<Polyhedron>& cubes )
{
    cubes.reserve( num_cubes * num_cubes * num_cubes );
    
    P3_E vertex = P3_E( centre.x() - cube_size, centre.y() - cube_size, centre.z() - cube_size );
    
    cube_size = cube_size / (double)num_cubes;
    
    for (int counter_1 = 0; counter_1 < num_cubes; ++counter_1)
    {
        for (int counter_2 = 0; counter_2 < num_cubes; ++counter_2)
        {
            for (int counter_3 = 0; counter_3 < num_cubes; ++counter_3)
            {
                Polyhedron cube;
                
                P3_E new_vertex = vertex + V3_E( 2 * counter_1 * cube_size, 2 * counter_2 * cube_size, 2 * counter_3 * cube_size );
                
                P3_E new_centre = new_vertex + V3_E( cube_size, cube_size, cube_size );
                
                Generate_Cube( cube_size, new_centre, cube );
                
                cubes.push_back( cube );
            }
        }
    }
}

void Initialise_Cubes_I ( double cube_size, int num_cubes, P3 const& centre, vector<Polyhedron_I>& cubes )
{
    cubes.reserve( num_cubes * num_cubes * num_cubes );
    
    P3 vertex = P3( centre.x() - cube_size, centre.y() - cube_size, centre.z() - cube_size );
    
    cube_size = cube_size / (double)num_cubes;
    
    for (int counter_1 = 0; counter_1 < num_cubes; ++counter_1)
    {
        for (int counter_2 = 0; counter_2 < num_cubes; ++counter_2)
        {
            for (int counter_3 = 0; counter_3 < num_cubes; ++counter_3)
            {
                Polyhedron_I cube;
                
                P3 new_vertex = vertex + V3( 2 * counter_1 * cube_size, 2 * counter_2 * cube_size, 2 * counter_3 * cube_size );
                
                P3 new_centre = new_vertex + V3( cube_size, cube_size, cube_size );
                
                Generate_Cube_I( cube_size, new_centre, cube );
                
                cubes.push_back( cube );
            }
        }
    }
}
