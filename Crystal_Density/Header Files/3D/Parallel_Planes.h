#pragma once

#include "Angle_Between_Vectors3D.h"

typedef K::Plane_3 Pl3;

#ifndef Pi
#define Pi
const double PI = 3.14159265359;
#endif

bool Parallel_Planes ( Pl3 const& p1, Pl3 const& p2 );
