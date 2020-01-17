#include <vector>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

void Manipulate_File_Analysis ( string const& directory3D )
{
    string filename_1 = directory3D + "Data/T2 Packing Functions/Molecule_Centres/Analysis/Raw Data/beta.txt";
    string filename_2 = directory3D + "Data/T2 Packing Functions/Oxygens/Analysis/Raw Data/beta.txt";
    string filename_3 = directory3D + "Data/T2 Packing Functions/Molecule_Centres_with_Oxygens/Analysis/Raw Data/beta.txt";
    
    vector<int> diff_lengths_m, diff_lengths_o, diff_lengths_mo;
    vector<double> pi_1_m, pi_2_m, pi_3_m, pi_1_o, pi_2_o, pi_3_o, pi_1_mo, pi_2_mo, pi_3_mo, metric;
    string line_data;
    stringstream stream;
    
    diff_lengths_m.reserve( 5688 );
    diff_lengths_o.reserve( 5688 );
    diff_lengths_mo.reserve( 5688 );
    pi_1_m.reserve( 5688 );
    pi_2_m.reserve( 5688 );
    pi_3_m.reserve( 5688 );
    pi_1_o.reserve( 5688 );
    pi_2_o.reserve( 5688 );
    pi_3_o.reserve( 5688 );
    pi_1_mo.reserve( 5688 );
    pi_2_mo.reserve( 5688 );
    pi_3_mo.reserve( 5688 );
    
    ifstream ifs_1( filename_1 );
    
    while (getline( ifs_1, line_data ))
    {
        string ID;
        int val_4;
        double val_1, val_2, val_3;
        
        stream.clear();
        stream << line_data;
        
        stream >> ID >> val_1 >> val_2 >> val_3 >> val_4;
        
        pi_1_m.push_back( val_1 );
        pi_2_m.push_back( val_2 );
        pi_3_m.push_back( val_3 );
        diff_lengths_m.push_back( val_4 );
    }
    
    ifstream ifs_2( filename_2 );
    
    while (getline( ifs_2, line_data ))
    {
        string ID;
        int val_4;
        double val_1, val_2, val_3;
        
        stream.clear();
        stream << line_data;
        
        stream >> ID >> val_1 >> val_2 >> val_3 >> val_4;
        
        pi_1_o.push_back( val_1 );
        pi_2_o.push_back( val_2 );
        pi_3_o.push_back( val_3 );
        diff_lengths_o.push_back( val_4 );
    }
    
    ifstream ifs_3( filename_3 );
    
    while (getline( ifs_3, line_data ))
    {
        string ID;
        int val_4;
        double val_1, val_2, val_3;
        
        stream.clear();
        stream << line_data;
        
        stream >> ID >> val_1 >> val_2 >> val_3 >> val_4;
        
        pi_1_mo.push_back( val_1 );
        pi_2_mo.push_back( val_2 );
        pi_3_mo.push_back( val_3 );
        diff_lengths_mo.push_back( val_4 );
    }
    
    for (int counter = 0; counter < 5688; ++counter)
    {
        double met = pi_1_m[counter] + pi_1_o[counter] + pi_1_mo[counter] + pi_2_m[counter] + pi_2_o[counter] + pi_2_mo[counter] + pi_3_m[counter] + pi_3_o[counter] + pi_3_mo[counter];
        
        metric.push_back( met );
    }
    
    multimap<double, int> list;
    
    for (int counter = 0; counter < 5688; ++counter)
    {
        list.insert( pair<double, int>( metric[counter], counter ) );
    }
    
    ofstream ofs( directory3D + "Data/T2 Packing Functions/Analysis/beta.txt" );
    
    for (int counter_1 = 0; counter_1 < 5688; ++counter_1)
    {
        auto iter = next( list.begin(), counter_1 );
        
        for (int counter_2 = 0; counter_2 < 5688; ++counter_2)
        {
            if (counter_2 == (*iter).second)
            {
                //if (diff_lengths_m[counter_2] < 2 && diff_lengths_o[counter_2] < 2 && diff_lengths_mo[counter_2] < 2) ofs << "ID" <<  counter_2 + 1 << " " << pi_1_m[counter_2] << " " << pi_2_m[counter_2] << " " << pi_3_m[counter_2] << " " << pi_1_o[counter_2] << " " << pi_2_o[counter_2] << " " << pi_3_o[counter_2] << " " << pi_1_mo[counter_2] << " " << pi_2_mo[counter_2] << " " << pi_3_mo[counter_2] << " " << diff_lengths_m[counter_2] << " " << diff_lengths_o[counter_2] << " " << diff_lengths_mo[counter_2] << " " << metric[counter_2] << endl;
                
                ofs << "ID" <<  counter_2 + 1 << " " << pi_1_m[counter_2] << " " << pi_2_m[counter_2] << " " << pi_3_m[counter_2] << " " << pi_1_o[counter_2] << " " << pi_2_o[counter_2] << " " << pi_3_o[counter_2] << " " << pi_1_mo[counter_2] << " " << pi_2_mo[counter_2] << " " << pi_3_mo[counter_2] << " " << diff_lengths_m[counter_2] << " " << diff_lengths_o[counter_2] << " " << diff_lengths_mo[counter_2] << " " << metric[counter_2] << endl;
                
                //ofs << "ID" <<  counter_2 + 1 << " " << pi_1[counter_2] << " " << pi_2[counter_2] << " " << pi_3[counter_2] << " " << diff_lengths[counter_2] << " " << metric[counter_2] << endl;
                
                break;
            }
        }
    }
}

