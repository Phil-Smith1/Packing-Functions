#pragma once

#include "Non_Trivial_Three_Circle_Intersection_Area.h"
#include "Non_Trivial_Four_Circle_Intersection_Pts.h"
#include "Non_Trivial_Four_Circle_Intersection_Area.h"
#include "Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge.h"
#include "Cell_4Circles.h"

double Four_Circle_Intersection_Area_Excluded_By_Exterior_Edge ( Circle const& c1, Circle const& c2, Circle const& c3, Circle const& c4, Edge const& e1, Edge const& e2, Edge const& e3, Edge const& e4, Cell const& cell );

double Four_Circle_Intersection_Area_Excluded_By_Exterior_Edge ( Cell_4Circles const& c4c, Edge const& e1, Edge const& e2, Edge const& e3, Edge const& e4 );
