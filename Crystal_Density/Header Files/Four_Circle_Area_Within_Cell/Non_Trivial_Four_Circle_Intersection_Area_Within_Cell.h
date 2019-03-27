#pragma once

#include "Three_Circle_Intersection_Area_Within_Cell.h"
#include "Non_Trivial_Four_Circle_Intersection_Area.h"
#include "Four_Circle_Intersection_Area_Excluded_By_Exterior_Edge.h"

//double Non_Trivial_Four_Circle_Intersection_Area_Within_Cell ( Cell& cell, Circle const& c1, Circle const& c2, Circle const& c3, Circle const& c4 );

double Non_Trivial_Four_Circle_Intersection_Area_Within_Cell ( Cell_4Circles& c4c );
