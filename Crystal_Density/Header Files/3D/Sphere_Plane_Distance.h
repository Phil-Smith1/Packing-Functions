#pragma once

#include "Norm3D.h"
#include "Sphere.h"

typedef K::Plane_3 Pl3;

double Sphere_Plane_Distance ( Sphere const& s, Pl3 const& p );
