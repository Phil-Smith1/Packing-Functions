#pragma once

#include "Read_Cell_Shape.h"
#include "Input3D.h"
#include "Assign_Experimental_Data.h"
#include "Transformation_Matrix.h"
#include "Read_Atom_Coords.h"
#include "Obtain_T2_Centres.h"
#include "Brillouin_Surrounding_Pts.h"
#include "Cell_Volume.h"

void Preprocessing_T2_For_Brillouin ( string const& dataset_directory, int index, Input3D const& input, vector<P3_E>& centres_E, vector<P3>& centres, vector<multimap<double, P3>>& pts );
