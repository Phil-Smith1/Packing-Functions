#include "Comparing_Entries.h"

void File_Dataset_Analysis ( string const& directory3D )
{
    vector<int> length_diff;
    vector<double> pi_1, pi_2, pi_3;
    
    length_diff.reserve( 5688 );
    pi_1.reserve( 5688 );
    pi_2.reserve( 5688 );
    pi_3.reserve( 5688 );
    
    string filename_1 = directory3D + "Data/T2 Packing Functions/Molecule_Centres/Synthesised Crystals/delta.txt";
    
    for (int counter = 0; counter < 5688; ++counter)
    {
        string filename_2 = directory3D + "Data/T2 Packing Functions/Molecule_Centres/Dataset/" + to_string( counter + 1 ) + ".txt";
        
        int difference_in_length;
        double max_diff_pi_1, max_diff_pi_2, max_diff_pi_3;
        
        Comparing_Entries( filename_1, filename_2, max_diff_pi_1, max_diff_pi_2, max_diff_pi_3, difference_in_length );
        
        length_diff.push_back( difference_in_length );
        pi_1.push_back( max_diff_pi_1 );
        pi_2.push_back( max_diff_pi_2 );
        pi_3.push_back( max_diff_pi_3 );
    }
    
    ofstream ofs( directory3D + "Data/T2 Packing Functions/Molecule_Centres/Analysis/Raw Data/delta.txt" );
     
     for (int counter_2 = 0; counter_2 < 5688; ++counter_2)
     {
         ofs << "ID" <<  counter_2 + 1 << " " << pi_1[counter_2] << " " << pi_2[counter_2] << " " << pi_3[counter_2] << " " << length_diff[counter_2] << endl;
     }
     
     ofs.close();
}
