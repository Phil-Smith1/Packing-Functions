#pragma once

#include "Cell.h"

// Returns true if point is within or on boundary of convex hull, else returns false.

bool Pt_Within_Convex_Hull ( Cell const& cell, P2 const& p );
