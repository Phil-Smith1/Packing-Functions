// Code for computing Packing Functions.

// Include for gemmi, for parsing CIFs.

#define BOOST_HAS_THREADS

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

#include "Preprocessing_T2_For_Brillouin.h"
#include "Compute_Brillouin_Zones.h"
#include "Extract_Tetra_Cells.h"
#include "Extract_Data_Pts_Brillouin.h"
#include "Plot_Graph_Brillouin.h"

#include "Compute_Brillouin_Zones_2D.h"
#include "Extract_Data_Pts_Brillouin_2D.h"

// Main.

int main ( int, char*[] )
{
    clock_t start_time = clock(); // Starts the clock measuring the runtime of the code.
    
    chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now(); // Starts the clock measuring the absolute time elapsed to complete the code.
    
    if (twoD) // Runs for 2D packing functions.
    {
        /*vector<Cell> cells;
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
        }*/
        
        /*GIF( directory + "Graphs/Deformation", "Deform", input.iterations );
        
        for (int counter = 0; counter < input.iterations; ++counter)
        {
            string str = "cd && cd '" + directory + "Graphs/' && /usr/local/Cellar/imagemagick/7.0.8-35/bin/convert Deformation/Deform" + to_string( counter ) + ".png Cells/Cell_" + to_string( counter ) + ".png +append Append/Append_" + to_string( counter ) + ".png";
            
            system( str.c_str() );
        }
        
        GIF( directory + "Graphs/Append", "Append_", input.iterations );*/
    }
    
    /*if (threeD) // Runs for 3D packing functions.
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
    }*/
    
    if (analysis)
    {
        string filename_1 = "/Users/philsmith/Documents/Work/Xcode Projects/Crystal_Density/3D/Data/Completeness Tests 2/K 2/A.txt";
        string filename_2 = "/Users/philsmith/Documents/Work/Xcode Projects/Crystal_Density/3D/Data/Completeness Tests 2/K 2/Q.txt";
        
        Compare_Two_Files( filename_1, filename_2 );
        
        //File_Dataset_Analysis( directory3D );
        
        //Manipulate_File_Analysis( directory3D );
        
        /*ifstream ifs_1( filename_1 );
        ifstream ifs_2( filename_2 );
        
        vector<double> vec1, vec2;
        
        string line_data;
        
        while (getline( ifs_1, line_data ))
        {
            stringstream stream;
            
            double val;
            
            stream << line_data;
            
            stream >> val;
            
            vec1.push_back( val );
        }
        
        while (getline( ifs_2, line_data ))
        {
            stringstream stream;
            
            double val;
            
            stream << line_data;
            
            stream >> val;
            
            vec2.push_back( val );
        }
        
        for (int counter = 0; counter < vec1.size(); ++counter)
        {
            double diff = vec1[counter] - vec2[counter];
            
            if (diff > 0)
            {
                cout << vec1[counter] << endl;
                cout << vec2[counter] << endl;
                cout << diff << endl;
                cout << counter << endl << endl;
            }
        }*/
    }
    
    if (brillouin)
    {
        if (twoD)
        {
            int k = 2;
            int point_set = 2;
            
            //P2 p1 = P2( 10, 0 ), p2 = P2( 0, 1 / (double)(k - 0.5) );
            
            //P2 p1 = P2( 2 * k + 6, 0 ), p2 = P2( 0, k + 2 );
            
            P2 p1 = P2( 1, 0 ), p2 = P2( 0, 1 );
            
            vector<P2> int_pts;
            
            int_pts.push_back( P2( 0, 0 ) );
            int_pts.push_back( P2( 0.25, 0 ) );
            
            /*int_pts.push_back( P2( 0.1, 0 ) );
            if (point_set == 1) int_pts.push_back( P2( 0.2, 0 ) );
            else int_pts.push_back( P2( 0.4, 0 ) );
            int_pts.push_back( P2( 0.5, 0 ) );
            int_pts.push_back( P2( 0.6, 0 ) );*/
            
            /*for (int counter_1 = 0; counter_1 < 2 * k + 6; ++counter_1)
            {
                for (int counter_2 = 0; counter_2 < k + 2; ++counter_2)
                {
                    if (counter_1 == 0 && counter_2 == 0) continue;
                    
                    if (point_set == 1)
                    {
                        if (counter_1 == k + 2 && counter_2 == 0) continue;
                    }
                    
                    if (point_set == 2)
                    {
                        if (counter_1 == k + 3 && counter_2 == 0) continue;
                    }
                    
                    int_pts.push_back( P2( counter_1, counter_2 ) );
                }
            }*/
            
            vector<P2> int_pts_coords;
            vector<P2> centres;
            
            for (int counter = 0; counter < int_pts.size(); ++counter)
            {
                int_pts_coords.push_back( P2( int_pts[counter].x() * p1.x() + int_pts[counter].y() * p2.x(), int_pts[counter].x() * p1.y() + int_pts[counter].y() * p2.y() ) );
                
                //int_pts_coords.push_back( int_pts[counter] );
                
                centres.push_back( int_pts_coords[counter] );
            }
            
            vector<multimap<double, P2>> pts;
            
            V2 v1 = V2( p1.x(), p1.y() );
            V2 v2 = V2( p2.x(), p2.y() );
            
            for (int counter_1 = 0; counter_1 < centres.size(); ++counter_1)
            {
                multimap<double, P2> copy;
                
                for (int counter_2 = 0; counter_2 < centres.size(); ++counter_2)
                {
                    for (int counter_3 = -perim; counter_3 < perim + 1; ++counter_3)
                    {
                        for (int counter_4 = -perim; counter_4 < perim + 1; ++counter_4)
                        {
                            if (counter_3 == 0 && counter_4 == 0 && counter_2 == counter_1) continue;
                            
                            V2 v = counter_3 * v1 + counter_4 * v2;
                            
                            P2 p = centres[counter_2] + v;
                            
                            double dist = squared_distance( centres[counter_1], p );
                            
                            copy.insert( pair<double, P2>( dist, p ) );
                        }
                    }
                }
                
                pts.push_back( copy );
            }
            
            vector<P2> draw_pts;
            
            draw_pts.push_back( centres[0] );
            
            for (int counter = 0; counter < pts[0].size(); ++counter)
            {
                auto iter = pts[0].begin();
                
                for (int counter_2 = 0; counter_2 < counter; ++counter_2)
                {
                    ++iter;
                }
                
                draw_pts.push_back( iter->second );
            }
            
            Draw_Unit_Cell( p1, p2, draw_pts );
            
            vector<vector<vector<Tri>>> triangles( centres.size() );
            
            vector<vector<double>> max_radii( centres.size() );
            
            vector<double> cell_volume( zone_limit, 0 );
            
            for (int counter = 0; counter < centres.size(); ++counter)
            {
                Compute_Brillouin_Zones_2D( pts[counter], zone_limit, centres[counter], triangles[counter], max_radii[counter], cell_volume );
            }
            
            for (int counter = 0; counter < zone_limit; ++counter)
            {
                //cout << cell_volume[counter] << endl;
            }
            
            Extract_Data_Pts_Brillouin_2D( directory3D, input3D, k, centres, triangles, cell_volume, max_radii );
            
            Circle c1( centres[0], 3.53 );
            Circle c2( centres[0], 3.54 );
            
            Circle c( centres[0], 10 );
            
            /*for (int counter_1 = 0; counter_1 < centres.size(); ++counter_1)
            {
                for (int counter_2 = 0; counter_2 < zone_limit; ++counter_2)
                {
                    cout << max_radii[counter_1][counter_2] << endl;
                }
            }*/
            
            Tri t = triangles[0][4][0];
            
            //cout << Disk_Triangle_Intersection( c, t ) << endl;
            
            /*for (int counter = 0; counter< triangles[0][4].size(); ++counter)
            {
                Tri t = triangles[0][4][counter];
                
                cout << t.area() << endl;
                //cout << Disk_Triangle_Intersection( c1, t ) << endl;
                //cout << Disk_Triangle_Intersection( c2, t ) << endl;
            }*/
            
            Gnuplot gp;
            
            gp << "cd \"" << directory3D << "\"\n";
            
            gp << "set terminal pdfcairo size 5, 3.5\n";
            
            gp << "set border 3\n";
            gp << "set grid\n";
            gp << "set bmargin 4.5\n";
            gp << "set lmargin 9\n";
            
            if (graph_params.title)
            {
                gp << "set tmargin 5\n";
                //gp << "set title 'Density Functions for the Square Lattice' font ', 20' offset 0, 4\n";
            }
            
            else gp << "set tmargin 3\n";
            
            gp << "set rmargin 2\n";
            
            gp << "set ylabel '{/Symbol y}@_k^A(t)' font ', 20' offset -0.5, 0\n";
            gp << "set xlabel 'Radius of Balls' font ', 20' offset 0, -0.3\n";
            
            gp << "set xrange [0: " << input3D.max_radius << "]\n";
            gp << "set yrange [0: " << 1 << "]\n";
            gp << "set xtics font ', 18'\n";
            gp << "set ytics font ', 18'\n";
            
            gp << "set key horizontal at graph 0.5, graph 1.04 center bottom font ', 16' spacing 1.5\n";
            
            gp << "set style line 1 lc rgb '#0d61ec' lw 3\n";
            gp << "set style line 2 lc rgb '#24ae1d' lw 3\n";
            gp << "set style line 3 lc rgb '#ffae00' lw 3\n";
            gp << "set style line 4 lc rgb '#e70000' lw 3\n";
            gp << "set style line 5 lc rgb '#db0dec' lw 3\n";
            gp << "set style line 6 lc rgb '#7B0985' lw 3\n";
            gp << "set style line 7 lc rgb '#87663E' lw 3\n";
            gp << "set style line 8 lc rgb '#000000' lw 3\n";
            gp << "set style line 9 lc rgb '#05FCF5' lw 3\n";
            gp << "set style line 10 lc rgb '#43FA96' lw 3\n";
            gp << "set style line 11 dt 2 lc rgb '#0d61ec' lw 3\n";
            gp << "set style line 12 dt 2 lc rgb '#24ae1d' lw 3\n";
            gp << "set style line 13 dt 2 lc rgb '#ffae00' lw 3\n";
            gp << "set style line 14 dt 2 lc rgb '#e70000' lw 3\n";
            gp << "set style line 15 dt 2 lc rgb '#db0dec' lw 3\n";
            gp << "set style line 16 dt 2 lc rgb '#7B0985' lw 3\n";
            gp << "set style line 17 dt 2 lc rgb '#87663E' lw 3\n";
            gp << "set style line 18 dt 2 lc rgb '#000000' lw 3\n";
            
            gp << "set output \"Graphs/Lattice Packing Functions/Square.pdf\"\n";
            
            gp << "set samples 1000\n";
            
            string plot = "plot 'Data/Lattice Packing Functions/Set1.txt' using 1:2 smooth csplines ls 1 title '{/Symbol y}@_1^A'";
            
            for (int counter = 1; counter < zone_limit - 1; ++counter)
            {
                plot += ", 'Data/Lattice Packing Functions/Set1.txt' using 1:" + to_string( counter + 2 ) + "smooth csplines ls " + to_string( (counter) % 12 + 1 ) + " title '  {/Symbol y}@_{" + to_string( counter + 1 ) + "}^A'";
            }
            
            for (int counter = 0; counter < zone_limit - 1; ++counter)
            {
                plot += ", 'Data/Lattice Packing Functions/Set2.txt' using 1:" + to_string( counter + 2 ) + "smooth csplines ls " + to_string( counter + 11 ) + " notitle";
            }
            
            plot += "\n";
            
            gp << plot;
        }
        
        if (threeD)
        {
            for (int file_index = 356; file_index < 357; ++file_index)
            {
                /*cout << "T2 crystal: " << file_index + 1 << "." << endl;
                
                vector<P3_E> centres_E;
                vector<P3> centres;
                vector<multimap<double, P3>> pts;
                vector<multimap<double, P3_E>> pts_E;
                
                if (T2)
                {
                    Preprocessing_T2_For_Brillouin( dataset_directory, file_index + 1, input3D, centres_E, centres, pts );
                }
                
                else
                {
                    multimap<double, P3> pts_copy;
                    
                    P3 p1 = input3D.parallelepiped_vectors[0], p2 = input3D.parallelepiped_vectors[1], p3 = input3D.parallelepiped_vectors[2];
                    
                    centres_E.push_back( P3_E( 0, 0, 0 ) );
                    centres.push_back( P3( 0, 0, 0 ) );
                    
                    V3 v1_E = V3( p1.x(), p1.y(), p1.z() );
                    V3 v2_E = V3( p2.x(), p2.y(), p2.z() );
                    V3 v3_E = V3( p3.x(), p3.y(), p3.z() );
                    
                    for (int counter_1 = -perim; counter_1 < perim + 1; ++counter_1)
                    {
                        for (int counter_2 = -perim; counter_2 < perim + 1; ++counter_2)
                        {
                            for (int counter_3 = -perim; counter_3 < perim + 1; ++counter_3)
                            {
                                if (counter_1 == 0 && counter_2 == 0 && counter_3 == 0) continue;
                                
                                V3 v = counter_1 * v1_E + counter_2 * v2_E + counter_3 * v3_E;
                                
                                P3 p = P3( v.x(), v.y(), v.z() );
                                
                                double dist = to_double( squared_distance( centres[0], p ) );
                                
                                pts_copy.insert( pair<double, P3>( dist, p ) );
                            }
                        }
                    }
                    
                    pts.push_back( pts_copy );
                }
                
                vector<vector<vector<Tetrahedron_I>>> zones_of_tetras( pts.size() );
                
                cout << "Computing Brillouin zones for " << pts.size() << " points." << endl;
                
                clock_t time_1 = clock();
                
                vector<vector<double>> max_radii( (int)centres.size() );
                
                bool use_threads = true;
                
                if (use_threads)
                {
                    vector<thread> thr;
                    
                    for (int counter = 0; counter < pts.size(); ++counter)
                    {
                        thr.push_back( thread( Compute_Brillouin_Zones_IT, pts[counter], zone_limit, centres[counter], ref( zones_of_tetras[counter] ), ref( max_radii[counter] ) ) );
                    }
                    
                    for (int counter = 0; counter < pts.size(); ++counter)
                    {
                        thr[counter].join();
                    }
                }
                
                else
                {
                    for (int counter = 0; counter < pts.size(); ++counter)
                    {
                        Compute_Brillouin_Zones_I( pts[counter], zone_limit, centres[counter], zones_of_tetras[counter], max_radii[counter] );
                    }
                }
                
                clock_t time_2 = clock();
                
                double time_taken = (time_2 - time_1) / (double)CLOCKS_PER_SEC;
                
                cout << "Time taken to compute Brillouin zones: " << time_taken << "." << endl;
                
                vector<vector<double>> cell_volume( pts.size() );
                vector<vector<vector<vector<Pl3>>>> tetra_cells( pts.size() );
                
                for (int counter = 0; counter < pts.size(); ++counter)
                {
                    Extract_Tetra_Cells_I( centres[counter], zones_of_tetras[counter], zone_limit, tetra_cells[counter], cell_volume[counter] );
                }
                
                cout << "Tetrahedrons extracted." << endl;
                
                Extract_Data_Pts_Brillouin( directory3D, input3D, file_index + 1, centres, tetra_cells, cell_volume, max_radii );
                
                cout << "Data extracted." << endl;*/
                
                if (input3D.experimental_T2) Plot_Graph_Brillouin_T2( directory3D, input3D, graph_params, file_index + 1 );
                
                else Plot_Graph_Brillouin( directory3D, input3D, graph_params, file_index + 1 );
                
                cout << "Graph plotted." << endl << endl;
            }
        }
    }
    
    Print_Info( start_time, start );
    
    return 0;
}
