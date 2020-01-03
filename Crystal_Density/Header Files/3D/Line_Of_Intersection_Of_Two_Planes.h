#pragma once

#include "Norm3D.h"

typedef K::Line_3 L3;
typedef K::Plane_3 Pl3;

L3 Line_Of_Intersection_Of_Two_Planes ( Pl3 const& p1, Pl3 const& p2 );
