#include "Read_Cell_Shape.h"
#include "Input3D.h"
#include "Assign_Experimental_Data.h"
#include "Transformation_Matrix.h"
#include "Read_Atom_Coords.h"
#include "Obtain_T2_Centres.h"
#include "Brillouin_Surrounding_Pts.h"
#include "Cell_Volume.h"

void Preprocessing_T2_For_Brillouin ( string const& dataset_directory, int index, Input3D const& input, double& cell_volume, vector<P3_E>& centres_E, vector<P3>& centres, vector<multimap<double, P3_E>>& pts )
{
    string filename = "T2_" + to_string( index ) + "_num_molGeom.cif";
    string file_path = dataset_directory + filename;
    
    cif::Document cif_file = cif::read_file( file_path ); // Accessing CIF file.
    
    cif::Block * block = &(*(++cif_file.blocks.begin())); // Pointer to relevant block.
    
    vector<pair<string, double>> cell_shape;
    
    Read_Cell_Shape( block, cell_shape ); // Reading cell shape.
    
    if (input.experimental_T2) Assign_Experimental_Cell_Shape( cell_shape, input.experimental_T2_label );
    
    double ** matrix;
    matrix = new double *[3];
    for (int counter_2 = 0; counter_2 < 3; ++counter_2)
    {
        matrix[counter_2] = new double [3];
    }
    
    Transformation_Matrix( cell_shape, matrix ); // Calculating the transformation matrix.
    
    vector<P3> atom_cloud;
    
    Read_Atom_Coords( block, matrix, atom_cloud );
    
    vector<P3> T2_centres;
    
    Obtain_T2_Centres( atom_cloud, input.type_of_experiment, T2_centres );
    
    if (input.experimental_T2) Assign_Experimental_Centres( T2_centres, matrix, input.experimental_T2_label, input.type_of_experiment );
    
    pts.resize( T2_centres.size() );
    
    for (int counter = 0; counter < T2_centres.size(); ++counter)
    {
        Brillouin_Surrounding_Pts( input.perim, matrix, counter, T2_centres, pts[counter] );
    }
    
    cell_volume = Cell_Volume( cell_shape );
    
    for (int counter = 0; counter < T2_centres.size(); ++counter)
    {
        centres_E.push_back( P3_E( T2_centres[counter].x(), T2_centres[counter].y(), T2_centres[counter].z() ) );
        centres.push_back( T2_centres[counter] );
    }
}
