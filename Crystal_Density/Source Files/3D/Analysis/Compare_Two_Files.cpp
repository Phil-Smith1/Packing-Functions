#include <iostream>

#include "Comparing_Entries.h"

void Compare_Two_Files ( string const& filename_1, string const& filename_2 )
{
    int difference_in_length;
    double max_diff_pi_1, max_diff_pi_2, max_diff_pi_3;
    
    Comparing_Entries( filename_1, filename_2, max_diff_pi_1, max_diff_pi_2, max_diff_pi_3, difference_in_length );
    
    cout << difference_in_length << endl;
    cout << max_diff_pi_1 << endl;
    cout << max_diff_pi_2 << endl;
    cout << max_diff_pi_3 << endl;
    cout << max_diff_pi_1 + max_diff_pi_2 + max_diff_pi_3 << endl;
}
