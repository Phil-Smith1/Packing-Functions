#include <vector>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

void Manipulate_File_Analysis ( string const& directory3D )
{
    string filename_1 = directory3D + "Data/T2 Packing Functions/Comparison Files/Raw Data/alpha.txt";
    
    vector<int> diff_lengths;
    vector<double> pi_1, pi_2, pi_3, metric;
    string line_data;
    stringstream stream;
    
    diff_lengths.reserve( 5688 );
    pi_1.reserve( 5688 );
    pi_2.reserve( 5688 );
    pi_3.reserve( 5688 );
    
    ifstream ifs( filename_1 );
    
    while (getline( ifs, line_data ))
    {
        string ID;
        int val_4;
        double val_1, val_2, val_3;
        
        stream.clear();
        stream << line_data;
        
        stream >> ID >> val_1 >> val_2 >> val_3 >> val_4;
        
        pi_1.push_back( val_1 );
        pi_2.push_back( val_2 );
        pi_3.push_back( val_3 );
        diff_lengths.push_back( val_4 );
        
        double met = val_1 + val_2 + val_3;
        
        metric.push_back( met );
    }
    
    multimap<double, int> list;
    
    for (int counter = 0; counter < 5688; ++counter)
    {
        list.insert( pair<double, int>( metric[counter], counter ) );
    }
    
    ofstream ofs( directory3D + "Data/T2 Packing Functions/alpha.txt" );
    
    for (int counter_1 = 0; counter_1 < 5688; ++counter_1)
    {
        auto iter = next( list.begin(), counter_1 );
        
        for (int counter_2 = 0; counter_2 < 5688; ++counter_2)
        {
            if (counter_2 == (*iter).second)
            {
                if (diff_lengths[counter_2] < 2) ofs << "ID" <<  counter_2 + 1 << " " << pi_1[counter_2] << " " << pi_2[counter_2] << " " << pi_3[counter_2] << " " << diff_lengths[counter_2] << " " << metric[counter_2] << endl;
                
                break;
            }
        }
    }
}

