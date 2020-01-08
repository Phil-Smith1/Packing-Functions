#pragma once

#include "Input.h"
#include "Input3D.h"
#include "Graph_Parameters.h"

const string directory = "/Users/philsmith/Documents/Work/Xcode Projects/Crystal_Density/2D/"; // Root directory of 2D results.

const string directory3D = "/Users/philsmith/Documents/Work/Xcode Projects/Crystal_Density/3D/"; // Root directory of 3D results.

const string dataset_directory = "/Users/philsmith/Documents/Work/Xcode Projects/T2_Dataset/";

bool twoD = false; // Run code for 2D.

bool threeD = false; // Run code for 3D.

bool T2 = true;

bool comparing = true;

const string function_type = "Exact"; // Exact, At_Least.

const string lattice_type = "Square"; // Square, Triangular, Custom.

vector<P2> pts = { P2( 0, 1 ), P2( 1, 0 ) }; // Input vectors for 2D case.

vector<P3> Cube = { P3( 1, 0, 0 ), P3( 0, 1, 0 ), P3( 0, 0, 1 ) }; // r = sqrt( (double)2 ) / (double)2.

vector<P3> BCC = { P3( 5 / (double)6, -1 / (double)6, -1 / (double)6 ), P3( -1 / (double)6, 5 / (double)6, -1 / (double)6 ), P3( -1 / (double)6, -1 / (double)6, 5 / (double)6 ) }; // r = 0.56

vector<P3> FCC = { P3( 4 / (double)3, 1 / (double)3, 1 / (double)3 ), P3( 1 / (double)3, 4 / (double)3, 1 / (double)3 ), P3( 1 / (double)3, 1 / (double)3, 4 / (double)3 ) }; // r = 0.816.

vector<P3> parallelepiped_vectors = BCC;//{ P3( 1, 0, 0 ), P3( 0, 1, 0 ), P3( 0.5, 0, 0.5 * sqrt( (double)3 ) ) }; // Input vectors for 3D case.

bool pts_at_vertices = true;

bool interior_points = false; // Run code with interior points.

vector<double> scale = { 1, 1, 1 }; // Scale factors of input vectors.

vector<P2> square_additional_pts = { P2( -1, 0 ), P2( -1, 1 ), P2( 0, 2 ), P2( 1, 2 ), P2( 2, 1 ), P2( 2, 0 ), P2( 1, -1 ), P2( 0, -1 )};

vector<P2> interior_pts = { P2( 0.25, 0 ), P2( 0.25, 1 ), P2( 1.25, 1 ), P2( 1.25, 0 ) };//P2( 0.25, 0.25 ), P2( 0.75, 0.75 ) }; // 2D interior points.

vector<P3> interior_pts3D = { P3( 1, 1, -1 ) }; // 3D interior points.

int deformation_type = 0; // 0: No deformation; 1: Square to Triangular; 2: Interior point maps out semicircle; 3: Interior point maps out diagonal 1; 4: Interior point maps out diagonal 2.

int deformation_type3D = 0; // 0: No deformation; 1: Cube to slanted z-plane in the x-direction (upto angle 80 degrees).

int iterations = 1; // Number of iterations.

int sample_rate = 10; // Sample rate.

bool draw_cell = false; // True to draw cell.

bool auto_max_radius = true;

double max_radius = 6;

bool parallelepiped = false;

bool title = false;

string title_str = "Packing Functions for T2-{/Symbol a}";

double yrange = 1.01;

Graph_Parameters graph_params( title, yrange, title_str );

Input3D input3D( T2, function_type, lattice_type, parallelepiped_vectors, pts_at_vertices, scale, interior_points, interior_pts3D, deformation_type3D, iterations, sample_rate, auto_max_radius, max_radius, parallelepiped );

Input input( function_type, lattice_type, pts, scale, interior_points, interior_pts, deformation_type, iterations, sample_rate );
