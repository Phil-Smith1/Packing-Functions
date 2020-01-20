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
    
    Print_Info( start_time, start );
    
    return 0;
}
