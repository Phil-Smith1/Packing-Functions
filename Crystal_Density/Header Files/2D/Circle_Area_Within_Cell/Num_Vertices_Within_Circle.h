#pragma once

#include "Norm.h"
#include "Cell_Circle.h"

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

int Num_Vertices_Within_Circle ( Cell const& cell, Circle const& circle );

void Num_Vertices_Within_Circle ( Cell_Circle& cc );
