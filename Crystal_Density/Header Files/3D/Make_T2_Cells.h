#pragma once

#include "Read_Cell_Shape.h"
#include "Transformation_Matrix.h"
#include "Make_T2_Cell.h"
#include "Assign_Experimental_data.h"
#include "Read_Atom_Coords.h"
#include "Obtain_T2_Centres.h"
#include "Translate_Centres.h"
#include "Add_Surrounding_Pts.h"

void Make_T2_Cells ( string const& dataset_directory, Input3D& input3D, vector<Cell3D>& cells, int index );
