#pragma once

#include <string>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;
typedef K::Point_3 P3;

const string function_type = "Exact"; // Exact, At_Least.

const string lattice_type = "Square"; // Square, Triangular, Custom.

vector<P2> pts = { P2( 0, 1 ), P2( 1, 0 ) }; // Input vectors for 2D case.

vector<P3> Cube = { P3( 1, 0, 0 ), P3( 0, 1, 0 ), P3( 0, 0, 1 ) }; // r = sqrt( (double)2 ) / (double)2.

vector<P3> BCC = { P3( 5 / (double)6, -1 / (double)6, -1 / (double)6 ), P3( -1 / (double)6, 5 / (double)6, -1 / (double)6 ), P3( -1 / (double)6, -1 / (double)6, 5 / (double)6 ) }; // r = 0.56

vector<P3> FCC = { P3( 4 / (double)3, 1 / (double)3, 1 / (double)3 ), P3( 1 / (double)3, 4 / (double)3, 1 / (double)3 ), P3( 1 / (double)3, 1 / (double)3, 4 / (double)3 ) }; // r = 0.816.

vector<double> scale = { 1, 1, 1 }; // Scale factors of input vectors.

vector<P2> square_additional_pts = { P2( -1, 0 ), P2( -1, 1 ), P2( 0, 2 ), P2( 1, 2 ), P2( 2, 1 ), P2( 2, 0 ), P2( 1, -1 ), P2( 0, -1 )};

vector<P2> interior_pts = { P2( 0.25, 0 ), P2( 0.25, 1 ), P2( 1.25, 1 ), P2( 1.25, 0 ) };//P2( 0.25, 0.25 ), P2( 0.75, 0.75 ) }; // 2D interior points.

int deformation_type = 0; // 0: No deformation; 1: Square to Triangular; 2: Interior point maps out semicircle; 3: Interior point maps out diagonal 1; 4: Interior point maps out diagonal 2.

bool draw_cell = false; // True to draw cell.

double max_radius = 20;

bool parallelepiped = false;

double yrange = 1.01; // yrange of output graph.
