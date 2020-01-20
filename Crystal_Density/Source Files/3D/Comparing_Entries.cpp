#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

void Comparing_Entries( string const& filename_1, string const& filename_2, double& max_diff_pi_1, double& max_diff_pi_2, double& max_diff_pi_3, int& difference_in_length )
{
    ifstream ifs_1( filename_1 );
    ifstream ifs_2( filename_2 );
    
    string line_data;
    stringstream stream;
    vector<vector<double>> file_1, file_2;
    vector<double> pi_1, pi_2, pi_3;
    
    while (getline( ifs_1, line_data ))
    {
        double col_1, col_2, col_3, col_4;
        stringstream stream;
        
        stream << line_data;
        stream >> col_1 >> col_2 >> col_3 >> col_4;
        
        pi_1.push_back( col_2 );
        pi_2.push_back( col_3 );
        pi_3.push_back( col_4 );
    }
    
    file_1.push_back( pi_1 );
    pi_1.clear();
    file_1.push_back( pi_2 );
    pi_2.clear();
    file_1.push_back( pi_3 );
    pi_3.clear();
    
    ifs_1.close();
    
    while (getline( ifs_2, line_data ))
    {
        double col_1, col_2, col_3, col_4;
        stringstream stream;
        
        stream << line_data;
        stream >> col_1 >> col_2 >> col_3 >> col_4;
        
        pi_1.push_back( col_2 );
        pi_2.push_back( col_3 );
        pi_3.push_back( col_4 );
    }
    
    file_2.push_back( pi_1 );
    pi_1.clear();
    file_2.push_back( pi_2 );
    pi_2.clear();
    file_2.push_back( pi_3 );
    pi_3.clear();
    
    ifs_2.close();
    
    double max_r = (int)file_1[0].size();
    
    if (max_r > (int)file_2[0].size()) max_r = (int)file_2[0].size();
    
    difference_in_length = (int)file_2[0].size() - (int)file_1[0].size();
    
    double maximum_diff_pi_1 = 0, maximum_diff_pi_2 = 0, maximum_diff_pi_3 = 0;
    
    for (int counter = 0; counter < max_r; ++counter)
    {
        double diff = abs( file_1[0][counter] - file_2[0][counter] );
        
        if (diff > maximum_diff_pi_1) maximum_diff_pi_1 = diff;
        
        diff = abs( file_1[1][counter] - file_2[1][counter] );
        
        if (diff > maximum_diff_pi_2) maximum_diff_pi_2 = diff;
        
        diff = abs( file_1[2][counter] - file_2[2][counter] );
        
        if (diff > maximum_diff_pi_3) maximum_diff_pi_3 = diff;
    }
    
    max_diff_pi_1 = maximum_diff_pi_1;
    max_diff_pi_2 = maximum_diff_pi_2;
    max_diff_pi_3 = maximum_diff_pi_3;
}
