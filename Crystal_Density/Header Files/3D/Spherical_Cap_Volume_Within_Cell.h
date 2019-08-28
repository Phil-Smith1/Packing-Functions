#pragma once

#include "Cell3D.h"
#include "Cap_Volume_By_Exclusion.h"

double Spherical_Cap_Volume_Within_Cell ( Cell3D const& cell, Sphere const& s, Pl3 const& p );
