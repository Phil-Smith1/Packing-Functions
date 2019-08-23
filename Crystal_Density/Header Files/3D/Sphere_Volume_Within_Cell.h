#pragma once

#include "Cell3D.h"
#include "Sphere_Volume_By_Exclusion.h"

double Sphere_Volume_Within_Cell ( Cell3D const& cell, Sphere const& s );
