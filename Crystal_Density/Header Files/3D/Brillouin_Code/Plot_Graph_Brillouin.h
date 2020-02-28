#pragma once

#include "gnuplot-iostream.h"

#include "Input3D.h"
#include "Graph_Parameters.h"

void Plot_Graph_Brillouin ( string const& directory3D, Input3D const& input, Graph_Parameters const& graph_params, int index );

void Plot_Graph_Brillouin_T2 ( string const& directory3D, Input3D const& input, Graph_Parameters const& graph_params, int index );
