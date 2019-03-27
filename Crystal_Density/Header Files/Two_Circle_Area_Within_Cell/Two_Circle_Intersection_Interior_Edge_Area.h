#pragma once

#include "Make_Cell.h"
#include "Two_Circle_Intersection_Area_Within_Cell.h"
#include "Cell_2Circles.h"

double Two_Circle_Intersection_Interior_Edge_Area ( Circle const& c1, Circle const& c2, Edge const& e, Cell const& cell_1, Cell const& cell_2 );

double Two_Circle_Intersection_Interior_Edge_Area ( Cell_2Circles const& c2c, Edge const& e );
