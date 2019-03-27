#pragma once

#include "Cell_3Circles.h"
#include "Two_Circle_Intersection_Area_Within_Cell.h"
#include "Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge.h"
#include "Three_Circle_Intersection_Irregular_Sector_Area.h"
#include "Three_Circle_Intersection_Interior_Edge_Area.h"
#include "Three_Circle_Intersection_Concave_Cone_Area.h"

double Non_Trivial_Three_Circle_Intersection_Area_Within_Cell ( Cell& cell, Circle const& c1, Circle const& c2, Circle const& c3 );

double Non_Trivial_Three_Circle_Intersection_Area_Within_Cell ( Cell_3Circles& c3c );
