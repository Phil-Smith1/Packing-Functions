#pragma once

#include "Non_Trivial_Three_Circle_Intersection_Area.h"
#include "Non_Trivial_Three_Circle_Intersection_Pts.h"
#include "Two_Circle_Intersection_Irregular_Sector_Area.h"
#include "Cell_3Circles.h"

double Three_Circle_Intersection_Irregular_Sector_Area ( Circle const& c1, Circle const& c2, Circle const& c3, Edge const& e1, Edge const& e2, Edge const& e3, Edge const& e4, Edge const& e5, Edge const& e6 );

double Three_Circle_Intersection_Irregular_Sector_Area ( Cell_3Circles const& c3c, Edge const& e1, Edge const& e2, Edge const& e3, Edge const& e4, Edge const& e5, Edge const& e6 );
