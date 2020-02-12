#pragma once

#include "Input3D.h"
#include "Sphere_Tetrahedron_Intersection.h"

#include <fstream>

void Extract_Data_Pts_Brillouin ( string const& directory3D, Input3D& input, int index, vector<P3> const& centres, vector<vector<vector<vector<Pl3>>>>const& tetra_cells, double cell_volume );
