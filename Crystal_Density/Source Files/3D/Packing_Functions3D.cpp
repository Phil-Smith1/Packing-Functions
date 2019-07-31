#include "Input3D.h"
#include "Extract_Data_Pts3D.h"
#include "Derivatives3D.h"
#include "Plot_Graph3D.h"

void Packing_Functions3D ( string const& directory, Input3D const& input, Cell3D const& cell )
{
    Extract_Data_Pts3D ( directory, cell, input.sample_rate, input.max_radius );
    
    Derivatives3D( directory, "Data/Results.txt" );
    
    Plot_Graph3D( directory, input );
}
