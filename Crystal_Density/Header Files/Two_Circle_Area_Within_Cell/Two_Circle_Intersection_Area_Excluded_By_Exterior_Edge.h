#pragma once

#include "Cell_2Circles.h"
#include "Triangle_Area.h"
#include "Area_Excluded_By_Exterior_Edge.h"

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

double Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge ( Cell_2Circles const& c2c, Edge const& e1, Edge const& e2 );
