#pragma once

#include "Angle_Between_Vectors3D.h"

typedef K::Plane_3 Pl3;

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

bool Parallel_Planes ( Pl3 const& p1, Pl3 const& p2 );
