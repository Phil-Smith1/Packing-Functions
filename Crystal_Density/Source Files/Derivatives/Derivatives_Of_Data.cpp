#include <vector>

#include "Derivatives_At_Pt.h"
#include "Discontinuity.h"

using namespace std;

void Derivatives_Of_Data ( vector<double>const& x, vector<double> const& y, vector<pair<double, double>>& first_deriv, vector<pair<double, double>>& second_deriv, vector<pair<double, double>>& disc_pts )
{
    first_deriv.reserve( (int)x.size() - 2 );
    second_deriv.reserve( (int)x.size() - 2 );
    
    bool discontinuity = false, start_pt = true;
    int discontinuity_counter = 0, start_pt_counter = 0;
    double trend = 0;
    
    for (int counter = 0; counter < x.size() - 2; ++counter)
    {
        double first_der, second_der;
        
        Derivatives_At_Pt( x[counter], x[counter + 2], y[counter], y[counter + 1], y[counter + 2], first_der, second_der );
        
        first_deriv.push_back( pair<double, double>( x[counter + 1], first_der ) );
        
        if (!start_pt && !discontinuity) discontinuity = Discontinuity( second_deriv.back().second, trend, second_der );
        
        if (!discontinuity) second_deriv.push_back( pair<double, double>( x[counter + 1], second_der ) );
        
        if (discontinuity && discontinuity_counter == 0) disc_pts.push_back( pair<double, double>( x[counter + 1], y[counter + 1] ) );
        
        if (start_pt && start_pt_counter == 0) ++start_pt_counter;
        
        else if (start_pt && start_pt_counter == 1)
        {
            start_pt = false;
            start_pt_counter = 0;
        }
        
        if (discontinuity && discontinuity_counter == 0) ++discontinuity_counter;
        
        else if (discontinuity && discontinuity_counter == 1)
        {
            discontinuity = false;
            discontinuity_counter = 0;
            start_pt = true;
        }
        
        if (second_deriv.size() > 1) trend = second_deriv[(int)second_deriv.size() - 1].second - second_deriv[(int)second_deriv.size() - 2].second;
        
        if (trend < 0.1 && trend >=0) trend = 0.1;
        
        else if (trend > -0.1 && trend <=0) trend = -0.1;
    }
}
