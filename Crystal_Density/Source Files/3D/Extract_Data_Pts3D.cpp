#include <fstream>

#include "First_Order_Total_Volume.h"

void Extract_Data_Pts3D ( string const& directory, Cell3D const& cell, int sample_rate, double max_radius )
{
    ofstream ofs( directory + "Data/Results.txt" );
    
    double num_pts = max_radius * sample_rate + 1;
    
    for (double counter = 0; counter < num_pts; ++counter)
    {
        double radius = counter / (double)sample_rate;
        
        ofs << setprecision( 10 ) << radius << " " << First_Order_Total_Volume( cell, radius ) << endl;
    }
    
    ofs.close();
}
