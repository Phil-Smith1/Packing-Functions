#include "Read_Cell_Shape.h"
#include "Transformation_Matrix.h"
#include "Make_T2_Cell.h"
#include "Assign_Experimental_data.h"
#include "Read_Atom_Coords.h"
#include "Obtain_T2_Centres.h"
#include "Translate_Centres.h"
#include "Add_Surrounding_Pts.h"

void Make_T2_Cells ( string const& dataset_directory, Input3D& input3D, vector<Cell3D>& cells, int index )
{
    string filename = "T2_" + to_string( index ) + "_num_molGeom.cif";
    
    string file_path = dataset_directory + filename;
    
    cif::Document cif_file = cif::read_file( file_path ); // Accessing CIF file.
    
    cif::Block * block = &(*(++cif_file.blocks.begin())); // Pointer to relevant block.
    
    vector<pair<string, double>> cell_shape;
    
    Read_Cell_Shape( block, cell_shape ); // Reading cell shape.
    
    bool experimental = false;
    string label = "d";
    
    if (experimental) Assign_Experimental_Cell_Shape( cell_shape, label );
    
    double ** matrix;
    matrix = new double *[3];
    for (int counter_2 = 0; counter_2 < 3; ++counter_2)
    {
        matrix[counter_2] = new double [3];
    }
    
    Transformation_Matrix( cell_shape, matrix ); // Calculating the transformation matrix.
    
    Cell3D cell;
    
    Make_T2_Cell( cell_shape, matrix, cell );
    
    vector<P3> atom_cloud;
    
    Read_Atom_Coords( block, matrix, atom_cloud );
    
    vector<P3> T2_centres;
    
    Obtain_T2_Centres( atom_cloud, T2_centres );
    
    if (experimental) Assign_Experimental_Centres( T2_centres, matrix, label );
    
    cell.pts = T2_centres;
    
    if (!Centres_In_Cell( cell )) Translate_Centres( cell );
    
    Add_Surrounding_Pts( input3D, cell );
    
    cells.push_back( cell );
}
