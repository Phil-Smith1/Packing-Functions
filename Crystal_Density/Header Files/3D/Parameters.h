#pragma once

#include "Further_Parameters.h"
#include "Input.h"
#include "Input3D.h"
#include "Graph_Parameters.h"

const string directory = "/Users/philsmith/Documents/Work/Xcode Projects/Crystal_Density/2D/"; // Root directory of 2D results.

const string directory3D = "/Users/philsmith/Documents/Work/Xcode Projects/Crystal_Density/3D/"; // Root directory of 3D results.

const string dataset_directory = "/Users/philsmith/Documents/Work/Xcode Projects/T2_Dataset/"; // Root directory for the T2 dataset.

bool twoD = false; // Run code for 2D.

bool threeD = false; // Run code for 3D.

bool T2 = true; // Run code for T2 crystals.

string type_of_experiment = "Molecule_Centres"; // Molecule_Centres, Molecule_Centres_with_Oxygens, Oxygens

bool experimental_T2 = false;

string experimental_T2_label = "c";

bool analysis = false; // Perform analysis.

bool brillouin = true;

vector<P3> parallelepiped_vectors = Cube; //{ P3( 1, 0, 0 ), P3( 0, 1, 0 ), P3( 0.5, 0, 0.5 * sqrt( (double)3 ) ) }; // Input vectors for 3D case.

bool pts_at_vertices = true; // Add points at vertices of the parallelepiped.

bool interior_points = false; // Run code with interior points.

vector<P3> interior_pts3D = { P3( 1, 1, -1 ) }; // 3D interior points.

int deformation_type3D = 0; // 0: No deformation; 1: Cube to slanted z-plane in the x-direction (upto angle 80 degrees).

int iterations = 5688; // Number of iterations.

int sample_rate = 10; // Sample rate.

bool auto_max_radius = true; // The code automatically produces the maximum radius.

bool title = false; // Adds title to output graph.

string title_str = "Packing Functions for T2 Entry 1"; // Title of output graph.

Graph_Parameters graph_params( title, yrange, title_str );

Input3D input3D( T2, type_of_experiment, experimental_T2, experimental_T2_label, function_type, lattice_type, parallelepiped_vectors, pts_at_vertices, scale, interior_points, interior_pts3D, deformation_type3D, iterations, sample_rate, auto_max_radius, max_radius, parallelepiped );

Input input( function_type, lattice_type, pts, scale, interior_points, interior_pts, deformation_type, iterations, sample_rate );
