#include <fstream>

#include "Input3D.h"
#include "Circumradius.h"
#include "First_Order_Total_Volume.h"
#include "Second_Order_Total_Volume.h"
#include "Third_Order_Total_Volume.h"
#include "Volumes3D.h"

void Extract_Data_Pts3D ( string const& directory, Input3D const& input, Cell3D const& cell, int index )
{
    string dir;
    
    if (input.T2) dir = directory + "Data/T2 Packing Functions/Dataset/" + to_string( index ) + ".txt";
    else dir = directory + "Data/Results.txt";
    
    if (input.experimental_T2) dir = directory + "Data/T2 Packing Functions/Synthesised Crystals/experimental.txt";
    
    ofstream ofs( dir );
    
    double num_pts = input.max_radius * input.sample_rate + 1;
    
    for (double counter = 0; counter < num_pts; ++counter)
    {
        double radius = counter / (double)input.sample_rate;
        
        if (radius > input.max_radius) radius = input.max_radius;
        
        double first_order_total_volume = First_Order_Total_Volume( cell, radius, input.parallelepiped );
        
        double second_order_total_volume = Second_Order_Total_Volume( cell, radius, input.parallelepiped );
        
        double third_order_total_volume = Third_Order_Total_Volume( cell, radius );
        
        if (abs( first_order_total_volume ) < tiny_num) first_order_total_volume = tiny_num;
        
        if (abs( second_order_total_volume ) < tiny_num) second_order_total_volume = tiny_num;
        
        if (abs( third_order_total_volume ) < tiny_num) third_order_total_volume = tiny_num;
        
        vector<double> volumes_at_least;
        vector<double> volumes_exact;
        
        Volumes3D( first_order_total_volume, second_order_total_volume, third_order_total_volume, volumes_at_least, volumes_exact );
        
        //ofs << setprecision( 10 ) << radius << " " << first_order_total_volume / (double)cell.vol << " " << second_order_total_volume / (double)cell.vol << " " << third_order_total_volume / (double)cell.vol << " " << (first_order_total_volume - second_order_total_volume + third_order_total_volume) / (double)cell.vol << endl;
        
        ofs << setprecision( 10 ) << radius << " " << volumes_exact[0] / (double)cell.vol << " " << volumes_exact[1] / (double)cell.vol << " " << volumes_exact[2] / (double)cell.vol << " " << endl;
    }
    
    ofs.close();
}
