#include <iostream>

#include "Comparing_Entries.h"

void Dataset_Dataset_Analysis ( string const& directory3D )
{
    vector<int> diff_lengths;
    vector<double> pi_1, pi_2, pi_3;

    ofstream ofs_1( directory3D + "Data/T2 Packing Functions/Pi_1.txt" );
    ofstream ofs_2( directory3D + "Data/T2 Packing Functions/Pi_2.txt" );
    ofstream ofs_3( directory3D + "Data/T2 Packing Functions/Pi_3.txt" );
    ofstream ofs_4( directory3D + "Data/T2 Packing Functions/Diff_Lengths.txt" );

    for (int counter_1 = 0; counter_1 < 5688; ++counter_1)
    {
        cout << "Comparison: " << counter_1 << endl;
        
        pi_1.clear();
        pi_2.clear();
        pi_3.clear();
        diff_lengths.clear();
        
        string filename_1 = directory3D + "Data/T2 Packing Functions/Dataset/" + to_string( counter_1 + 1 ) + ".txt";

        for (int counter_2 = counter_1; counter_2 < 5688; ++counter_2)
        {
            string filename_2 = directory3D + "Data/T2 Packing Functions/Dataset/" + to_string( counter_2 + 1 ) + ".txt";

            int difference_in_length;
            double max_diff_pi_1, max_diff_pi_2, max_diff_pi_3;

            Comparing_Entries( filename_1, filename_2, max_diff_pi_1, max_diff_pi_2, max_diff_pi_3, difference_in_length );

            pi_1.push_back( max_diff_pi_1 );
            pi_2.push_back( max_diff_pi_2 );
            pi_3.push_back( max_diff_pi_3 );
            diff_lengths.push_back( difference_in_length );
        }

        ofs_1 << pi_1[0];
        ofs_2 << pi_2[0];
        ofs_3 << pi_3[0];
        ofs_4 << diff_lengths[0];

        for (int counter_2 = 1; counter_2 < 5688 - counter_1; ++counter_2)
        {
            ofs_1 << " " << pi_1[counter_2];
            ofs_2 << " " << pi_2[counter_2];
            ofs_3 << " " << pi_3[counter_2];
            ofs_4 << " " << diff_lengths[counter_2];
        }

        ofs_1 << endl;
        ofs_2 << endl;
        ofs_3 << endl;
        ofs_4 << endl;
    }

    ofs_1.close();
    ofs_2.close();
    ofs_3.close();
    ofs_4.close();
}
