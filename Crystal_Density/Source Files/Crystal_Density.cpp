// Code for computing Packing Functions.

// Include for gemmi, for parsing CIFs.

#include <gemmi/cif.hpp>

// Includes.

#include "Parameters.h"
#include "Packing_Functions3D.h"
#include "Make_Cells3D.h"
#include "Make_T2_Cells.h"
#include "Deformation.h"
#include "Cell_Data.h"
#include "Draw_Cells.h"
#include "Packing_Functions.h"
#include "GIF.h"
#include "Compare_Two_Files.h"
#include "Dataset_Dataset_Analysis.h"
#include "Manipulate_Dataset_Dataset_Analysis.h"
#include "File_Dataset_Analysis.h"
#include "Manipulate_File_Analysis.h"
#include "Read_Dataset_Matrix.h"
#include "Print_Info.h"

#include "Brillouin_Surrounding_Pts.h"
#include "Compute_Brillouin_Zones.h"
#include "Extract_Tetra_Cells.h"
#include "Sphere_Tetrahedron_Intersection.h"

#include "Triangle_Area3D.h"

// Main.

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
        
        if (T2) // Runs for T2 crystals.
        {
            for (int counter = 0; counter < input3D.iterations; ++counter)
            {
                cout << "Iteration: " << counter << "." << endl;
                
                Make_T2_Cells( dataset_directory, input3D, cells, counter + 1 ); // Adds a new T2 cell.
                
                Packing_Functions3D( directory3D, input3D, graph_params, cells[counter], counter + 1 );
            }
        }
        
        else // Runs for custom point clouds.
        {
            Make_Cells3D( input3D, cells ); // Initialises the vector of cells.
            
            for (int counter = 0; counter < cells.size(); ++counter) // Looping over the vector of cells.
            {
                cout << "Iteration: " << counter << "." << endl;
                
                Packing_Functions3D( directory3D, input3D, graph_params, cells[counter], counter );
            }
            
            if (input3D.deformation_type != 0) GIF( directory3D + "Graphs/Deformation", "Deform", input3D.iterations );
        }
    }
    
    if (analysis)
    {
        //string filename_1 = directory3D + "Data/T2 Packing Functions/Synthesised Crystals/beta.txt";
        //string filename_2 = directory3D + "Data/T2 Packing Functions/Synthesised Crystals/delta.txt";
        
        //Compare_Two_Files( filename_1, filename_2 );
        
        //File_Dataset_Analysis( directory3D );
        
        Manipulate_File_Analysis( directory3D );
    }
    
    if (brillouin)
    {
        for (int file_index = 13; file_index < 14; ++file_index)
        {
            /*int perim = 5;
            
            int zone_limit = 9;
            
            vector<P3_E> centre_E;
            vector<P3> centre;
            
            vector<multimap<double, P3_E>> pts;
            
            double cell_volume = 0;
            
            if (T2)
            {
                string filename = "T2_" + to_string( file_index + 1 ) + "_num_molGeom.cif";
                
                string file_path = dataset_directory + filename;
                
                cif::Document cif_file = cif::read_file( file_path ); // Accessing CIF file.
                
                cif::Block * block = &(*(++cif_file.blocks.begin())); // Pointer to relevant block.
                
                vector<pair<string, double>> cell_shape;
                
                Read_Cell_Shape( block, cell_shape ); // Reading cell shape.
                
                if (input3D.experimental_T2) Assign_Experimental_Cell_Shape( cell_shape, input3D.experimental_T2_label );
                
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
                
                Obtain_T2_Centres( atom_cloud, input3D.type_of_experiment, T2_centres );
                
                if (input3D.experimental_T2) Assign_Experimental_Centres( T2_centres, matrix, input3D.experimental_T2_label, input3D.type_of_experiment );
                
                pts.resize( T2_centres.size() );
                
                for (int counter = 0; counter < T2_centres.size(); ++counter)
                {
                    Brillouin_Surrounding_Pts( perim, matrix, counter, T2_centres, pts[counter] );
                }
                
                cell_volume = Cell_Volume( cell_shape );
                
                for (int counter = 0; counter < T2_centres.size(); ++counter)
                {
                    centre_E.push_back( P3_E( T2_centres[counter].x(), T2_centres[counter].y(), T2_centres[counter].z() ) );
                    centre.push_back( T2_centres[counter] );
                }
            }
            
            else
            {
                multimap<double, P3_E> pts_copy;
                
                P3 p1 = input3D.parallelepiped_vectors[0], p2 = input3D.parallelepiped_vectors[1], p3 = input3D.parallelepiped_vectors[2];
                
                centre_E.push_back( P3_E( 0, 0, 0 ) );
                centre.push_back( P3( 0, 0, 0 ) );
                
                V3_E v1_E = V3_E( p1.x(), p1.y(), p1.z() );
                V3_E v2_E = V3_E( p2.x(), p2.y(), p2.z() );
                V3_E v3_E = V3_E( p3.x(), p3.y(), p3.z() );
                
                for (int counter_1 = -perim; counter_1 < perim + 1; ++counter_1)
                {
                    for (int counter_2 = -perim; counter_2 < perim + 1; ++counter_2)
                    {
                        for (int counter_3 = -perim; counter_3 < perim + 1; ++counter_3)
                        {
                            if (counter_1 == 0 && counter_2 == 0 && counter_3 == 0) continue;
                            
                            V3_E v = counter_1 * v1_E + counter_2 * v2_E + counter_3 * v3_E;
                            
                            P3_E p = P3_E( v.x(), v.y(), v.z() );
                            
                            double dist = to_double( squared_distance( centre_E[0], p ) );
                            
                            pts_copy.insert( pair<double, P3_E>( dist, p ) );
                        }
                    }
                }
                
                pts.push_back( pts_copy );
            }
            
            vector<vector<vector<Tetrahedron>>> zones_of_tetras( pts.size() );
            
            clock_t time_1 = clock();
            
            for (int counter = 0; counter < pts.size(); ++counter)
            {
                Compute_Brillouin_Zones( pts[counter], zone_limit, centre_E[counter], zones_of_tetras[counter] );
            }
            
            clock_t time_2 = clock();
            
            double time_taken = (time_2 - time_1) / (double)CLOCKS_PER_SEC;
            
            cout << "Time taken = " << time_taken << endl;
            
            vector<vector<vector<vector<Pl3>>>> tetra_cells( pts.size() );
            
            for (int counter = 0; counter < pts.size(); ++counter)
            {
                Extract_Tetra_Cells( zones_of_tetras[counter], zone_limit, tetra_cells[counter] );
            }
            
            if (!T2)
            {
                for (int counter = 0; counter < zones_of_tetras[0].size(); ++counter)
                {
                    cell_volume += to_double( zones_of_tetras[0][0][counter].volume() );
                }
            }
            
            string dir = directory3D + "Data/Brill/" + to_string( file_index + 1 ) + ".txt";
            
            ofstream ofs( dir );
            
            double final_radius = 20;
            
            double num_pts = final_radius * 10;
            
            //num_pts = 1;
            
            bool limit_non_zero = false;
            
            for (int counter_1 = 0; counter_1 < num_pts; ++counter_1)
            {
                double radius = counter_1 / (double)10;
                
                //radius = 8.5;
                
                if (counter_1 == 1) radius += 0.1;
                if (counter_1 == 2) radius += 0.2;
                
                vector<double> volume( zone_limit, 0 );
                
                for (int counter_4 = 0; counter_4 < pts.size(); ++counter_4)
                {
                    Sphere s( centre[counter_4], radius );
                    
                    for (int counter_2 = 0; counter_2 < zone_limit; ++counter_2)
                    {
                        for (int counter_3 = 0; counter_3 < tetra_cells[counter_4][counter_2].size(); ++counter_3)
                        {
                            volume[counter_2] += Sphere_Tetrahedron_Intersection( s, tetra_cells[counter_4][counter_2][counter_3] );
                        }
                    }
                }
                
                for (int counter_2 = 0; counter_2 < zone_limit; ++counter_2)
                {
                    if (abs( volume[counter_2] ) < tiny_num) volume[counter_2] = tiny_num;
                }
                
                vector<double> pi( zone_limit );
                
                for (int counter_2 = 0; counter_2 < zone_limit - 1; ++counter_2)
                {
                    pi[counter_2] = volume[counter_2] - volume[counter_2 + 1];
                    pi[counter_2] = pi[counter_2] / (double)cell_volume;
                }
                
                pi[zone_limit - 1] = volume[zone_limit - 1];
                
                if (!limit_non_zero)
                {
                    if (pi[zone_limit - 2] > tiny_num * 1e9)
                    {
                        limit_non_zero = true;
                    }
                }
                
                if (limit_non_zero)
                {
                    if (pi[zone_limit - 2] < tiny_num * 1e8)
                    {
                        final_radius = radius;
                        break;
                    }
                }
                
                ofs << setprecision( 10 ) << radius;
                
                for (int counter_2 = 0; counter_2 < zone_limit - 1; ++counter_2)
                {
                    ofs << " " << pi[counter_2];
                }
                
                ofs << endl;
            }
            
            ofs.close();*/
            
            Gnuplot gp;
            
            gp << "cd \"" << directory3D << "\"\n";
            
            gp << "set terminal pdfcairo size 8.5, 3.5\n";
            
            gp << "set border 3\n";
            gp << "set grid\n";
            gp << "set bmargin 4.5\n";
            gp << "set lmargin 8.5\n";
            
            if (false)
            {
                gp << "set tmargin 5\n";
                gp << "set title '" << graph_params.title_str << "' font ', 20' offset 0, 2\n";
            }
            
            else gp << "set tmargin 3\n";
            
            gp << "set rmargin 2\n";
            
            gp << "set ylabel '{/Symbol D}_i(r)' font ', 20' offset -0.5, 0\n";
            gp << "set xlabel 'Radius of Balls (Angstroms)' font ', 20' offset 0, -0.3\n";
            
            gp << "set xrange [0: " << 16.9 << "]\n";
            gp << "set yrange [0: " << 1 << "]\n";
            gp << "set xtics font ', 18'\n";
            gp << "set ytics font ', 18'\n";
            
            gp << "set key horizontal at graph 0.5, graph 1.04 center bottom font ', 18'\n";
            
            gp << "set style line 1 lc rgb '#0d61ec' lw 3\n";
            gp << "set style line 2 lc rgb '#24ae1d' lw 3\n";
            gp << "set style line 3 lc rgb '#ffae00' lw 3\n";
            gp << "set style line 4 lc rgb '#e70000' lw 3\n";
            gp << "set style line 5 lc rgb '#db0dec' lw 3\n";
            gp << "set style line 6 lc rgb '#7B0985' lw 3\n";
            gp << "set style line 7 lc rgb '#87663E' lw 3\n";
            gp << "set style line 8 lc rgb '#000000' lw 3\n";
            gp << "set style line 9 lc rgb '#000000' pt 7 ps 0.5\n";
            gp << "set style line 11 dt 2 lc rgb '#0d61ec' lw 3\n";
            gp << "set style line 12 dt 2 lc rgb '#24ae1d' lw 3\n";
            gp << "set style line 13 dt 2 lc rgb '#ffae00' lw 3\n";
            gp << "set style line 14 dt 2 lc rgb '#e70000' lw 3\n";
            gp << "set style line 15 dt 2 lc rgb '#db0dec' lw 3\n";
            gp << "set style line 16 dt 2 lc rgb '#7B0985' lw 3\n";
            gp << "set style line 17 dt 2 lc rgb '#87663E' lw 3\n";
            gp << "set style line 18 dt 2 lc rgb '#000000' lw 3\n";
            
            /*gp << "set output \"Graphs/Brill/" + to_string( file_index + 1 ) + ".pdf\"\n";
            
            gp << "set samples 1000\n";
            
            string plot = "plot 'Data/Brill/" + to_string( file_index + 1 ) + ".txt' using 1:2 smooth csplines ls 1 title '{/Symbol D}_1(r)'";
            
            for (int counter = 1; counter < zone_limit - 1; ++counter)
            {
                plot += ", 'Data/Brill/" + to_string( file_index + 1 ) + ".txt' using 1:" + to_string( counter + 2 ) + "smooth csplines ls " + to_string( counter + 1 ) + " title '{/Symbol D}_" + to_string( counter + 1 ) + "(r)'";
            }
            
            plot += "\n";
            
            gp << plot;*/
            
            gp << "set output \"Graphs/Brill/gamma1.pdf\"\n";
            
            gp << "set samples 1000\n";
            
            string plot = "plot 'Data/Brill/gamma.txt' using 1:2 smooth csplines ls 1 title '{/Symbol D}_1(r)'";
            
            for (int counter = 1; counter < 9 - 1; ++counter)
            {
                plot += ", 'Data/Brill/gamma.txt' using 1:" + to_string( counter + 2 ) + "smooth csplines ls " + to_string( counter + 1 ) + " title '{/Symbol D}_" + to_string( counter + 1 ) + "(r)'";
            }
            
            plot += ", 'Data/Brill/62.txt' using 1:2 smooth csplines ls 11 notitle";
            
            for (int counter = 1; counter < 9 - 1; ++counter)
            {
                plot += ", 'Data/Brill/62.txt' using 1:" + to_string( counter + 2 ) + "smooth csplines ls " + to_string( counter + 11 ) + " notitle";
            }
            
            plot += "\n";
            
            gp << plot;
        }
        
        /*P3 cent = P3(0.951082, 2.98712, 2.97644 );
        double rad = 15.2;
        
        Pl3 pl1 = Pl3(-2.68284, 2.21299, 1.81431, -34.3814);
        Pl3 pl2 = Pl3(3.87613, 0, 0, 24.2449);
        Pl3 pl3 = Pl3(0.870735, -3.14632, 0.00826682, 30.8389);
        Pl3 pl4 = Pl3(-2.06403, 0.933328, -1.82258, -15.991);
        
        vector<Pl3> plan;
        plan.push_back(pl1);
        plan.push_back(pl2);
        plan.push_back(pl3);
        plan.push_back(pl4);
        
        L3 l1 = Line_Of_Intersection_Of_Two_Planes( plan[0].opposite(), plan[1].opposite() );
        L3 l2 = Line_Of_Intersection_Of_Two_Planes( plan[0].opposite(), plan[2].opposite() );
        
        P3 p = Intersection_Of_Two_Lines3D( l1, l2 );
        
        //Parallel_Lines( l1, l2 );
        
        //cout << plan[3].oriented_side( p ) << endl;
        
        //cout << General_Spherical_Cone( Sphere( cent, rad ), plan[0], plan[1], plan[2] ) << endl;
        
        cout << Sphere_Tetrahedron_Intersection( Sphere( cent, rad ), plan ) << endl;*/
        
        /*0.951082 2.98712 2.97644
        8.5
        2.76427 -1.0033e-13 -1.41819e-14 17.2903
        2.84582 -1.5782 1.29388 26.0098
        -1.91327 1.5782 1.29388 -24.5192
        -3.69682 1.34115e-13 -2.58776 -15.421*/
        
        /*-336.687
        3.06911 23.2989 8.85385
        9.1
        0.99194 -4.77025e-13 1.69574e-16 4.10355
        -0.495058 0.747774 -3.39561 11.5888
        0.592715 -1.27724 2.8747 9.19461
        -1.0896 0.529464 0.520906 -23.4139*/
        
        /*-32.9443
        0.951082 2.98712 2.97644
        11.2
        -2.68284 2.21299 1.81431 -34.3814
        3.87613 -1.17252e-13 3.08075e-16 24.2449
        0.870735 -3.14632 0.00826682 30.8389
        -2.06403 0.933328 -1.82258 -15.991*/
        
        /*1308.28
         2281.48
         20.2289
         62.9201
         896.212
         3.49617
         0.0332353
         2.19532
         0.441001*/
        
        /*0.0673662
         1774.15
         1755.8
         1774.15
         5.14709*/
    }
    
    Print_Info( start_time, start );
    
    return 0;
}
