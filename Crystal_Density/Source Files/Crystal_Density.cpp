// Code for computing Packing Functions.

// Include for gemmi, for parsing CIFs.

#include <gemmi/cif.hpp>

#include <algorithm>
#include <thread>

// Includes.

#include "Parameters.h"
#include "Packing_Functions3D.h"
#include "Make_Cells3D.h"
#include "Make_T2_Cells.h"
#include "Deformation.h"
#include "Cell_Data.h"
#include "Draw_Cells.h"
#include "Packing_Functions.h"
#include "GIF.h"
#include "Compare_Two_Files.h"
#include "Dataset_Dataset_Analysis.h"
#include "Manipulate_Dataset_Dataset_Analysis.h"
#include "File_Dataset_Analysis.h"
#include "Manipulate_File_Analysis.h"
#include "Read_Dataset_Matrix.h"
#include "Print_Info.h"

#include "Brillouin_Code.h"
#include "Sphere_Tetrahedron_Intersection.h"

// Main.

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
        
        if (T2) // Runs for T2 crystals.
        {
            for (int counter = 0; counter < input3D.iterations; ++counter)
            {
                cout << "Iteration: " << counter << "." << endl;
                
                Make_T2_Cells( dataset_directory, input3D, cells, counter + 1 ); // Adds a new T2 cell.
                
                Packing_Functions3D( directory3D, input3D, graph_params, cells[counter], counter + 1 );
            }
        }
        
        else // Runs for custom point clouds.
        {
            Make_Cells3D( input3D, cells ); // Initialises the vector of cells.
            
            for (int counter = 0; counter < cells.size(); ++counter) // Looping over the vector of cells.
            {
                cout << "Iteration: " << counter << "." << endl;
                
                Packing_Functions3D( directory3D, input3D, graph_params, cells[counter], counter );
            }
            
            if (input3D.deformation_type != 0) GIF( directory3D + "Graphs/Deformation", "Deform", input3D.iterations );
        }
    }
    
    if (analysis)
    {
        //string filename_1 = directory3D + "Data/T2 Packing Functions/Synthesised Crystals/beta.txt";
        //string filename_2 = directory3D + "Data/T2 Packing Functions/Synthesised Crystals/delta.txt";
        
        //Compare_Two_Files( filename_1, filename_2 );
        
        //File_Dataset_Analysis( directory3D );
        
        Manipulate_File_Analysis( directory3D );
    }
    
    if (brillouin)
    {
        int perim = 5;
        
        int zone_limit = 5;
        
        P3_E centre_E = P3_E( 0, 0, 0 );
        P3 centre = P3( 0, 0, 0 );
        
        V3_E v1 = V3_E( 5 / (double)6, -1 / (double)6, -1 / (double)6 );
        V3_E v2 = V3_E( -1 / (double)6, 5 / (double)6, -1 / (double)6 );
        V3_E v3 = V3_E( -1 / (double)6, -1 / (double)6, 5 / (double)6 );
        
        multimap<double, P3_E> pts;
        
        for (int counter_1 = -perim; counter_1 < perim + 1; ++counter_1)
        {
            for (int counter_2 = -perim; counter_2 < perim + 1; ++counter_2)
            {
                for (int counter_3 = -perim; counter_3 < perim + 1; ++counter_3)
                {
                    if (counter_1 == 0 && counter_2 == 0 && counter_3 == 0) continue;
                    
                    V3_E v = counter_1 * v1 + counter_2 * v2 + counter_3 * v3;
                    
                    P3_E p = P3_E( v.x(), v.y(), v.z() );
                    
                    double dist = to_double( squared_distance( centre_E, p ) );
                    
                    pts.insert( pair<double, P3_E>( dist, p ) );
                }
            }
        }
        
        vector<vector<Tetrahedron>> zones_of_tetras;
        
        clock_t time_1 = clock();
        
        Compute_Brillouin_Zones( pts, zone_limit, centre_E, zones_of_tetras );
        
        clock_t time_2 = clock();
        
        double time_taken = (time_2 - time_1) / (double)CLOCKS_PER_SEC;
        
        cout << "Time taken = " << time_taken << endl;
        
        vector<vector<vector<Pl3>>> tetra_cells;
        
        Extract_Tetra_Cells( zones_of_tetras, zone_limit, tetra_cells );
        
        double cell_volume = 0;
        
        for (int counter = 0; counter < zones_of_tetras[0].size(); ++counter)
        {
            cell_volume += to_double( zones_of_tetras[0][counter].volume() );
        }
        
        string dir = directory3D + "Data/Results.txt";
        
        ofstream ofs( dir );
        
        double num_pts = 2 * 300;
        
        double final_radius = 2;
        
        for (double counter_1 = 0; counter_1 < num_pts; ++counter_1)
        {
            double radius = counter_1 / (double)300;
            
            Sphere s( centre, radius );
            
            vector<double> volume( zone_limit, 0 );
            
            for (int counter_2 = 0; counter_2 < zone_limit; ++counter_2)
            {
                for (int counter_3 = 0; counter_3 < tetra_cells[counter_2].size(); ++counter_3)
                {
                    volume[counter_2] += Sphere_Tetrahedron_Intersection( s, tetra_cells[counter_2][counter_3] );
                }
            }
            
            for (int counter_2 = 0; counter_2 < zone_limit; ++counter_2)
            {
                if (abs( volume[counter_2] ) < tiny_num) volume[counter_2] = tiny_num;
            }
            
            vector<double> pi( zone_limit );
            
            for (int counter_2 = 0; counter_2 < zone_limit - 1; ++counter_2)
            {
                pi[counter_2] = volume[counter_2] - volume[counter_2 + 1];
            }
            
            pi[zone_limit - 1] = volume[zone_limit - 1];
            
            if (pi[zone_limit - 1] > tiny_num)
            {
                final_radius = radius;
                break;
            }
            
            ofs << setprecision( 10 ) << radius;
            
            for (int counter_2 = 0; counter_2 < zone_limit - 1; ++counter_2)
            {
                ofs << " " << pi[counter_2] / (double)cell_volume;
            }
            
            ofs << endl;
        }
        
        ofs.close();
        
        Gnuplot gp;
        
        gp << "cd \"" << directory3D + "Data/" << "\"\n";
        
        gp << "set terminal pdfcairo size 8.5, 3.5\n";
        
        gp << "set border 3\n";
        gp << "set grid\n";
        gp << "set bmargin 4.5\n";
        gp << "set lmargin 8.5\n";
        
        if (true)
        {
            gp << "set tmargin 5\n";
            gp << "set title '" << graph_params.title_str << "' font ', 20' offset 0, 2\n";
        }
        
        else gp << "set tmargin 3\n";
        
        gp << "set rmargin 2\n";
        
        gp << "set ylabel '{/Symbol p}_i(r)' font ', 20' offset -0.5, 0\n";
        gp << "set xlabel 'Radius of Balls' font ', 20' offset 0, -0.3\n";
        
        gp << "set xrange [0: " << final_radius << "]\n";
        gp << "set yrange [0: " << 1 << "]\n";
        gp << "set xtics font ', 18'\n";
        gp << "set ytics font ', 18'\n";
        
        gp << "set key horizontal at graph 0.5, graph 1.04 center bottom font ', 18'\n";
        
        gp << "set style line 1 lc rgb '#0d61ec' lw 3\n";
        gp << "set style line 2 lc rgb '#24ae1d' lw 3\n";
        gp << "set style line 3 lc rgb '#ffae00' lw 3\n";
        gp << "set style line 4 lc rgb '#e70000' lw 3\n";
        gp << "set style line 5 lc rgb '#db0dec' lw 3\n";
        gp << "set style line 6 lc rgb '#7B0985' lw 3\n";
        gp << "set style line 7 lc rgb '#87663E' lw 3\n";
        gp << "set style line 8 lc rgb '#000000' lw 3\n";
        gp << "set style line 9 lc rgb '#000000' pt 7 ps 0.5\n";
        
        gp << "set output \"Packing Functions.pdf\"\n";
        
        gp << "set samples 1000\n";
        
        string plot = "plot 'Results.txt' using 1:2 smooth csplines ls 1 title '{/Symbol p}_1(r)'";
        
        for (int counter = 1; counter < zone_limit - 1; ++counter)
        {
            plot += ", 'Results.txt' using 1:" + to_string( counter + 2 ) + "smooth csplines ls " + to_string( counter + 1 ) + " title '{/Symbol p}_" + to_string( counter + 1 ) + "(r)'";
        }
        
        plot += "\n";
        
        gp << plot;
    }
    
    Print_Info( start_time, start );
    
    return 0;
}
