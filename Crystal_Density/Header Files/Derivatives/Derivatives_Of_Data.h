#include <vector>

#include "Derivatives_At_Pt.h"
#include "Discontinuity.h"

using namespace std;

void Derivatives_Of_Data ( vector<double>const& x, vector<double> const& y, vector<pair<double, double>>& first_deriv, vector<pair<double, double>>& second_deriv, vector<pair<double, double>>& disc_pts );
