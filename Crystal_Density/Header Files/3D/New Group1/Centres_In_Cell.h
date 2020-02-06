#pragma once

#include "Distance_To_Cell.h"

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

bool Centres_In_Cell ( Cell3D const& cell );
