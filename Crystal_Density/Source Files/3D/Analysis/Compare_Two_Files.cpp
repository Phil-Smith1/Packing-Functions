#include <iostream>

#include "Comparing_Entries.h"

void Compare_Two_Files ( string const& filename_1, string const& filename_2 )
{
    int zone_limit = 21;
    
    vector<double> max_diff_pi( zone_limit, 0 );
    
    Comparing_Entries( filename_1, filename_2, max_diff_pi, zone_limit );
    
    ofstream ofs( "/Users/philsmith/Documents/Work/Xcode Projects/Crystal_Density/3D/Data/Completeness Tests 2/Results.txt" );
    
    ofs << "Difference between sets" << endl << endl;
    
    ofs << "Density function  Difference" << endl;
    
    for (int counter = 0; counter < zone_limit; ++counter)
    {
        ofs << left << setw( 19 ) << counter + 1;
        ofs << max_diff_pi[counter] << endl;
    }
}
