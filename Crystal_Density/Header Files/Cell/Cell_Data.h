#pragma once

#include <string>

#include "Make_Cell.h"
#include "Interior_Pts.h"

void Cell_Data ( string const& lattice_type, P2 const& pt1, P2 const& pt2, P2 const& pt3, P2 const& pt4, bool interior_points, vector<P2>const& interior_pts, Cell& cell );
