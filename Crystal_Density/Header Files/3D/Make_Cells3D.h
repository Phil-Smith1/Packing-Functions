#pragma once

#include "Make_Cell3D.h"
#include "Norm3D.h"

#ifndef Pi
#define Pi
const double PI = 3.14159265359;
#endif

void Make_Cells3D ( Input3D& input3D, vector<Cell3D>& cells );
