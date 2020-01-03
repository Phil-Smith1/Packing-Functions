#pragma once

#include "Cell3D.h"

#ifndef Pi
#define Pi
const double PI = 3.14159265359;
#endif

void Cell_Volume ( Cell3D& cell );

double Cell_Volume ( vector<pair<string, double>>const& cell_shape );
