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
    
    int num_cubes = 10;
    
    Initialise_Cubes( cube_size, num_cubes, centre, cubes );
    
    vector<vector<B_Poly>> fin_polys( (int)cubes.size() );
    vector<thread> thr;
    
    thr.reserve( cubes.size() );
    
    bool threads = true;
    
    for (int counter = 0; counter < fin_polys.size(); ++counter)
    {
        fin_polys[counter].reserve( 1000 );
    }
    
    if (threads)
    {
        for (int counter = 0; counter < cubes.size(); ++counter)
        {
            //this_thread::sleep_for( chrono::milliseconds( 2 ) );
            
            multimap<double, P3_E> copy = pts;
            
            thr.push_back( thread( Divide_Polyhedron, centre, copy, cubes[counter], ref( fin_polys[counter] ), zone_limit ) );
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

void Dividing_Space_I ( P3 const& centre, multimap<double, P3>const& pts, vector<B_Poly_I>& final_polys, int zone_limit, vector<double>& max_radii )
{
    Polyhedron_I cube;
    
    double cube_size = sqrt( pts.rbegin()->first ) * 0.5;
    
    Generate_Cube_I( cube_size, centre, cube );
    
    multimap<double, P3> reduced_pts;
    multimap<double, P3> remaining_pts;
    
    for (auto iter = pts.begin(); iter != pts.end(); ++iter)
    {
        if ((int)reduced_pts.size() <= 5) reduced_pts.insert( pair<double, P3>( iter->first, iter->second ) );
        
        else remaining_pts.insert( pair<double, P3>( iter->first, iter->second ) );
    }
    
    vector<B_Poly_I> starting_polys;
    
    Divide_Polyhedron_I( centre, reduced_pts, cube, 1, starting_polys, zone_limit );
    
    vector<vector<B_Poly_I>> fin_polys( (int)starting_polys.size() );
    vector<thread> thr;
    
    thr.reserve( starting_polys.size() );
    
    bool threads = true;
    
    for (int counter = 0; counter < fin_polys.size(); ++counter)
    {
        fin_polys[counter].reserve( 1000 );
    }
    
    if (threads)
    {
        for (int counter = 0; counter < starting_polys.size(); ++counter)
        {
            thr.push_back( thread( Divide_Polyhedron_I, centre, remaining_pts, starting_polys[counter].poly, starting_polys[counter].zone, ref( fin_polys[counter] ), zone_limit ) );
        }
        
        for (int counter = 0; counter < starting_polys.size(); ++counter)
        {
            thr[counter].join();
        }
    }
    
    else
    {
        for (int counter = 0; counter < starting_polys.size(); ++counter)
        {
            Divide_Polyhedron_I( centre, remaining_pts, starting_polys[counter].poly, starting_polys[counter].zone, fin_polys[counter], zone_limit );
        }
    }
    
    for (int counter_1 = 0; counter_1 < starting_polys.size(); ++counter_1)
    {
        final_polys.insert( final_polys.end(), fin_polys[counter_1].begin(), fin_polys[counter_1].end() );
    }
    
    vector<double> vec( zone_limit, 0 );
    max_radii = vec;
    
    for (int counter = 0; counter < final_polys.size(); ++counter)
    {
        double max_radius = final_polys[counter].dist;
        
        if (max_radii[final_polys[counter].zone - 1] < max_radius) max_radii[final_polys[counter].zone - 1] = max_radius;
    }
}
