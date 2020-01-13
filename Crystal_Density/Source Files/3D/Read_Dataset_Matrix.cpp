#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

void Read_Dataset_Matrix ( string const& directory3D )
{
    ifstream ifs_1( directory3D + "Data/T2 Packing Functions/Whole_Dataset_Comparison/Pi_1.txt" );
    ifstream ifs_2( directory3D + "Data/T2 Packing Functions/Whole_Dataset_Comparison/Pi_2.txt" );
    ifstream ifs_3( directory3D + "Data/T2 Packing Functions/Whole_Dataset_Comparison/Pi_3.txt" );
    ifstream ifs_4( directory3D + "Data/T2 Packing Functions/Whole_Dataset_Comparison/Diff_Lengths.txt" );
    
    int row = 2;
    int column = 3;
    string line_data;
    stringstream stream;
    
    vector<int> diff_lengths;
    vector<double> pi_1, pi_2, pi_3;
    
    diff_lengths.reserve( 5688 );
    pi_1.reserve( 5688 );
    pi_2.reserve( 5688 );
    pi_3.reserve( 5688 );
    
    for (int counter = 0; counter < row; ++counter)
    {
        getline( ifs_1, line_data );
    }
    
    stream << line_data;
    
    for (int counter = 0; counter < 5688 + 1 - row; ++counter)
    {
        double val;
        
        stream >> val;
        
        pi_1.push_back( val );
    }
    
    for (int counter = 0; counter < row; ++counter)
    {
        getline( ifs_2, line_data );
    }
    
    stream.clear();
    stream << line_data;
    
    for (int counter = 0; counter < 5688 + 1 - row; ++counter)
    {
        double val;
        
        stream >> val;
        
        pi_2.push_back( val );
    }
    
    for (int counter = 0; counter < row; ++counter)
    {
        getline( ifs_3, line_data );
    }
    
    stream.clear();
    stream << line_data;
    
    for (int counter = 0; counter < 5688 + 1 - row; ++counter)
    {
        double val;
        
        stream >> val;
        
        pi_3.push_back( val );
    }
    
    for (int counter = 0; counter < row; ++counter)
    {
        getline( ifs_4, line_data );
    }
    
    stream.clear();
    stream << line_data;
    
    for (int counter = 0; counter < 5688 + 1 - row; ++counter)
    {
        double val;
        
        stream >> val;
        
        diff_lengths.push_back( val );
    }
    
    ifs_1.close();
    ifs_2.close();
    ifs_3.close();
    ifs_4.close();
    
    cout << pi_1[column - row] << endl;
    cout << pi_2[column - row] << endl;
    cout << pi_3[column - row] << endl;
    cout << diff_lengths[column - row] << endl;
}

