#include <fstream>
#include <sstream>

#include "Derivatives_Of_Data.h"

void Derivatives3D ( string const& directory, string const& filename )
{
    ifstream ifs( directory + filename );
    ofstream ofs_1( directory + "Data/First_Derivs.txt" );
    ofstream ofs_2( directory + "Data/F_1_Second_Derivs.txt" );
    ofstream ofs_3( directory + "Data/Derivative_Critical_Pts.txt" );
    
    string line_data;
    stringstream stream;
    vector<double> r, f1, f2, f3;
    
    while (getline( ifs, line_data ))
    {
        double rad, fn1, fn2, fn3;
        stringstream stream;
        
        stream << line_data;
        stream >> rad >> fn1 >> fn2 >> fn3;
        
        r.push_back( rad );
        f1.push_back( fn1 );
        f2.push_back( fn2 );
        f3.push_back( fn3 );
    }
    
    ifs.close();
    
    vector<pair<double, double>> first_deriv_f1;
    vector<pair<double, double>> second_deriv_f1;
    vector<pair<double, double>> disc_pts_f1;
    vector<pair<double, double>> first_deriv_f2;
    vector<pair<double, double>> second_deriv_f2;
    vector<pair<double, double>> disc_pts_f2;
    vector<pair<double, double>> first_deriv_f3;
    vector<pair<double, double>> second_deriv_f3;
    vector<pair<double, double>> disc_pts_f3;
    
    Derivatives_Of_Data( r, f1, first_deriv_f1, second_deriv_f1, disc_pts_f1 );
    Derivatives_Of_Data( r, f2, first_deriv_f2, second_deriv_f2, disc_pts_f2 );
    Derivatives_Of_Data( r, f3, first_deriv_f3, second_deriv_f3, disc_pts_f3 );
    
    for (int counter = 0; counter < first_deriv_f1.size(); ++counter)
    {
        ofs_1 << first_deriv_f1[counter].first << " " << first_deriv_f1[counter].second << endl;
    }
    
    for (int counter = 0; counter < second_deriv_f1.size(); ++counter)
    {
        if (second_deriv_f1[counter].first < 0) ofs_2 << endl;
        
        else ofs_2 << second_deriv_f1[counter].first << " " << second_deriv_f1[counter].second << endl;
    }
    
    for (int counter = 0; counter < disc_pts_f1.size(); ++counter)
    {
        ofs_3 << disc_pts_f1[counter].first << " " << disc_pts_f1[counter].second << " 1" << endl;
        //ofs_3 << disc_pts_f2[counter].first << " " << disc_pts_f2[counter].second << " 2" << endl;
    }
    
    ofs_1.close();
    ofs_2.close();
    ofs_3.close();
}
