#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cmath>

using namespace std;

void Manipulate_Dataset_Dataset_Analysis ( string const& directory3D )
{
    vector<double> metric;
    metric.reserve( 5688 );
    
    ofstream ofs( directory3D + "Data/T2 Packing Functions/Metric.txt" );
    
    ifstream ifs_1( directory3D + "Data/T2 Packing Functions/Whole_Dataset_Comparison/Pi_1.txt" );
    ifstream ifs_2( directory3D + "Data/T2 Packing Functions/Whole_Dataset_Comparison/Pi_2.txt" );
    ifstream ifs_3( directory3D + "Data/T2 Packing Functions/Whole_Dataset_Comparison/Pi_3.txt" );
    ifstream ifs_4( directory3D + "Data/T2 Packing Functions/Whole_Dataset_Comparison/Diff_Lengths.txt" );
    
    for (int counter_1 = 0; counter_1 < 5688; ++counter_1)
    {
        cout << "Comparison: " << counter_1 << endl;
        
        string line_data;
        stringstream stream;
        
        vector<int> diff_lengths;
        vector<double> pi_1, pi_2, pi_3;
        
        getline( ifs_1, line_data );
        stream << line_data;
        
        for (int counter = 0; counter < 5688 - counter_1; ++counter)
        {
            double val;
            
            stream >> val;
            
            pi_1.push_back( val );
        }
        
        getline( ifs_2, line_data );
        stream.clear();
        stream << line_data;
        
        for (int counter = 0; counter < 5688 - counter_1; ++counter)
        {
            double val;
            
            stream >> val;
            
            pi_2.push_back( val );
        }
        
        getline( ifs_3, line_data );
        stream.clear();
        stream << line_data;
        
        for (int counter = 0; counter < 5688 - counter_1; ++counter)
        {
            double val;
            
            stream >> val;
            
            pi_3.push_back( val );
        }
        
        getline( ifs_4, line_data );
        stream.clear();
        stream << line_data;
        
        for (int counter = 0; counter < 5688 - counter_1; ++counter)
        {
            double val;
            
            stream >> val;
            
            diff_lengths.push_back( val );
        }
        
        for (int counter_2 = counter_1; counter_2 < 5688; ++counter_2)
        {
            double val = 3 * pi_1[counter_2 - counter_1] + 2 * pi_2[counter_2 - counter_1] + pi_3[counter_2 - counter_1];
            
            val *= pow( 2, diff_lengths[counter_2 - counter_1] );
            
            metric.push_back( val );
        }
        
        ofs << metric[0];
        
        for (int counter_2 = 1; counter_2 < 5688 - counter_1; ++counter_2)
        {
            ofs << " " << metric[counter_2];
        }
        
        ofs << endl;
        
        metric.clear();
    }
    
    ifs_1.close();
    ifs_2.close();
    ifs_3.close();
    ofs.close();
}
