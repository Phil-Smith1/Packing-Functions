#include <sstream>
#include <fstream>

#include "Derivatives_Of_Data.h"

#include <iostream>

void Derivatives ( string const& directory, string const& filename )
{
    ifstream ifs( directory + filename );
    ofstream ofs_1( directory + "Data/First_Derivs.txt" );
    ofstream ofs_2( directory + "Data/Second_Derivs.txt" );
    ofstream ofs_3( directory + "Data/Derivative_Critical_Pts.txt" );
    
    string line_data;
    stringstream stream;
    vector<double> r, f1, f2, f3, f4;
    
    while (getline( ifs, line_data ))
    {
        double rad, fn1, fn2, fn3, fn4;
        stringstream stream;
        
        stream << line_data;
        stream >> rad >> fn1 >> fn2 >> fn3 >> fn4;
        
        r.push_back( rad );
        f1.push_back( fn1 );
        f2.push_back( fn2 );
        f3.push_back( fn3 );
        f4.push_back( fn4 );
    }
    
    ifs.close();
    
    vector<pair<double, double>> first_deriv_f1;
    vector<pair<double, double>> first_deriv_f2;
    vector<pair<double, double>> first_deriv_f3;
    vector<pair<double, double>> first_deriv_f4;
    vector<pair<double, double>> second_deriv_f1;
    vector<pair<double, double>> second_deriv_f2;
    vector<pair<double, double>> second_deriv_f3;
    vector<pair<double, double>> second_deriv_f4;
    vector<pair<double, double>> disc_pts;
    
    Derivatives_Of_Data( r, f1, first_deriv_f1, second_deriv_f1, disc_pts );
    Derivatives_Of_Data( r, f2, first_deriv_f2, second_deriv_f2, disc_pts );
    Derivatives_Of_Data( r, f3, first_deriv_f3, second_deriv_f3, disc_pts );
    Derivatives_Of_Data( r, f4, first_deriv_f4, second_deriv_f4, disc_pts );
    
    for (int counter = 0; counter < first_deriv_f1.size(); ++counter)
    {
        ofs_1 << first_deriv_f1[counter].first << " " << first_deriv_f1[counter].second << " " << first_deriv_f2[counter].second << " " << first_deriv_f3[counter].second << " " << first_deriv_f4[counter].second << " " << endl;
    }
    
    for (int counter = 0; counter < second_deriv_f1.size(); ++counter)
    {
        ofs_2 << second_deriv_f1[counter].first << " " << second_deriv_f1[counter].second << " " << second_deriv_f2[counter].first << " " << second_deriv_f2[counter].second << " " << second_deriv_f3[counter].first << " " << second_deriv_f3[counter].second << " " << second_deriv_f4[counter].first << " " << second_deriv_f4[counter].second << endl;
    }
    
    for (int counter = 0; counter < disc_pts.size(); ++counter)
    {
        ofs_3 << disc_pts[counter].first << " " << disc_pts[counter].second << endl;
    }
    
    ofs_1.close();
    ofs_2.close();
    ofs_3.close();
}
