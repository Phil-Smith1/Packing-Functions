#pragma once

#include "Circle.h"
#include "Angle_Between_Vectors3D.h"

typedef K::Plane_3 Pl3;

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

bool Intersection_Of_Plane_And_Circle ( Pl3 const& p, Circle3D const& c );
