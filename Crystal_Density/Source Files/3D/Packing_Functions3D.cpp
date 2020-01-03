#include "Extract_Data_Pts3D.h"
#include "Derivatives3D.h"
#include "Plot_Graph3D.h"

void Packing_Functions3D ( string const& directory, Input3D& input, Graph_Parameters const& graph_params, Cell3D const& cell, int iter )
{
    Extract_Data_Pts3D ( directory, input, cell, iter );
    
    //Derivatives3D( directory, "Data/Results.txt" );
    
    Plot_Graph3D( directory, input, graph_params, iter );
}
