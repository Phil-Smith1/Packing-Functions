#pragma once

#include "Generate_Cube.h"

void Initialise_Cubes ( double cube_size, int num_cubes, P3_E const& centre, vector<Polyhedron>& cubes );

void Initialise_Cubes_I ( double cube_size, int num_cubes, P3 const& centre, vector<Polyhedron_I>& cubes );
