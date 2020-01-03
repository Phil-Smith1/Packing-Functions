#include <gemmi/cif.hpp>

#include "Parameters.h"
#include "Packing_Functions3D.h"
#include "Make_Cells3D.h"
#include "Make_T2_Cells.h"
#include "Deformation.h"
#include "Cell_Data.h"
#include "Draw_Cells.h"
#include "Packing_Functions.h"
#include "GIF.h"
#include "Print_Info.h"

#include "Obtain_T2_Centres.h"

int main ( int, char*[] )
{
    clock_t start_time = clock(); // Starts the clock measuring the runtime of the code.
    chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now(); // Starts the clock measuring the absolute time elapsed to complete the code.
    
    if (twoD) // Runs for 2D packing functions.
    {
        vector<Cell> cells;
        cells.reserve( input.iterations );
        
        for (int counter = 0; counter < input.iterations; ++counter)
        {
            Deformation( input, counter );
            
            Cell cell;
            
            Cell_Data( input, cell );
            
            cells.push_back( cell );
        }
        
        if (draw_cell)
        {
            Draw_Cells( cells );
            
            GIF( directory + "Graphs/Cells", "Cell_", input.iterations );
        }
        
        for (int counter = 0; counter < cells.size(); ++counter)
        {
            cout << "Iteration: " << counter << "." << endl;
            
            Packing_Functions( directory, input, cells[counter], counter );
        }
        
        GIF( directory + "Graphs/Deformation", "Deform", input.iterations );
        
        for (int counter = 0; counter < input.iterations; ++counter)
        {
            string str = "cd && cd '" + directory + "Graphs/' && /usr/local/Cellar/imagemagick/7.0.8-35/bin/convert Deformation/Deform" + to_string( counter ) + ".png Cells/Cell_" + to_string( counter ) + ".png +append Append/Append_" + to_string( counter ) + ".png";
            
            system( str.c_str() );
        }
        
        GIF( directory + "Graphs/Append", "Append_", input.iterations );
    }
    
    if (threeD) // Runs for 3D packing functions.
    {
        vector<Cell3D> cells; // Vector of cells.
        
        if (T2)
        {
            for (int counter = 0; counter < input3D.iterations; ++counter)
            {
                cout << "Iteration: " << counter << "." << endl;
                
                Make_T2_Cells( dataset_directory, input3D, cells, counter + 1 );
                
                Packing_Functions3D( directory3D, input3D, graph_params, cells[counter], counter + 1 );
            }
            
            double r = 7.346;
            int c = 0;
            
            //cout << Second_Order_Total_Volume( cells[c], r - 0.001, false ) / (double)cells[c].vol << endl;
            //cout << Second_Order_Total_Volume( cells[c], r, false ) / (double)cells[c].vol << endl;
            //cout << Second_Order_Total_Volume( cells[c], r + 0.001, false ) / (double)cells[c].vol << endl;
            //cout << Second_Order_Total_Volume( cells[c], r + 0.002, false ) / (double)cells[c].vol << endl;
            
            //cout << Third_Order_Total_Volume( cells[c], r - 0.001 ) / (double)cells[c].vol << endl;
            //cout << Third_Order_Total_Volume( cells[c], r ) / (double)cells[c].vol << endl;
            //cout << Third_Order_Total_Volume( cells[c], r + 0.001 ) / (double)cells[c].vol << endl;
            //cout << Third_Order_Total_Volume( cells[c], r + 0.002 ) / (double)cells[c].vol << endl;
             
            vector<Sphere> spheres;
            spheres.push_back( Sphere( cells[c].pts[30], r ) ); // 15 35
            spheres.push_back( Sphere( cells[c].pts[34], r ) );
            spheres.push_back( Sphere( cells[c].pts[39], r ) );
            spheres.push_back( Sphere( cells[c].pts[30], r + 0.001 ) );
            spheres.push_back( Sphere( cells[c].pts[34], r + 0.001 ) );
            spheres.push_back( Sphere( cells[c].pts[39], r + 0.001 ) );
            
            //cout << Two_Sphere_Intersection_Volume_Within_Cell( cells[c], spheres[0], spheres[1] ) << endl;
            //cout << Two_Sphere_Intersection_Volume_Within_Cell( cells[c], spheres[3], spheres[4] ) << endl;
            
            //cout << Three_Sphere_Intersection_Volume_Within_Cell( cells[c], spheres[3], spheres[4], spheres[5] ) / (double)cells[c].vol << endl;
            //cout << Three_Sphere_Intersection_Volume_Within_Cell( cells[c], spheres[0], spheres[1], spheres[2] ) / (double)cells[c].vol << endl;
             
            double d1 = Norm( spheres[1].c, spheres[2].c ), d2 = Norm( spheres[0].c, spheres[2].c ), d3 = Norm( spheres[0].c, spheres[1].c );
             
            V3 v = spheres[0].c - spheres[1].c;
            v = v / (double)Norm( v );
             
            double k = (spheres[1].r * spheres[1].r + d3 * d3 - spheres[0].r * spheres[0].r) / (double)(2 * d3);
             
            P3 pt = spheres[1].c + k * v;
             
            Pl3 p3( pt, v );
             
            v = spheres[0].c - spheres[2].c;
            v = v / (double)Norm( v );
             
            k = (spheres[2].r * spheres[2].r + d2 * d2 - spheres[0].r * spheres[0].r) / (double)(2 * d2);
             
            pt = spheres[2].c + k * v;
             
            Pl3 p2( pt, v );
             
            v = spheres[1].c - spheres[2].c;
            v = v / (double)Norm( v );
             
            k = (spheres[2].r * spheres[2].r + d1 * d1 - spheres[1].r * spheres[1].r) / (double)(2 * d1);
             
            pt = spheres[2].c + k * v;
             
            Pl3 p1( pt, v );
            
            //cout << Spherical_Cap_Volume_Within_Cell( cells[c], spheres[0], p3.opposite() ) << endl;
            
            //cout << Spherical_Wedge_Volume_Within_Cell( cells[c], spheres[2], p3.opposite(), p2 ) << endl;
            
            //cout << Sphere_Five_Plane_Intersection_Volume( spheres[2], p3.opposite(), p2, cells[c].planes[0].opposite(), cells[c].planes[1].opposite(), cells[c].planes[5].opposite(), 0 ) << endl;
            
            //cout << Sphere_Five_Plane_Intersection_Volume( spheres[2], cells[c].planes[1].opposite(), p2, p3.opposite(), cells[c].planes[2].opposite(), cells[c].planes[4].opposite(), 11 ) << endl;
            
            //cout << Non_Parallel_Lines_Case5B( spheres[2], cells[c].planes[4].opposite(), p3.opposite(), p2, cells[c].planes[2].opposite(), cells[c].planes[3].opposite(), 15 ) << endl;
            
            //cout << Non_Parallel_Lines_Case5B( spheres[2], cells[c].planes[0].opposite(), p3.opposite(), cells[c].planes[1].opposite(), p2, cells[c].planes[5].opposite(), 15 ) << endl;
            
            //cout << Sphere_Four_Plane_Intersection_Volume( spheres[2], cells[c].planes[5], p3, cells[c].planes[0], cells[c].planes[1] ) << endl;
            
            //cout << General_Spherical_Cone( spheres[0], p3, cells[c].planes[2], cells[c].planes[4] ) << endl;
            
            //cout << Parallel_Planes_Case5( spheres[1], p3, cells[c].planes[1].opposite(), p1.opposite(), cells[c].planes[0].opposite(), cells[c].planes[5].opposite() ) << endl;
            //cout << Parallel_Planes_Case5( spheres[3], p3, cells[c].planes[1].opposite(), p1.opposite(), cells[c].planes[0].opposite(), cells[c].planes[5].opposite() ) << endl;
            
            //cout << General_Spherical_Cone( spheres[0], p3.opposite(), cells[c].planes[0].opposite(), cells[c].planes[4].opposite() ) << endl;
            //cout << Circumradius( spheres[0].c, spheres[1].c, spheres[2].c ) << endl;
            //cout << General_Spherical_Wedge( spheres[2], p3.opposite(), p2 ) << endl;
            //cout << General_Spherical_Wedge( spheres[2], p3, p1 ) << endl;
        }
        
        else
        {
            Make_Cells3D( input3D, cells ); // Initialised the vector of cells.
            
            for (int counter = 0; counter < cells.size(); ++counter) // Looping over the vector of cells.
            {
                cout << "Iteration: " << counter << "." << endl;
                
                Packing_Functions3D( directory3D, input3D, graph_params, cells[counter], counter );
            }
            
            if (input3D.deformation_type != 0) GIF( directory3D + "Graphs/Deformation", "Deform", input3D.iterations );
        }
    }
    
    if (false)
    {
        for (int counter_1 = 99; counter_1 < 100; ++counter_1)
        {
            /*cell_shape.push_back( pair<string, double>( "_cell_length_a", 7.2523 ) );
            cell_shape.push_back( pair<string, double>( "_cell_length_b", 13.033 ) );
            cell_shape.push_back( pair<string, double>( "_cell_length_c", 20.693 ) );
            cell_shape.push_back( pair<string, double>( "_cell_angle_alpha", 72.701 ) );
            cell_shape.push_back( pair<string, double>( "_cell_angle_beta", 86.552 ) );
            cell_shape.push_back( pair<string, double>( "_cell_angle_gamma", 73.915 ) );
            
            P3 p = P3( 0.7707, 0.33245, 0.34045 );
            Frac_To_Cart_Coords( matrix, p );
            T2_centres.push_back( p );
            
            p = P3( 0.2293, 0.66755, 0.65955 );
            Frac_To_Cart_Coords( matrix, p );
            T2_centres.push_back( p );
            
            p = P3( 0.81344, 0.76646, 0.5 );
            Frac_To_Cart_Coords( matrix, p );
            T2_centres.push_back( p );
            
            p = P3( 0.23354, 0.81344, 0 );
            Frac_To_Cart_Coords( matrix, p );
            T2_centres.push_back( p );*/
        }
    }
    
    ifstream ifs_1( directory3D + "Data/T2 Packing Functions/delta.txt" );
    ifstream ifs_2( directory3D + "Data/T2 Packing Functions/deltaex.txt" );
    ifstream ifs_3( directory3D + "Data/T2 Packing Functions/gamma.txt" );
    ifstream ifs_4( directory3D + "Data/T2 Packing Functions/delta.txt" );
    ifstream ifs_5( directory3D + "Data/T2 Packing Functions/epsilon.txt" );
    
    string line_data;
    stringstream stream;
    vector<vector<double>> af, bf, cf, df, ef;
    
    vector<double> f1, f2, f3;
    
    while (getline( ifs_1, line_data ))
    {
        double rad, fn1, fn2, fn3;
        stringstream stream;
        
        stream << line_data;
        stream >> rad >> fn1 >> fn2 >> fn3;
        
        f1.push_back( fn1 );
        f2.push_back( fn2 );
        f3.push_back( fn3 );
    }
    
    af.push_back( f1 );
    f1.clear();
    af.push_back( f2 );
    f2.clear();
    af.push_back( f3 );
    f3.clear();
    
    ifs_1.close();
    
    while (getline( ifs_2, line_data ))
    {
        double rad, fn1, fn2, fn3;
        stringstream stream;
        
        stream << line_data;
        stream >> rad >> fn1 >> fn2 >> fn3;
        
        f1.push_back( fn1 );
        f2.push_back( fn2 );
        f3.push_back( fn3 );
    }
    
    bf.push_back( f1 );
    f1.clear();
    bf.push_back( f2 );
    f2.clear();
    bf.push_back( f3 );
    f3.clear();
    
    ifs_2.close();
    
    while (getline( ifs_3, line_data ))
    {
        double rad, fn1, fn2, fn3;
        stringstream stream;
        
        stream << line_data;
        stream >> rad >> fn1 >> fn2 >> fn3;
        
        f1.push_back( fn1 );
        f2.push_back( fn2 );
        f3.push_back( fn3 );
    }
    
    cf.push_back( f1 );
    f1.clear();
    cf.push_back( f2 );
    f2.clear();
    cf.push_back( f3 );
    f3.clear();
    
    ifs_3.close();
    
    while (getline( ifs_4, line_data ))
    {
        double rad, fn1, fn2, fn3;
        stringstream stream;
        
        stream << line_data;
        stream >> rad >> fn1 >> fn2 >> fn3;
        
        f1.push_back( fn1 );
        f2.push_back( fn2 );
        f3.push_back( fn3 );
    }
    
    df.push_back( f1 );
    f1.clear();
    df.push_back( f2 );
    f2.clear();
    df.push_back( f3 );
    f3.clear();
    
    ifs_4.close();
    
    while (getline( ifs_5, line_data ))
    {
        double rad, fn1, fn2, fn3;
        stringstream stream;
        
        stream << line_data;
        stream >> rad >> fn1 >> fn2 >> fn3;
        
        f1.push_back( fn1 );
        f2.push_back( fn2 );
        f3.push_back( fn3 );
    }
    
    ef.push_back( f1 );
    f1.clear();
    ef.push_back( f2 );
    f2.clear();
    ef.push_back( f3 );
    f3.clear();
    
    ifs_5.close();
    
    /*double ** matrix_1;
    matrix_1 = new double *[5];
    for (int counter_2 = 0; counter_2 < 5; ++counter_2)
    {
        matrix_1[counter_2] = new double [5];
    }
    
    matrix_1[0][0] = 0;
    matrix_1[1][1] = 0;
    matrix_1[2][2] = 0;
    matrix_1[3][3] = 0;
    matrix_1[4][4] = 0;
    
    int function = 2;
    
    double max_r = (int)af[function].size();
    
    if (max_r > (int)bf[function].size()) max_r = (int)bf[function].size();
    
    double max_diff = 0;
    
    for (int counter = 0; counter < max_r; ++counter)
    {
        double diff = abs( af[function][counter] - bf[function][counter] );
        
        if (diff > max_diff) max_diff = diff;
    }
    
    matrix_1[0][1] = matrix_1[1][0] = max_diff;
    
    max_r = (int)af[function].size();
    
    if (max_r > (int)cf[function].size()) max_r = (int)cf[function].size();
    
    max_diff = 0;
    
    for (int counter = 0; counter < max_r; ++counter)
    {
        double diff = abs( af[function][counter] - cf[function][counter] );
        
        if (diff > max_diff) max_diff = diff;
    }
    
    matrix_1[0][2] = matrix_1[2][0] = max_diff;
    
    max_r = (int)af[function].size();
    
    if (max_r > (int)df[function].size()) max_r = (int)df[function].size();
    
    max_diff = 0;
    
    for (int counter = 0; counter < max_r; ++counter)
    {
        double diff = abs( af[function][counter] - df[function][counter] );
        
        if (diff > max_diff) max_diff = diff;
    }
    
    matrix_1[0][3] = matrix_1[3][0] = max_diff;
    
    max_r = (int)af[function].size();
    
    if (max_r > (int)ef[function].size()) max_r = (int)ef[function].size();
    
    max_diff = 0;
    
    for (int counter = 0; counter < max_r; ++counter)
    {
        double diff = abs( af[function][counter] - ef[function][counter] );
        
        if (diff > max_diff) max_diff = diff;
    }
    
    matrix_1[0][4] = matrix_1[4][0] = max_diff;
    
    max_r = (int)bf[function].size();
    
    if (max_r > (int)cf[function].size()) max_r = (int)cf[function].size();
    
    max_diff = 0;
    
    for (int counter = 0; counter < max_r; ++counter)
    {
        double diff = abs( bf[function][counter] - cf[function][counter] );
        
        if (diff > max_diff) max_diff = diff;
    }
    
    matrix_1[1][2] = matrix_1[2][1] = max_diff;
    
    max_r = (int)bf[function].size();
    
    if (max_r > (int)df[function].size()) max_r = (int)df[function].size();
    
    max_diff = 0;
    
    for (int counter = 0; counter < max_r; ++counter)
    {
        double diff = abs( bf[function][counter] - df[function][counter] );
        
        if (diff > max_diff) max_diff = diff;
    }
    
    matrix_1[1][3] = matrix_1[3][1] = max_diff;
    
    max_r = (int)bf[function].size();
    
    if (max_r > (int)ef[function].size()) max_r = (int)ef[function].size();
    
    max_diff = 0;
    
    for (int counter = 0; counter < max_r; ++counter)
    {
        double diff = abs( bf[function][counter] - ef[function][counter] );
        
        if (diff > max_diff) max_diff = diff;
    }
    
    matrix_1[1][4] = matrix_1[4][1] = max_diff;
    
    max_r = (int)cf[function].size();
    
    if (max_r > (int)df[function].size()) max_r = (int)df[function].size();
    
    max_diff = 0;
    
    for (int counter = 0; counter < max_r; ++counter)
    {
        double diff = abs( cf[function][counter] - df[function][counter] );
        
        if (diff > max_diff) max_diff = diff;
    }
    
    matrix_1[2][3] = matrix_1[3][2] = max_diff;
    
    max_r = (int)cf[function].size();
    
    if (max_r > (int)ef[function].size()) max_r = (int)ef[function].size();
    
    max_diff = 0;
    
    for (int counter = 0; counter < max_r; ++counter)
    {
        double diff = abs( cf[function][counter] - ef[function][counter] );
        
        if (diff > max_diff) max_diff = diff;
    }
    
    matrix_1[2][4] = matrix_1[4][2] = max_diff;
    
    max_r = (int)df[function].size();
    
    if (max_r > (int)ef[function].size()) max_r = (int)ef[function].size();
    
    max_diff = 0;
    
    for (int counter = 0; counter < max_r; ++counter)
    {
        double diff = abs( df[function][counter] - ef[function][counter] );
        
        if (diff > max_diff) max_diff = diff;
    }
    
    matrix_1[3][4] = matrix_1[4][3] = max_diff;
    
    cout << matrix_1[0][0] << " " << matrix_1[0][1] << " " << matrix_1[0][2] << " " << matrix_1[0][3] << " " << matrix_1[0][4] << endl;
    cout << matrix_1[1][0] << " " << matrix_1[1][1] << " " << matrix_1[1][2] << " " << matrix_1[1][3] << " " << matrix_1[1][4] << endl;
    cout << matrix_1[2][0] << " " << matrix_1[2][1] << " " << matrix_1[2][2] << " " << matrix_1[2][3] << " " << matrix_1[2][4] << endl;
    cout << matrix_1[3][0] << " " << matrix_1[3][1] << " " << matrix_1[3][2] << " " << matrix_1[3][3] << " " << matrix_1[3][4] << endl;
    cout << matrix_1[4][0] << " " << matrix_1[4][1] << " " << matrix_1[4][2] << " " << matrix_1[4][3] << " " << matrix_1[4][4] << endl;*/
    
    /*double ** matrix_1;
    matrix_1 = new double *[4];
    for (int counter_2 = 0; counter_2 < 4; ++counter_2)
    {
        matrix_1[counter_2] = new double [3];
    }
    
    double max_r = (int)af[0].size();
    
    if (max_r > (int)bf[0].size()) max_r = (int)bf[0].size();
    
    double max_diff = 0;
    
    for (int counter = 0; counter < max_r; ++counter)
    {
        double diff = abs( af[0][counter] - bf[0][counter] );
        
        if (diff > max_diff) max_diff = diff;
    }
    
    matrix_1[0][0] = max_diff;
    
    max_r = (int)af[1].size();
    
    if (max_r > (int)bf[1].size()) max_r = (int)bf[1].size();
    
    max_diff = 0;
    
    for (int counter = 0; counter < max_r; ++counter)
    {
        double diff = abs( af[1][counter] - bf[1][counter] );
        
        if (diff > max_diff) max_diff = diff;
    }
    
    matrix_1[0][1] = max_diff;
    
    max_r = (int)af[2].size();
    
    if (max_r > (int)bf[2].size()) max_r = (int)bf[2].size();
    
    max_diff = 0;
    
    for (int counter = 0; counter < max_r; ++counter)
    {
        double diff = abs( af[2][counter] - bf[2][counter] );
        
        if (diff > max_diff) max_diff = diff;
    }
    
    matrix_1[0][2] = max_diff;
    
    cout << matrix_1[0][0] << endl;
    cout << matrix_1[0][1] << endl;
    cout << matrix_1[0][2] << endl;*/
    
    Print_Info( start_time, start );
    
    return 0;
}
