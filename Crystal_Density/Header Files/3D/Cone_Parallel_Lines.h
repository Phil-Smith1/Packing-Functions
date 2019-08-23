#pragma once

#include "General_Spherical_Wedge.h"

double Cone_Shared_Line_Orthogonal_Planes ( Sphere const& s, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3, P3 const& pt, P3 const& i1, P3 const& i2 );

double Cone_Shared_Line ( Sphere const& s, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3, P3 const& pt, P3 const& i1, P3 const& i2 );

double Cone_Parallel_Lines ( Sphere const& s, L3 const& l3, L3 const& l2, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3 );
