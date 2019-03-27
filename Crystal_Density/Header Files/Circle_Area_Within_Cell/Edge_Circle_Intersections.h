#pragma once

#include "Cell.h"
#include "Norm.h"
#include "Line_Circle_Intersections.h"

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

void Edge_Circle_Intersections ( Circle const& circle, Edge& e );

