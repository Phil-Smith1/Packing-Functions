#include "Extract_Data_Pts.h"
#include "Derivatives.h"
#include "Plot_Graph.h"

void Packing_Functions ( string const& directory, Input const& input, Cell& cell, int iter )
{
    Extract_Data_Pts( directory, cell, input.sample_rate, input.max_radius );
    
    //Derivatives( directory, "Data/Results_" + input.function_type + ".txt" );
    
    Plot_Graph( directory, input, iter );
}
