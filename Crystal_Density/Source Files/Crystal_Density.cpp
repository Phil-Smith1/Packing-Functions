#include "Make_Cell3D.h"
#include "Input3D.h"
#include "Sphere.h"
#include "Deformation.h"
#include "Cell_Data.h"
#include "Packing_Functions.h"
#include "Print_Info.h"

const string directory = "/Users/philsmith/Documents/Xcode Projects/Crystal_Density/";

bool twoD = true;

bool threeD = false;

const string function_type = "Exact"; // Exact, At_Least.

const string lattice_type = "Custom"; // Square, Triangular, Custom.

vector<P2> pts = { P2( 0, 1 ), P2( 1, 0 ) };

vector<P3> pts3D = { P3( 1, 0, 0 ), P3( 0, 1, 0 ), P3( 0, 0, 1 ) };

vector<double> scale = { 1, 1, 1 };

bool interior_points = false;

vector<P2> interior_pts = { P2( 0.25, 0.25 ), P2( 0.75, 0.75 ) };

vector<P3> interior_pts3D;

int deformation_type = 1; // 0: No deformation; 1: Square to Triangular; 2: Interior point maps out semicircle; 3: Interior point maps out diagonal 1; 4: Interior point maps out diagonal 2.

int iterations = 101;

int sample_rate = 300;

double max_radius = 1.5; // If Square: 1.5; Triangular: 1.8.

Input3D input3D( function_type, lattice_type, pts3D, scale, interior_points, interior_pts3D, deformation_type, iterations, sample_rate );

Input input( function_type, lattice_type, pts, scale, interior_points, interior_pts, deformation_type, iterations, sample_rate );

int main ( int, char*[] )
{
    clock_t start_time = clock();
    chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
    
    if (twoD)
    {
        for (int counter = 0; counter < iterations; ++counter)
        {
            Deformation( input, counter );
            
            Cell cell;
            
            Cell_Data( input, cell );
            
            Packing_Functions( directory, function_type, cell, lattice_type, sample_rate, max_radius, counter );
        }
    }
    
    if (threeD)
    {
        Cell3D cell;
        
        Make_Cell3D( input3D, cell );
    }
    
    Print_Info( start_time, start );
    
    return 0;
}
