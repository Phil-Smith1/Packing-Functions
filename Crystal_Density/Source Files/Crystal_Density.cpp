// Code for computing Packing Functions.

// Include for gemmi, for parsing CIFs.

#include <gemmi/cif.hpp>

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
        int perim = 4;
        
        int zone_limit = 11;
        
        double cube_size = 10;
        
        P3_E centre_E = P3_E( 0, 0, 0 );
        P3 centre = P3( 0, 0, 0 );
        
        vector<vector<Tetrahedron>> zones_of_tetras;
        
        clock_t time_1 = clock();
        
        Compute_Brillouin_Zones( perim, zone_limit, cube_size, centre_E, zones_of_tetras );
        
        clock_t time_2 = clock();
        
        double time_taken = (time_2 - time_1) / (double)CLOCKS_PER_SEC;
        
        cout << "Time taken = " << time_taken << endl;
        
        vector<vector<vector<Pl3>>> tetra_cells;
        
        Extract_Tetra_Cells( zones_of_tetras, zone_limit, tetra_cells );
        
        string dir = directory3D + "Data/Results.txt";
        
        ofstream ofs( dir );
        
        double num_pts = 2 * 300;
        
        double final_radius = 0;
        
        for (double counter = 0; counter < num_pts; ++counter)
        {
            double radius = counter / (double)300;
            
            Sphere s( centre, radius );
            
            double volume1 = 0;
            double volume2 = 0;
            double volume3 = 0;
            double volume4 = 0;
            double volume5 = 0;
            double volume6 = 0;
            double volume7 = 0;
            double volume8 = 0;
            double volume9 = 0;
            
            for (int counter = 0; counter < tetra_cells[0].size(); ++counter)
            {
                volume1 += Sphere_Tetrahedron_Intersection( s, tetra_cells[0][counter] );
            }
            
            for (int counter = 0; counter < tetra_cells[1].size(); ++counter)
            {
                volume2 += Sphere_Tetrahedron_Intersection( s, tetra_cells[1][counter] );
            }
            
            for (int counter = 0; counter < tetra_cells[2].size(); ++counter)
            {
                volume3 += Sphere_Tetrahedron_Intersection( s, tetra_cells[2][counter] );
            }
            
            for (int counter = 0; counter < tetra_cells[3].size(); ++counter)
            {
                volume4 += Sphere_Tetrahedron_Intersection( s, tetra_cells[3][counter] );
            }
            
            for (int counter = 0; counter < tetra_cells[4].size(); ++counter)
            {
                volume5 += Sphere_Tetrahedron_Intersection( s, tetra_cells[4][counter] );
            }
            
            for (int counter = 0; counter < tetra_cells[5].size(); ++counter)
            {
                volume6 += Sphere_Tetrahedron_Intersection( s, tetra_cells[5][counter] );
            }
            
            for (int counter = 0; counter < tetra_cells[6].size(); ++counter)
            {
                volume7 += Sphere_Tetrahedron_Intersection( s, tetra_cells[6][counter] );
            }
            
            for (int counter = 0; counter < tetra_cells[7].size(); ++counter)
            {
                volume8 += Sphere_Tetrahedron_Intersection( s, tetra_cells[7][counter] );
            }
            
            for (int counter = 0; counter < tetra_cells[8].size(); ++counter)
            {
                volume9 += Sphere_Tetrahedron_Intersection( s, tetra_cells[8][counter] );
            }
            
            if (abs( volume1 ) < tiny_num) volume1 = tiny_num;
            if (abs( volume2 ) < tiny_num) volume2 = tiny_num;
            if (abs( volume3 ) < tiny_num) volume3 = tiny_num;
            if (abs( volume4 ) < tiny_num) volume4 = tiny_num;
            if (abs( volume5 ) < tiny_num) volume5 = tiny_num;
            if (abs( volume6 ) < tiny_num) volume6 = tiny_num;
            if (abs( volume7 ) < tiny_num) volume7 = tiny_num;
            if (abs( volume8 ) < tiny_num) volume8 = tiny_num;
            if (abs( volume9 ) < tiny_num) volume9 = tiny_num;
            
            double pi_1 = volume1 - volume2;
            double pi_2 = volume2 - volume3;
            double pi_3 = volume3 - volume4;
            double pi_4 = volume4 - volume5;
            double pi_5 = volume5 - volume6;
            double pi_6 = volume6 - volume7;
            double pi_7 = volume7 - volume8;
            double pi_8 = volume8 - volume9;
            double pi_9 = volume9;
            
            if (pi_9 > tiny_num)
            {
                final_radius = radius;
                break;
            }
            
            ofs << setprecision( 10 ) << radius << " " << pi_1 << " " << pi_2 << " " << pi_3 << " " << pi_4 << " " << pi_5 << " " << pi_6 << " " << pi_7 << " " << pi_8 << endl;
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
        
        gp << "plot 'Results.txt' using 1:2 smooth csplines ls 1 title '{/Symbol p}_1(r)', 'Results.txt' using 1:3 smooth csplines ls 2 title '{/Symbol p}_2(r)', 'Results.txt' using 1:4 smooth csplines ls 3 title '{/Symbol p}_3(r)', 'Results.txt' using 1:5 smooth csplines ls 4 title '{/Symbol p}_4(r)', 'Results.txt' using 1:6 smooth csplines ls 5 title '{/Symbol p}_5(r)', 'Results.txt' using 1:7 smooth csplines ls 6 title '{/Symbol p}_6(r)', 'Results.txt' using 1:8 smooth csplines ls 7 title '{/Symbol p}_7(r)', 'Results.txt' using 1:9 smooth csplines ls 8 title '{/Symbol p}_8(r)'\n";
    }
    
    Print_Info( start_time, start );
    
    return 0;
}
