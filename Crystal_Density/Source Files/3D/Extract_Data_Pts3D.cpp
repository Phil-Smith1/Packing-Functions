#include <fstream>

#include "First_Order_Total_Volume.h"
#include "Second_Order_Total_Volume.h"

void Extract_Data_Pts3D ( string const& directory, Cell3D const& cell, int sample_rate, double max_radius )
{
    ofstream ofs( directory + "Data/Results.txt" );
    
    double num_pts = max_radius * sample_rate + 1;
    
    for (double counter = 0; counter < num_pts; ++counter)
    {
        double radius = counter / (double)sample_rate;
        
        double first_order_total_volume = First_Order_Total_Volume( cell, radius );
        
        double second_order_total_volume = Second_Order_Total_Volume( cell, radius );
        
        if (abs( first_order_total_volume ) < tiny_num) first_order_total_volume = tiny_num;
        
        if (abs( second_order_total_volume ) < tiny_num) second_order_total_volume = tiny_num;
        
        ofs << setprecision( 10 ) << radius << " " << first_order_total_volume / (double)cell.vol << " " << second_order_total_volume / (double)cell.vol << " " << (first_order_total_volume - second_order_total_volume) / (double)cell.vol << endl;
    }
    
    ofs.close();
}
