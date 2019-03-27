#include "Extract_Data_Pts.h"
#include "Derivatives.h"
#include "Plot_Graph.h"

void Packing_Functions ( string const& directory, string const& function_type, Cell& cell, string const& lattice_type, int sample_rate, double max_radius, int iter )
{
    Extract_Data_Pts( directory, cell, sample_rate, max_radius );
    
    Derivatives( directory, "Data/Results_" + function_type + ".txt" );
    
    Plot_Graph( directory, function_type, lattice_type, max_radius, iter );
}
