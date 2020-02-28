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
        
        /*GIF( directory + "Graphs/Deformation", "Deform", input.iterations );
        
        for (int counter = 0; counter < input.iterations; ++counter)
        {
            string str = "cd && cd '" + directory + "Graphs/' && /usr/local/Cellar/imagemagick/7.0.8-35/bin/convert Deformation/Deform" + to_string( counter ) + ".png Cells/Cell_" + to_string( counter ) + ".png +append Append/Append_" + to_string( counter ) + ".png";
            
            system( str.c_str() );
        }
        
        GIF( directory + "Graphs/Append", "Append_", input.iterations );*/
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
        for (int file_index = 0; file_index < 100; ++file_index)
        {
            cout << "T2 crystal: " << file_index + 1 << "." << endl;
            
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
            
            cout << "Data extracted." << endl;
            
            if (input3D.experimental_T2) Plot_Graph_Brillouin_T2( directory3D, input3D, graph_params, file_index + 1 );
            
            else Plot_Graph_Brillouin( directory3D, input3D, graph_params, file_index + 1 );
            
            cout << "Graph plotted." << endl << endl;
        }
    }
    
    Print_Info( start_time, start );
    
    return 0;
}
