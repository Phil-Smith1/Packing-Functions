//#include "Three_Sphere_Intersection_Volume_Within_Cell.h"
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
            
            Packing_Functions3D( directory3D, input3D, cells[counter], counter );
        }
        
        if (input3D.deformation_type != 0) GIF( directory3D + "Graphs/Deformation", "Deform", input3D.iterations );
        
        //double r = 0.708;
        
        //Pl3 p1( P3( 0.5, 0.5, 0 ), V3( -0.5 * sqrt( (double)2 ), -0.5 * sqrt( (double)2 ), 0 ) );
        //Pl3 p2( P3( 0.5, 0.5, 0.5 ), V3( -0.5 * sqrt( (double)3 ), -0.5 * sqrt( (double)3 ), 0.5 * sqrt( (double)3 ) ) );
        
        //cout << Third_Order_Total_Volume( cells[0], r ) << endl;
        
        //cout << Three_Sphere_Intersection_Volume_Within_Cell( cells[0], Sphere( cells[0].vertices[0], r ), Sphere( cells[0].vertices[2], r ), Sphere( cells[0].vertices[5], r ) ) << endl;
        
        //cout << General_Spherical_Cone( Sphere( cells[0].vertices[2], r ), p1.opposite(), p2.opposite(), cells[0].planes[2].opposite() ) << endl;
        
        double a;
        
    }
    
    Print_Info( start_time, start );
    
    return 0;
}
