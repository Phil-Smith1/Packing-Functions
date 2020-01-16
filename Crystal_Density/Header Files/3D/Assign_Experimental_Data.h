#pragma once

#include "Frac_To_Cart_Coords.h"

#include <string>
#include <vector>

using namespace std;

void Assign_Experimental_Cell_Shape ( vector<pair<string, double>>& cell_shape, string const& label );

void Assign_Experimental_Centres ( vector<P3>& T2_centres, double ** matrix, string const& label, string const& type_of_experiment );
