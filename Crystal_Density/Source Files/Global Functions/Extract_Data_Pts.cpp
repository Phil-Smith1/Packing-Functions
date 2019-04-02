#include <fstream>

#include "First_Order_Total_Area.h"
#include "Second_Order_Total_Area.h"
#include "Third_Order_Total_Area.h"
#include "Fourth_Order_Total_Area.h"
#include "Areas.h"

void Extract_Data_Pts ( string const& directory, Cell& cell, int sample_rate, double& max_radius )
{
    ofstream ofs_1( directory + "Data/Results_At_Least.txt" );
    ofstream ofs_2( directory + "Data/Results_Exact.txt" );
    
    max_radius = (Norm( cell.vertices[0], cell.vertices[2] ) > Norm( cell.vertices[1], cell.vertices[3] )) ? Norm( cell.vertices[0], cell.vertices[2] ) : Norm( cell.vertices[1], cell.vertices[3] );
    max_radius += 0.01;
    
    double num_pts = max_radius * sample_rate + 1;
    
    for (double counter = 0; counter < num_pts; ++counter)
    {
        double radius = counter / (double)sample_rate;
        
        vector<double> r = { radius, radius, radius, radius, radius, radius };
        
        Frame f( cell, r );
        
        First_Order_Total_Area( f );
        
        Second_Order_Total_Area( f );
        
        Third_Order_Total_Area( f );
        
        Fourth_Order_Total_Area( f );
        
        Areas( f );
        
        ofs_1 << setprecision( 10 ) << radius << " " << f.area_at_least[0] << " " << f.area_at_least[1] << " " << f.area_at_least[2] << " " << f.area_at_least[3] << endl;
        
        ofs_2 << setprecision( 10 ) << radius << " " << f.area_exact[0] << " " << f.area_exact[1] << " " << f.area_exact[2] << " " << f.area_exact[3] << endl;
    }
    
    ofs_1.close();
    ofs_2.close();
}
