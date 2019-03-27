#pragma once

#include "Non_Trivial_Three_Circle_Intersection_Area.h"
#include "Non_Trivial_Three_Circle_Intersection_Pts.h"
#include "Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge.h"
#include "Cell_3Circles.h"

double Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( Circle const& c1, Circle const& c2, Circle const& c3, Edge const& e1, Edge const& e2, Edge const& e3, Cell const& cell );

double Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( Cell_3Circles const& c3c, Edge const& e1, Edge const& e2, Edge const& e3 );
