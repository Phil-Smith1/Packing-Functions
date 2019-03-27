#pragma once

#include "Same_Side.h"
#include "Concave_Cone_Area.h"
#include "Cell_2Circles.h"

double Two_Circle_Intersection_Concave_Cone_Area ( Circle const& c1, Circle const& c2, Edge const& e1, Edge const& e2, Edge const& e3, Edge const& e4 );

double Two_Circle_Intersection_Concave_Cone_Area ( Cell_2Circles const& c2c, Edge const& e1, Edge const& e2, Edge const& e3, Edge const& e4 );
