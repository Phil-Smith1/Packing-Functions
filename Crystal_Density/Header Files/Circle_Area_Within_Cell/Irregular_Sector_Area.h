#pragma once

#include "Edge.h"
#include "Same_Side.h"
#include "Triangle_Area.h"
#include "Segment_Area.h"

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

double Irregular_Sector_Area ( Circle const& circle, Edge const& e1, Edge const& e2 );
