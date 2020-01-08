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
#include "Comparing_Entries.h"
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
    
    if (comparing)
    {
        /*vector<int> length_diff;
        vector<double> pi_1, pi_2, pi_3, sum, metric;
        
        length_diff.reserve( 5688 );
        pi_1.reserve( 5688 );
        pi_2.reserve( 5688 );
        pi_3.reserve( 5688 );
        sum.reserve( 5688 );
        metric.reserve( 5688 );
        
        string filename_1 = directory3D + "Data/T2 Packing Functions/Synthesised Crystals/delta.txt";
        
        for (int counter = 0; counter < 5688; ++counter)
        {
            string filename_2 = directory3D + "Data/T2 Packing Functions/Dataset/" + to_string( counter + 1 ) + ".txt";
            
            int difference_in_length;
            double max_diff_pi_1, max_diff_pi_2, max_diff_pi_3;
            
            Comparing_Entries( filename_1, filename_2, max_diff_pi_1, max_diff_pi_2, max_diff_pi_3, difference_in_length );
            
            length_diff.push_back( difference_in_length );
            pi_1.push_back( max_diff_pi_1 );
            pi_2.push_back( max_diff_pi_2 );
            pi_3.push_back( max_diff_pi_3 );
            sum.push_back( max_diff_pi_1 + max_diff_pi_2 + max_diff_pi_3 );
            
            double met = pi_1[counter] + pi_2[counter] + pi_3[counter];
            
            //met *= pow( 2, difference_in_length );
            
            metric.push_back( met );
        }
        
        multimap<double, int> list;
        
        for (int counter = 0; counter < 5688; ++counter)
        {
            list.insert( pair<double, int>( metric[counter], counter ) );
        }
        
        ofstream ofs( directory3D + "Data/T2 Packing Functions/Dataset_Comparison.txt" );
        
        for (int counter_1 = 0; counter_1 < 5688; ++counter_1)
        {
            auto iter = next( list.begin(), counter_1 );
            
            for (int counter_2 = 0; counter_2 < 5688; ++counter_2)
            {
                if (counter_2 == (*iter).second)
                {
                    ofs << counter_2 + 1 << " " << length_diff[counter_2] << " " << pi_1[counter_2] << " " << pi_2[counter_2] << " " << pi_3[counter_2] << " " << sum[counter_2] << " " << metric[counter_2] << endl;
                    
                    break;
                }
            }
        }
        
        ofs.close();*/
        
        /*vector<double> A;
        vector<double> B;
        vector<double> C;
        vector<int> D;
        
        ofstream ofs_2( directory3D + "Data/T2 Packing Functions/Whole_Dataset_Comparison1.txt" );
        ofstream ofs_3( directory3D + "Data/T2 Packing Functions/Whole_Dataset_Comparison2.txt" );
        ofstream ofs_4( directory3D + "Data/T2 Packing Functions/Whole_Dataset_Comparison3.txt" );
        ofstream ofs_5( directory3D + "Data/T2 Packing Functions/Whole_Dataset_Comparison4.txt" );
        
        for (int counter_1 = 0; counter_1 < 5688; ++counter_1)
        {
            cout << counter_1 << endl;
            string filename_3 = directory3D + "Data/T2 Packing Functions/Dataset/" + to_string( counter_1 + 1 ) + ".txt";
            
            A.clear();
            B.clear();
            C.clear();
            D.clear();
            
            for (int counter_2 = counter_1; counter_2 < 5688; ++counter_2)
            {
                string filename_4 = directory3D + "Data/T2 Packing Functions/Dataset/" + to_string( counter_2 + 1 ) + ".txt";
                
                int difference_in_length;
                double max_diff_pi_1, max_diff_pi_2, max_diff_pi_3;
                
                Comparing_Entries( filename_3, filename_4, max_diff_pi_1, max_diff_pi_2, max_diff_pi_3, difference_in_length );
                
                //double met = max_diff_pi_1 * 3 + max_diff_pi_2 * 2 + max_diff_pi_3;
                
                //met *= pow( 2, difference_in_length );
                
                A.push_back( max_diff_pi_1 );
                B.push_back( max_diff_pi_2 );
                C.push_back( max_diff_pi_3 );
                D.push_back( difference_in_length );
            }
            
            ofs_2 << A[0];
            ofs_3 << B[0];
            ofs_4 << C[0];
            ofs_5 << D[0];
            
            for (int counter_2 = 1; counter_2 < 5688 - counter_1; ++counter_2)
            {
                ofs_2 << " " << A[counter_2];
                ofs_3 << " " << B[counter_2];
                ofs_4 << " " << C[counter_2];
                ofs_5 << " " << D[counter_2];
            }
            
            ofs_2 << endl;
            ofs_3 << endl;
            ofs_4 << endl;
            ofs_5 << endl;
        }
        
        ofs_2.close();
        ofs_3.close();
        ofs_4.close();
        ofs_5.close();*/
        
        vector<double> E;
        E.reserve( 5688 );
        
        ofstream ofs_2( directory3D + "Data/T2 Packing Functions/Whole_Dataset_Comparison1.txt" );
        
        ifstream ifs1( directory3D + "Data/T2 Packing Functions/Whole_Dataset_Comparison/Pi_1.txt" );
        ifstream ifs2( directory3D + "Data/T2 Packing Functions/Whole_Dataset_Comparison/Pi_2.txt" );
        ifstream ifs3( directory3D + "Data/T2 Packing Functions/Whole_Dataset_Comparison/Pi_3.txt" );
        ifstream ifs4( directory3D + "Data/T2 Packing Functions/Whole_Dataset_Comparison/Diff_Lengths.txt" );
        
        for (int counter_1 = 0; counter_1 < 5688; ++counter_1)
        {
            cout << counter_1 << endl;
            
            string line_data;
            stringstream stream;
            
            vector<double> B;
            vector<double> C;
            vector<double> D;
            vector<int> F;
            
            getline( ifs1, line_data );
            stream << line_data;
            
            for (int counter = 0; counter < 5688 - counter_1; ++counter)
            {
                double val;
                
                stream >> val;
                
                B.push_back( val );
            }
            
            getline( ifs2, line_data );
            stream.clear();
            stream << line_data;
            
            for (int counter = 0; counter < 5688 - counter_1; ++counter)
            {
                double val;
                
                stream >> val;
                
                C.push_back( val );
            }
            
            getline( ifs3, line_data );
            stream.clear();
            stream << line_data;
            
            for (int counter = 0; counter < 5688 - counter_1; ++counter)
            {
                double val;
                
                stream >> val;
                
                D.push_back( val );
            }
            
            getline( ifs4, line_data );
            stream.clear();
            stream << line_data;
            
            for (int counter = 0; counter < 5688 - counter_1; ++counter)
            {
                double val;
                
                stream >> val;
                
                F.push_back( val );
            }
            
            for (int counter_2 = counter_1; counter_2 < 5688; ++counter_2)
            {
                double val = 3 * B[counter_2 - counter_1] + 2 * C[counter_2 - counter_1] + D[counter_2 - counter_1];
                
                val *= pow( 2, F[counter_2 - counter_1] );
                
                E.push_back( val );
            }
            
            ofs_2 << E[0];
            
            for (int counter_2 = 1; counter_2 < 5688 - counter_1; ++counter_2)
            {
                ofs_2 << " " << E[counter_2];
            }
            
            ofs_2 << endl;
            
            E.clear();
        }
        
        ifs1.close();
        ifs2.close();
        ifs3.close();
        ofs_2.close();
        
        /*ifstream ifs1( directory3D + "Data/T2 Packing Functions/Whole_Dataset_Comparison/Pi_1.txt" );
        ifstream ifs2( directory3D + "Data/T2 Packing Functions/Whole_Dataset_Comparison/Pi_2.txt" );
        ifstream ifs3( directory3D + "Data/T2 Packing Functions/Whole_Dataset_Comparison/Pi_3.txt" );
        
        int row = 2;
        int column = 3;
        string line_data;
        stringstream stream;
        
        vector<double> B;
        vector<double> C;
        vector<double> D;
        
        for (int counter = 0; counter < row; ++counter)
        {
            getline( ifs1, line_data );
        }
        
        stream << line_data;
        
        for (int counter = 0; counter < 5688 + 1 - row; ++counter)
        {
            double val;
            
            stream >> val;
            
            B.push_back( val );
        }
        
        for (int counter = 0; counter < row; ++counter)
        {
            getline( ifs2, line_data );
        }
        
        stream.clear();
        stream << line_data;
        
        for (int counter = 0; counter < 5688 + 1 - row; ++counter)
        {
            double val;
            
            stream >> val;
            
            C.push_back( val );
        }
        
        for (int counter = 0; counter < row; ++counter)
        {
            getline( ifs3, line_data );
        }
        
        stream.clear();
        stream << line_data;
        
        for (int counter = 0; counter < 5688 + 1 - row; ++counter)
        {
            double val;
            
            stream >> val;
            
            D.push_back( val );
        }
        
        ifs1.close();
        ifs2.close();
        ifs3.close();*/
    }
    
    Print_Info( start_time, start );
    
    return 0;
}
