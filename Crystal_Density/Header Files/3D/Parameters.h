#pragma once

#include "Input.h"
#include "Input3D.h"

const string directory = "/Users/philsmith/Documents/Xcode Projects/Crystal_Density/2D/"; // Root directory of 2D results.

const string directory3D = "/Users/philsmith/Documents/Xcode Projects/Crystal_Density/3D/"; // Root directory of 3D results.

bool twoD = false; // Run code for 2D.

bool threeD = true; // Run code for 3D.

const string function_type = "Exact"; // Exact, At_Least.

const string lattice_type = "Square"; // Square, Triangular, Custom.

vector<P2> pts = { P2( 0, 1 ), P2( 1, 0 ) }; // Input vectors for 2D case.

vector<P3> pts3D = { P3( 1, 0, 0 ), P3( 0, 1, 0 ), P3( 0.5, 0, 0.5 * sqrt( (double)3 ) ) }; // Input vectors for 3D case.

vector<double> scale = { 1, 1, 1 }; // Scale factors of input vectors.

bool interior_points = false; // Run code with interior points.

vector<P2> interior_pts = { /*P2( 0.5, 0.5 )*//*P2( 0.25, 0.25 ), P2( 0.75, 0.75 )*/ }; // 2D interior points.

vector<P3> interior_pts3D = { P3( 0.5, 0.5, 0.5 ) }; // 3D interior points.

int deformation_type = 2; // 0: No deformation; 1: Square to Triangular; 2: Interior point maps out semicircle; 3: Interior point maps out diagonal 1; 4: Interior point maps out diagonal 2.

int deformation_type3D = 0; // 0: No deformation; 1: Cube to slanted z-plane in the x-direction (upto angle 80 degrees).

int iterations = 101; // Number of iterations.

int sample_rate = 300; // Sample rate.

bool draw_cell = true; // True to draw cell.

Input3D input3D( function_type, lattice_type, pts3D, scale, interior_points, interior_pts3D, deformation_type3D, iterations, sample_rate );

Input input( function_type, lattice_type, pts, scale, interior_points, interior_pts, deformation_type, iterations, sample_rate );
