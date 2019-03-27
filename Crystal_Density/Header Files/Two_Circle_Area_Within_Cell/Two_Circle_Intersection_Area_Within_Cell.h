#pragma once

#include "Circle_Area_Within_Cell.h"
#include "Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge.h"
#include "Two_Circle_Intersection_Irregular_Sector_Area.h"
#include "Two_Circle_Intersection_Interior_Edge_Area.h"
#include "Two_Circle_Intersection_Concave_Cone_Area.h"

double Two_Circle_Intersection_Area_Within_Cell ( Cell& cell, Circle const& c1, Circle const& c2 );

double Two_Circle_Intersection_Area_Within_Cell ( Cell_2Circles& c2c );
