#include "Parameters.h"
#include "Volume_Of_Intersection_Of_Two_Spheres.h"
#include "Packing_Functions3D.h"
#include "Make_Cells3D.h"
#include "Deformation.h"
#include "Cell_Data.h"
#include "Draw_Cells.h"
#include "Packing_Functions.h"
#include "GIF.h"
#include "Print_Info.h"

int main ( int, char*[] )
{
    clock_t start_time = clock();
    chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
    
    if (twoD)
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
    
    if (threeD)
    {
        vector<Cell3D> cells;
        
        Make_Cells3D( input3D, cells );
        
        for (int counter = 0; counter < cells.size(); ++counter)
        {
            cout << "Iteration: " << counter << "." << endl;
            
            //Packing_Functions3D( directory3D, input3D, cells[counter], counter );
        }
        
        if (input3D.deformation_type != 0) GIF( directory3D + "Graphs/Deformation", "Deform", input3D.iterations );
    }
    
    Print_Info( start_time, start );
    
    return 0;
}
