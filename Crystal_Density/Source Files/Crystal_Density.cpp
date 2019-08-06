#include "Packing_Functions3D.h"
#include "Make_Cell3D.h"
#include "Deformation.h"
#include "Cell_Data.h"
#include "Draw_Cells.h"
#include "Packing_Functions.h"
#include "GIF.h"
#include "Print_Info.h"

const string directory = "/Users/philsmith/Documents/Xcode Projects/Crystal_Density/2D/";

const string directory3D = "/Users/philsmith/Documents/Xcode Projects/Crystal_Density/3D/";

bool twoD = false;

bool threeD = true;

const string function_type = "Exact"; // Exact, At_Least.

const string lattice_type = "Square"; // Square, Triangular, Custom.

vector<P2> pts = { P2( 0, 1 ), P2( 1, 0 ) };

vector<P3> pts3D = { P3( 1, 0, 0 ), P3( 0, 1, 0 ), P3( 0.5, 0, 0.5 * sqrt( (double)3 ) ) };

vector<double> scale = { 1, 1, 1 };

bool interior_points = true;

vector<P2> interior_pts = { /*P2( 0.5, 0.5 )*//*P2( 0.25, 0.25 ), P2( 0.75, 0.75 )*/ };

vector<P3> interior_pts3D;

int deformation_type = 2; // 0: No deformation; 1: Square to Triangular; 2: Interior point maps out semicircle; 3: Interior point maps out diagonal 1; 4: Interior point maps out diagonal 2.

int iterations = 101;

int sample_rate = 300;

bool draw_cell = true;

Input3D input3D( function_type, lattice_type, pts3D, scale, interior_points, interior_pts3D, deformation_type, iterations, sample_rate );

Input input( function_type, lattice_type, pts, scale, interior_points, interior_pts, deformation_type, iterations, sample_rate );

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
        Cell3D cell;
        
        Make_Cell3D( input3D, cell );
        
        Packing_Functions3D( directory3D, input3D, cell );
    }
    
    Print_Info( start_time, start );
    
    return 0;
}
