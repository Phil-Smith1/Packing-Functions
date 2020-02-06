#pragma once

#include "Norm3D.h"

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

double Angle_Between_Vectors ( P3 const& p1, P3 const& p2 );
