#include "Input3D.h"
#include "Sphere_Tetrahedron_Intersection.h"

#include <fstream>
#include <thread>

void Data_Pts_For_Given_Radius ( Input3D const input, int counter_1, vector<double>& results, vector<P3>const centres, vector<vector<vector<vector<Pl3>>>>const tetra_cells, vector<vector<double>>const cell_volume, vector<vector<double>>const max_radii )
{
    double radius = counter_1 / (double)input.sample_rate;
    
    results[0] = radius;
    
    vector<double> volume( input.zone_limit, 0 );
    
    for (int counter_2 = 0; counter_2 < centres.size(); ++counter_2)
    {
        Sphere s( centres[counter_2], radius );
        
        for (int counter_3 = 0; counter_3 < input.zone_limit; ++counter_3)
        {
            if (max_radii[counter_2][counter_3] < radius)
            {
                volume[counter_3] = 1;
            }
            
            else
            {
                for (int counter_4 = 0; counter_4 < tetra_cells[counter_2][counter_3].size(); ++counter_4)
                {
                    volume[counter_3] += Sphere_Tetrahedron_Intersection( s, tetra_cells[counter_2][counter_3][counter_4] );
                }
                
                volume[counter_3] = volume[counter_3] / (double)cell_volume[counter_2][counter_3];
            }
        }
    }
    
    for (int counter_2 = 0; counter_2 < input.zone_limit - 1; ++counter_2)
    {
        results[counter_2 + 1] = volume[counter_2] - volume[counter_2 + 1];
        
        if (abs( results[counter_2 + 1] ) < tiny_num) results[counter_2 + 1] = tiny_num;
        else if (results[counter_2 + 1] < 0) results[counter_2 + 1] = tiny_num;
    }
}

void Extract_Data_Pts_Brillouin ( string const& directory3D, Input3D& input, int index, vector<P3> const& centres, vector<vector<vector<vector<Pl3>>>>const& tetra_cells, vector<vector<double>>const& cell_volume, vector<vector<double>>const& max_radii )
{
    bool use_thread = true;
    
    if (use_thread)
    {
        double max_radius = 0;
        
        for (int counter = 0; counter < centres.size(); ++counter)
        {
            double rad = max_radii[counter][max_radii[counter].size() - 1];
            
            if (rad > max_radius) max_radius = rad;
        }
        
        int num_pts = max_radius * input.sample_rate + 1;
        
        input.max_radius = (num_pts - 1) / (double)input.sample_rate;
        
        if (num_pts < max_radius * input.sample_rate + 1)
        {
            ++num_pts;
            input.max_radius = (num_pts - 1) / (double)input.sample_rate;
        }
        
        vector<vector<double>> results( num_pts );
        vector<thread> thr;
        
        for (int counter = 0; counter < num_pts; ++counter)
        {
            results[counter].resize( input.zone_limit + 1 );
            thr.push_back( thread( Data_Pts_For_Given_Radius, input, counter, ref( results[counter] ), centres, tetra_cells, cell_volume, max_radii ) );
        }
        
        for (int counter = 0; counter < num_pts; ++counter)
        {
            thr[counter].join();
        }
        
        string dir = directory3D + "Data/Brill/" + to_string( index ) + ".txt";
        
        ofstream ofs( dir );
        
        ofs << setprecision( 10 ) << results[0][0];
        
        for (int counter = 0; counter < input.zone_limit - 1; ++counter)
        {
            ofs << " " << results[0][counter + 1];
        }
        
        for (int counter_1 = 1; counter_1 < num_pts; ++counter_1)
        {
            ofs << endl;
            
            ofs << setprecision( 10 ) << results[counter_1][0];
            
            for (int counter_2 = 0; counter_2 < input.zone_limit - 1; ++counter_2)
            {
                ofs << " " << results[counter_1][counter_2 + 1];
            }
        }
    }
    
    else
    {
        string dir = directory3D + "Data/Brill/" + to_string( index ) + ".txt";
        
        ofstream ofs( dir );
        
        input.max_radius = 20;
        
        double num_pts = input.max_radius * input.sample_rate;
        
        vector<bool> nonzero( input.zone_limit, false );
        vector<bool> zero_again( input.zone_limit, false );
        
        for (int counter_1 = 0; counter_1 < num_pts; ++counter_1)
        {
            double radius = counter_1 / (double)input.sample_rate;
            
            if (zero_again[input.zone_limit - 2])
            {
                input.max_radius = radius;
                
                ofs << setprecision( 10 ) << radius;
                
                for (int counter_2 = 0; counter_2 < input.zone_limit - 1; ++counter_2)
                {
                    ofs << " " << tiny_num;
                }
                
                break;
            }
            
            vector<double> volume( input.zone_limit, 0 );
            
            for (int counter_2 = 0; counter_2 < centres.size(); ++counter_2)
            {
                Sphere s( centres[counter_2], radius );
                
                for (int counter_3 = 0; counter_3 < input.zone_limit; ++counter_3)
                {
                    if (counter_3 == 0 && zero_again[counter_3]) continue;
                    if (counter_3 > 0 && zero_again[counter_3 - 1] && zero_again[counter_3]) continue;
                    
                    for (int counter_4 = 0; counter_4 < tetra_cells[counter_2][counter_3].size(); ++counter_4)
                    {
                        /*if (Sphere_Tetrahedron_Intersection( s, tetra_cells[counter_2][counter_3][counter_4] ) < -1e-3)
                        {
                            cout << counter_2 << endl;
                            cout << counter_3 << endl;
                            cout << counter_4 << endl;
                            cout << Sphere_Tetrahedron_Intersection( s, tetra_cells[counter_2][counter_3][counter_4] ) << endl;
                            cout << s.c << endl;
                            cout << s.r << endl;
                            cout << tetra_cells[counter_2][counter_3][counter_4][0] << endl;
                            cout << tetra_cells[counter_2][counter_3][counter_4][1] << endl;
                            cout << tetra_cells[counter_2][counter_3][counter_4][2] << endl;
                            cout << tetra_cells[counter_2][counter_3][counter_4][3] << endl << endl;
                        }*/
                        
                        volume[counter_3] += Sphere_Tetrahedron_Intersection( s, tetra_cells[counter_2][counter_3][counter_4] );
                    }
                    
                    volume[counter_3] = volume[counter_3] / (double)cell_volume[counter_2][counter_3];
                }
            }
            
            vector<double> pi( input.zone_limit );
            
            for (int counter_2 = 0; counter_2 < input.zone_limit - 1; ++counter_2)
            {
                if (zero_again[counter_2]) pi[counter_2] = tiny_num;
                
                else
                {
                    pi[counter_2] = volume[counter_2] - volume[counter_2 + 1];
                    
                    if (abs( pi[counter_2] ) < tiny_num) pi[counter_2] = tiny_num;
                    else if (pi[counter_2] < 0) pi[counter_2] = tiny_num;
                }
            }
            
            for (int counter_2 = 0; counter_2 < input.zone_limit - 1; ++counter_2)
            {
                if (!nonzero[counter_2])
                {
                    if (pi[counter_2] > 1e-2) nonzero[counter_2] = true;
                }
                
                else if (!zero_again[counter_2])
                {
                    if (pi[counter_2] < 1e-3) zero_again[counter_2] = true;
                }
            }
            
            ofs << setprecision( 10 ) << radius;
            
            for (int counter_2 = 0; counter_2 < input.zone_limit - 1; ++counter_2)
            {
                ofs << " " << pi[counter_2];
            }
            
            ofs << endl;
        }
        
        ofs.close();
    }
}
