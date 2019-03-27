#include "Deformation.h"
#include "Cell_Data.h"
#include "Packing_Functions.h"
#include "Print_Info.h"

const string directory = "/Users/philsmith/Documents/Xcode Projects/Crystal_Density/";

const string function_type = "Exact"; // Exact, At_Least.
const string lattice_type = "Square"; // Square, Triangular, Custom.

int sample_rate = 300;
double max_radius = 1.5; // If Square: 1.5; Triangular: 1.8.

int deformation_type = 0; // 0: No deformation; 1: Square to Triangular; 2: Interior point maps out semicircle; 3: Interior point maps out diagonal 1; 4: Interior point maps out diagonal 2.

int iterations = 1;

P2 p1 = P2( 0, 0 );
P2 p2 = P2( 0, 1 );
P2 p4 = P2( 1, 0 );
P2 p3 = P2( p2.x() + p4.x(), p2.y() + p4.y() );

bool interior_points = true;

vector<P2> interior_pts = { P2( 0.25, 0.25 ), P2( 0.75, 0.75 ) };

int main ( int, char*[] )
{
    clock_t start_time = clock();
    chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
    
    for (int counter = 0; counter < iterations; ++counter)
    {
        Deformation( deformation_type, iterations, counter, p2, p3, p4, interior_pts );
        
        Cell cell;
        
        Cell_Data( lattice_type, p1, p2, p3, p4, interior_points, interior_pts, cell );
        
        Packing_Functions( directory, function_type, cell, lattice_type, sample_rate, max_radius, counter );
    }
    
    Print_Info( start_time, start );
    
    return 0;
}
