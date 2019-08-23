#pragma once

#include "Angle_Between_Vectors3D.h"

typedef K::Line_3 L3;

#ifndef Pi
#define Pi
const double PI = 3.14159265359;
#endif

bool Parallel_Lines ( L3 const& l1, L3 const& l2 );
