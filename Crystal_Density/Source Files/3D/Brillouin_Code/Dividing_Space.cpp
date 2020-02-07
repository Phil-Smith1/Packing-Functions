#include "Initialise_Cubes.h"
#include "Divide_Polyhedron.h"

#include <thread>

void Dividing_Space ( P3_E const& centre, multimap<double, P3_E>const& pts, vector<B_Poly>& final_polys, int zone_limit )
{
    vector<B_Poly> polys;
    polys.reserve( 3000 );
    
    Polyhedron cube;
    
    double cube_size = sqrt( pts.rbegin()->first ) * 0.5;
    
    Generate_Cube( cube_size, centre, cube );
    
    double cube_distance = Max_Distance_To_Polyhedron( centre, cube );
    
    polys.push_back( B_Poly( cube, cube_distance, 1 ) );
    
    vector<Polyhedron> cubes;
    
    int num_cubes = 2;
    
    Initialise_Cubes( cube_size, num_cubes, centre, cubes );
    
    vector<vector<B_Poly>> fin_polys( (int)cubes.size() );
    vector<thread> thr;
    
    bool threads = true;
    
    for (int counter = 0; counter < fin_polys.size(); ++counter)
    {
        fin_polys[counter].reserve( 1000 );
    }
    
    if (threads)
    {
        for (int counter = 0; counter < cubes.size(); ++counter)
        {
            this_thread::sleep_for( chrono::milliseconds( 2 ) );
            
            thr.push_back( thread( Divide_Polyhedron, centre, pts, cubes[counter], ref( fin_polys[counter] ), zone_limit ) );
        }
        
        for (int counter = 0; counter < cubes.size(); ++counter)
        {
            thr[counter].join();
        }
    }
    
    else
    {
        for (int counter = 0; counter < cubes.size(); ++counter)
        {
            Divide_Polyhedron( centre, pts, cubes[counter], fin_polys[counter], zone_limit );
        }
    }
    
    for (int counter_1 = 0; counter_1 < cubes.size(); ++counter_1)
    {
        for (int counter_2 = 0; counter_2 < fin_polys[counter_1].size(); ++counter_2)
        {
            final_polys.push_back( fin_polys[counter_1][counter_2] );
        }
    }
}
