#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangle_2.h>

#include <thread>
#include <fstream>

#include "Input3D.h"

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;
typedef K::Vector_2 V2;
typedef K::Triangle_2 Tri;
typedef K::Line_2 L2;
typedef K::Segment_2 S2;

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

typedef K::Intersect_2 I2;

#include "Disk_Triangle_Intersection.h"

void Extract_Data_Pts_Brillouin_2D ( string const& directory3D, Input3D& input, int index, vector<P2> const& centres, vector<vector<vector<Tri>>> triangles, vector<double>const& cell_volume, vector<vector<double>>const& max_radii )
{
    string dir = directory3D + "Data/Lattice Packing Functions/Square.txt";
    
    ofstream ofs( dir );
    
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
    
    //vector<bool> nonzero( input.zone_limit, false );
    //vector<bool> zero_again( input.zone_limit, false );
    
    for (int counter_1 = 0; counter_1 < num_pts; ++counter_1)
    {
        double radius = counter_1 / (double)input.sample_rate;
        
        /*if (zero_again[input.zone_limit - 2])
        {
            input.max_radius = radius;
            
            ofs << setprecision( 10 ) << radius;
            
            for (int counter_2 = 0; counter_2 < input.zone_limit - 1; ++counter_2)
            {
                ofs << " " << tiny_num;
            }
            
            break;
        }*/
        
        vector<double> volume( input.zone_limit, 0 );
        
        for (int counter_2 = 0; counter_2 < centres.size(); ++counter_2)
        {
            Circle c( centres[counter_2], radius );
                
            for (int counter_3 = 0; counter_3 < input.zone_limit; ++counter_3)
            {
                if (max_radii[counter_2][counter_3] < radius + tiny_num)
                {
                    //if (counter_3 == 0 && zero_again[counter_3]) continue;
                    //if (counter_3 > 0 && zero_again[counter_3 - 1] && zero_again[counter_3]) continue;
                    
                    for (int counter_4 = 0; counter_4 < triangles[counter_2][counter_3].size(); ++counter_4)
                    {
                        volume[counter_3] += triangles[counter_2][counter_3][counter_4].area();
                    }
                }
                
                else
                {
                    //if (counter_3 == 0 && zero_again[counter_3]) continue;
                    //if (counter_3 > 0 && zero_again[counter_3 - 1] && zero_again[counter_3]) continue;
                    
                    for (int counter_4 = 0; counter_4 < triangles[counter_2][counter_3].size(); ++counter_4)
                    {
                        volume[counter_3] += Disk_Triangle_Intersection( c, triangles[counter_2][counter_3][counter_4] );
                    }
                }
            }
        }
        
        for (int counter_2 = 0; counter_2 < input.zone_limit; ++counter_2)
        {
            volume[counter_2] = volume[counter_2] / (double)cell_volume[counter_2];
        }
        
        /*if (radius >= 2.45 && radius <= 3.6)
        {
            cout << "volumes: " << radius << endl;
            
            for (int counter_2 = 0; counter_2 < input.zone_limit; ++counter_2)
            {
                cout << volume[counter_2] << endl;
            }
            
            cout << endl;
        }*/
        
        vector<double> pi( input.zone_limit );
        
        for (int counter_2 = 0; counter_2 < input.zone_limit - 1; ++counter_2)
        {
            //if (zero_again[counter_2]) pi[counter_2] = tiny_num;
            
            //else
            {
                pi[counter_2] = volume[counter_2] - volume[counter_2 + 1];
                
                if (abs( pi[counter_2] ) < tiny_num) pi[counter_2] = tiny_num;
                else if (pi[counter_2] < 0) pi[counter_2] = tiny_num;
            }
        }
        
        /*for (int counter_2 = 0; counter_2 < input.zone_limit - 1; ++counter_2)
        {
            if (!nonzero[counter_2])
            {
                if (pi[counter_2] > 1e-2) nonzero[counter_2] = true;
            }
            
            else if (!zero_again[counter_2])
            {
                if (pi[counter_2] < 1e-3) zero_again[counter_2] = true;
            }
        }*/
        
        ofs << setprecision( 10 ) << radius;
        
        for (int counter_2 = 0; counter_2 < input.zone_limit - 1; ++counter_2)
        {
            ofs << " " << pi[counter_2];
        }
        
        ofs << endl;
    }
    
    ofs.close();
}
