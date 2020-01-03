#include <gemmi/cif.hpp>

#include "Parameters.h"
#include "Packing_Functions3D.h"
#include "Make_Cells3D.h"
#include "Make_T2_Cells.h"
#include "Deformation.h"
#include "Cell_Data.h"
#include "Draw_Cells.h"
#include "Packing_Functions.h"
#include "GIF.h"
#include "Comparing_Entries.h"
#include "Print_Info.h"

#include "Obtain_T2_Centres.h"

int main ( int, char*[] )
{
    clock_t start_time = clock(); // Starts the clock measuring the runtime of the code.
    chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now(); // Starts the clock measuring the absolute time elapsed to complete the code.
    
    if (twoD) // Runs for 2D packing functions.
    {
        vector<Cell> cells;
        cells.reserve( input.iterations );
        
        for (int counter = 0; counter < input.iterations; ++counter)
        {
            Deformation( input, counter );
            
            Cell cell;
            
            Cell_Data( input, cell );
            
            cells.push_back( cell );
        }
        
        if (draw_cell)
        {
            Draw_Cells( cells );
            
            GIF( directory + "Graphs/Cells", "Cell_", input.iterations );
        }
        
        for (int counter = 0; counter < cells.size(); ++counter)
        {
            cout << "Iteration: " << counter << "." << endl;
            
            Packing_Functions( directory, input, cells[counter], counter );
        }
        
        GIF( directory + "Graphs/Deformation", "Deform", input.iterations );
        
        for (int counter = 0; counter < input.iterations; ++counter)
        {
            string str = "cd && cd '" + directory + "Graphs/' && /usr/local/Cellar/imagemagick/7.0.8-35/bin/convert Deformation/Deform" + to_string( counter ) + ".png Cells/Cell_" + to_string( counter ) + ".png +append Append/Append_" + to_string( counter ) + ".png";
            
            system( str.c_str() );
        }
        
        GIF( directory + "Graphs/Append", "Append_", input.iterations );
    }
    
    if (threeD) // Runs for 3D packing functions.
    {
        vector<Cell3D> cells; // Vector of cells.
        
        if (T2)
        {
            for (int counter = 0; counter < input3D.iterations; ++counter)
            {
                cout << "Iteration: " << counter << "." << endl;
                
                Make_T2_Cells( dataset_directory, input3D, cells, counter + 1 );
                
                Packing_Functions3D( directory3D, input3D, graph_params, cells[counter], counter + 1 );
            }
            
            double r = 7.346;
            int c = 0;
            
            //cout << Second_Order_Total_Volume( cells[c], r - 0.001, false ) / (double)cells[c].vol << endl;
            //cout << Second_Order_Total_Volume( cells[c], r, false ) / (double)cells[c].vol << endl;
            //cout << Second_Order_Total_Volume( cells[c], r + 0.001, false ) / (double)cells[c].vol << endl;
            //cout << Second_Order_Total_Volume( cells[c], r + 0.002, false ) / (double)cells[c].vol << endl;
            
            //cout << Third_Order_Total_Volume( cells[c], r - 0.001 ) / (double)cells[c].vol << endl;
            //cout << Third_Order_Total_Volume( cells[c], r ) / (double)cells[c].vol << endl;
            //cout << Third_Order_Total_Volume( cells[c], r + 0.001 ) / (double)cells[c].vol << endl;
            //cout << Third_Order_Total_Volume( cells[c], r + 0.002 ) / (double)cells[c].vol << endl;
             
            vector<Sphere> spheres;
            spheres.push_back( Sphere( cells[c].pts[30], r ) ); // 15 35
            spheres.push_back( Sphere( cells[c].pts[34], r ) );
            spheres.push_back( Sphere( cells[c].pts[39], r ) );
            spheres.push_back( Sphere( cells[c].pts[30], r + 0.001 ) );
            spheres.push_back( Sphere( cells[c].pts[34], r + 0.001 ) );
            spheres.push_back( Sphere( cells[c].pts[39], r + 0.001 ) );
            
            //cout << Two_Sphere_Intersection_Volume_Within_Cell( cells[c], spheres[0], spheres[1] ) << endl;
            //cout << Two_Sphere_Intersection_Volume_Within_Cell( cells[c], spheres[3], spheres[4] ) << endl;
            
            //cout << Three_Sphere_Intersection_Volume_Within_Cell( cells[c], spheres[3], spheres[4], spheres[5] ) / (double)cells[c].vol << endl;
            //cout << Three_Sphere_Intersection_Volume_Within_Cell( cells[c], spheres[0], spheres[1], spheres[2] ) / (double)cells[c].vol << endl;
             
            double d1 = Norm( spheres[1].c, spheres[2].c ), d2 = Norm( spheres[0].c, spheres[2].c ), d3 = Norm( spheres[0].c, spheres[1].c );
             
            V3 v = spheres[0].c - spheres[1].c;
            v = v / (double)Norm( v );
             
            double k = (spheres[1].r * spheres[1].r + d3 * d3 - spheres[0].r * spheres[0].r) / (double)(2 * d3);
             
            P3 pt = spheres[1].c + k * v;
             
            Pl3 p3( pt, v );
             
            v = spheres[0].c - spheres[2].c;
            v = v / (double)Norm( v );
             
            k = (spheres[2].r * spheres[2].r + d2 * d2 - spheres[0].r * spheres[0].r) / (double)(2 * d2);
             
            pt = spheres[2].c + k * v;
             
            Pl3 p2( pt, v );
             
            v = spheres[1].c - spheres[2].c;
            v = v / (double)Norm( v );
             
            k = (spheres[2].r * spheres[2].r + d1 * d1 - spheres[1].r * spheres[1].r) / (double)(2 * d1);
             
            pt = spheres[2].c + k * v;
             
            Pl3 p1( pt, v );
            
            //cout << Spherical_Cap_Volume_Within_Cell( cells[c], spheres[0], p3.opposite() ) << endl;
            
            //cout << Spherical_Wedge_Volume_Within_Cell( cells[c], spheres[2], p3.opposite(), p2 ) << endl;
            
            //cout << Sphere_Five_Plane_Intersection_Volume( spheres[2], p3.opposite(), p2, cells[c].planes[0].opposite(), cells[c].planes[1].opposite(), cells[c].planes[5].opposite(), 0 ) << endl;
            
            //cout << Sphere_Five_Plane_Intersection_Volume( spheres[2], cells[c].planes[1].opposite(), p2, p3.opposite(), cells[c].planes[2].opposite(), cells[c].planes[4].opposite(), 11 ) << endl;
            
            //cout << Non_Parallel_Lines_Case5B( spheres[2], cells[c].planes[4].opposite(), p3.opposite(), p2, cells[c].planes[2].opposite(), cells[c].planes[3].opposite(), 15 ) << endl;
            
            //cout << Non_Parallel_Lines_Case5B( spheres[2], cells[c].planes[0].opposite(), p3.opposite(), cells[c].planes[1].opposite(), p2, cells[c].planes[5].opposite(), 15 ) << endl;
            
            //cout << Sphere_Four_Plane_Intersection_Volume( spheres[2], cells[c].planes[5], p3, cells[c].planes[0], cells[c].planes[1] ) << endl;
            
            //cout << General_Spherical_Cone( spheres[0], p3, cells[c].planes[2], cells[c].planes[4] ) << endl;
            
            //cout << Parallel_Planes_Case5( spheres[1], p3, cells[c].planes[1].opposite(), p1.opposite(), cells[c].planes[0].opposite(), cells[c].planes[5].opposite() ) << endl;
            //cout << Parallel_Planes_Case5( spheres[3], p3, cells[c].planes[1].opposite(), p1.opposite(), cells[c].planes[0].opposite(), cells[c].planes[5].opposite() ) << endl;
            
            //cout << General_Spherical_Cone( spheres[0], p3.opposite(), cells[c].planes[0].opposite(), cells[c].planes[4].opposite() ) << endl;
            //cout << Circumradius( spheres[0].c, spheres[1].c, spheres[2].c ) << endl;
            //cout << General_Spherical_Wedge( spheres[2], p3.opposite(), p2 ) << endl;
            //cout << General_Spherical_Wedge( spheres[2], p3, p1 ) << endl;
        }
        
        else
        {
            Make_Cells3D( input3D, cells ); // Initialised the vector of cells.
            
            for (int counter = 0; counter < cells.size(); ++counter) // Looping over the vector of cells.
            {
                cout << "Iteration: " << counter << "." << endl;
                
                Packing_Functions3D( directory3D, input3D, graph_params, cells[counter], counter );
            }
            
            if (input3D.deformation_type != 0) GIF( directory3D + "Graphs/Deformation", "Deform", input3D.iterations );
        }
    }
    
    if (comparing)
    {
        vector<int> length_diff;
        length_diff.reserve( 5688 );
        vector<double> pi_1, pi_2, pi_3;
        pi_1.reserve( 5688 );
        pi_2.reserve( 5688 );
        pi_3.reserve( 5688 );
        
        for (int counter = 0; counter < 5688; ++counter)
        {
            string filename_1 = directory3D + "Data/T2 Packing Functions/Dataset/" + to_string( counter + 1 ) + ".txt";
            string filename_2 = directory3D + "Data/T2 Packing Functions/Dataset Copy/" + to_string( counter + 1 ) + ".txt";
            filename_1 = directory3D + "Data/T2 Packing Functions/alphaex.txt";
            
            int difference_in_length;
            double max_diff_pi_1, max_diff_pi_2, max_diff_pi_3;
            
            Comparing_Entries( filename_1, filename_2, max_diff_pi_1, max_diff_pi_2, max_diff_pi_3, difference_in_length );
            
            length_diff.push_back( difference_in_length );
            pi_1.push_back( max_diff_pi_1 );
            pi_2.push_back( max_diff_pi_2 );
            pi_3.push_back( max_diff_pi_3 );
        }
        
        ofstream ofs( directory3D + "Data/T2 Packing Functions/Dataset_Comparison.txt" );
        
        for (int counter = 0; counter < 5688; ++counter)
        {
            ofs << counter + 1 << " " << pi_1[counter] << " " << pi_2[counter] << " " << pi_3[counter] << " " << pi_1[counter] + pi_2[counter] + pi_3[counter] << " " << length_diff[counter] << endl;
        }
        
        int entry_1 = 0, entry_2 = 0, entry_3 = 0;
        double overall_max_pi_1 = 0, overall_max_pi_2 = 0, overall_max_pi_3 = 0;
        
        for (int counter = 0; counter < 5688; ++counter)
        {
            if (overall_max_pi_1 < pi_1[counter])
            {
                overall_max_pi_1 = pi_1[counter];
                entry_1 = counter;
            }
            
            if (overall_max_pi_2 < pi_2[counter])
            {
                overall_max_pi_2 = pi_2[counter];
                entry_2 = counter;
            }
            
            if (overall_max_pi_3 < pi_3[counter])
            {
                overall_max_pi_3 = pi_3[counter];
                entry_3 = counter;
            }
        }
        
        //cout << entry_1 << " " << overall_max_pi_1 << endl;
        //cout << entry_2 << " " << overall_max_pi_2 << endl;
        //cout << entry_3 << " " << overall_max_pi_3 << endl;
        
        entry_1 = entry_2 = entry_3 = 0;
        int entry = 0;
        overall_max_pi_1 = overall_max_pi_2 = overall_max_pi_3 = big_num;
        double sum_error = big_num;
        
        for (int counter = 0; counter < 5688; ++counter)
        {
            if (overall_max_pi_1 > pi_1[counter] && length_diff[counter] < 2)
            {
                overall_max_pi_1 = pi_1[counter];
                entry_1 = counter;
            }
            
            if (overall_max_pi_2 > pi_2[counter] && length_diff[counter] < 2)
            {
                overall_max_pi_2 = pi_2[counter];
                entry_2 = counter;
            }
            
            if (overall_max_pi_3 > pi_3[counter] && length_diff[counter] < 2)
            {
                overall_max_pi_3 = pi_3[counter];
                entry_3 = counter;
            }
            
            if (sum_error > pi_1[counter] + pi_2[counter] + pi_3[counter] && length_diff[counter] < 2)
            {
                sum_error = pi_1[counter] + pi_2[counter] + pi_3[counter];
                entry = counter;
            }
        }
        
        cout << entry_1 + 1 << " " << overall_max_pi_1 << endl;
        cout << entry_2 + 1 << " " << overall_max_pi_2 << endl;
        cout << entry_3 + 1 << " " << overall_max_pi_3 << endl;
        cout << entry + 1 << " " << sum_error << endl;
        
        cout << endl;
        
        for (int counter = 0; counter < 5688; ++counter)
        {
            if (pi_1[counter] + pi_2[counter] + pi_3[counter] < sum_error + 0.01 && length_diff[counter] < 2) cout << counter + 1 << " " << pi_1[counter] + pi_2[counter] + pi_3[counter] << endl;
        }
    }
    
    Print_Info( start_time, start );
    
    return 0;
}
