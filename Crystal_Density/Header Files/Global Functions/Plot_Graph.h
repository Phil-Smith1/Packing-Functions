#pragma once

#include "gnuplot-iostream.h"

#include <string>

using namespace std;

void Plot_Graph ( string const& directory, string const& function_type, string const& lattice_type, double max_radius, int iter );
