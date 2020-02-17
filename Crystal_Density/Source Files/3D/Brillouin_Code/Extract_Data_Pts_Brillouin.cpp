#include "Input3D.h"
#include "Sphere_Tetrahedron_Intersection.h"

#include <fstream>

void Extract_Data_Pts_Brillouin ( string const& directory3D, Input3D& input, int index, vector<P3> const& centres, vector<vector<vector<vector<Pl3>>>>const& tetra_cells, double cell_volume )
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
            Sphere s1( centres[counter_2], radius + 0.1 );
            
            for (int counter_3 = 0; counter_3 < input.zone_limit; ++counter_3)
            {
                if (counter_3 == 0 && zero_again[counter_3]) continue;
                if (counter_3 > 0 && zero_again[counter_3 - 1] && zero_again[counter_3]) continue;
                
                for (int counter_4 = 0; counter_4 < tetra_cells[counter_2][counter_3].size(); ++counter_4)
                {
                    volume[counter_3] += Sphere_Tetrahedron_Intersection( s, tetra_cells[counter_2][counter_3][counter_4] );
                }
            }
        }
        
        vector<double> pi( input.zone_limit );
        
        for (int counter_2 = 0; counter_2 < input.zone_limit - 1; ++counter_2)
        {
            if (zero_again[counter_2]) pi[counter_2] = tiny_num;
            
            else
            {
                pi[counter_2] = volume[counter_2] - volume[counter_2 + 1];
                pi[counter_2] = pi[counter_2] / (double)cell_volume;
                
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
