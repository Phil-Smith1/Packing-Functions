#pragma once

#include "Intersection_Of_Two_Circles.h"
#include "Segment_Area.h"

typedef K::Line_2 L2;

double Two_Circle_Intersection_Area ( Circle const& c1, Circle const& c2 );

double Two_Circle_Intersection_Area ( Circle const& c1, Circle const& c2, P2& i1, P2& i2, bool& intersection );
