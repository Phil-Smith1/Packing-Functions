#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

void Comparing_Entries( string const& filename_1, string const& filename_2, vector<double>& max_diff_pi, int zone_limit )
{
    ifstream ifs_1( filename_1 );
    ifstream ifs_2( filename_2 );
    
    string line_data;
    vector<vector<double>> file_1, file_2;
    vector<vector<double>> pi( zone_limit );
    
    while (getline( ifs_1, line_data ))
    {
        vector<double> col( zone_limit + 1 );
        stringstream stream;
        
        stream << line_data;
        
        for (int counter = 0; counter < zone_limit + 1; ++counter)
        {
            stream >> col[counter];
        }
        
        for (int counter = 0; counter < zone_limit; ++counter)
        {
            pi[counter].push_back( col[counter + 1] );
        }
    }
    
    for (int counter = 0; counter < zone_limit; ++counter)
    {
        file_1.push_back( pi[counter] );
        pi[counter].clear();
    }
    
    ifs_1.close();
    
    while (getline( ifs_2, line_data ))
    {
        vector<double> col( zone_limit + 1 );
        stringstream stream;
        
        stream << line_data;
        
        for (int counter = 0; counter < zone_limit + 1; ++counter)
        {
            stream >> col[counter];
        }
        
        for (int counter = 0; counter < zone_limit; ++counter)
        {
            pi[counter].push_back( col[counter + 1] );
        }
    }
    
    for (int counter = 0; counter < zone_limit; ++counter)
    {
        file_2.push_back( pi[counter] );
        pi[counter].clear();
    }
    
    ifs_2.close();
    
    int max_r_1 = (int)file_1[0].size();
    int max_r_2 = (int)file_2[0].size();
    int max_r;
    
    if (max_r_1 > max_r_2) max_r = max_r_2;
    else max_r = max_r_1;
    
    vector<double> maximum_diff_pi( zone_limit, 0 );
    
    for (int counter_1 = 0; counter_1 < max_r; ++counter_1)
    {
        for (int counter_2 = 0; counter_2 < zone_limit; ++counter_2)
        {
            double diff = abs( file_1[counter_2][counter_1] - file_2[counter_2][counter_1] );
            
            if (diff > maximum_diff_pi[counter_2]) maximum_diff_pi[counter_2] = diff;
        }
    }
    
    if (max_r_1 > max_r_2)
    {
        for (int counter_1 = max_r_2; counter_1 < max_r_1; ++counter_1)
        {
            for (int counter_2 = 0; counter_2 < zone_limit; ++counter_2)
            {
                double diff = file_1[counter_2][counter_1];
                
                if (diff > maximum_diff_pi[counter_2]) maximum_diff_pi[counter_2] = diff;
            }
        }
    }
    
    if (max_r_2 > max_r_1)
    {
        for (int counter_1 = max_r_1; counter_1 < max_r_2; ++counter_1)
        {
            for (int counter_2 = 0; counter_2 < zone_limit; ++counter_2)
            {
                double diff = file_2[counter_2][counter_1];
                
                if (diff > maximum_diff_pi[counter_2]) maximum_diff_pi[counter_2] = diff;
            }
        }
    }
    
    for (int counter = 0; counter < zone_limit; ++counter)
    {
        max_diff_pi[counter] = maximum_diff_pi[counter];
    }
}
