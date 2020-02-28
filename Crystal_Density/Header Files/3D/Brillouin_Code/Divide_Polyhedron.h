#pragma once

#include "Max_Distance_To_Polyhedron.h"
#include "Removing_Polyhedrons.h"
#include "Max_Radius_Of_Space.h"
#include "Plane_Intersect_Polyhedron.h"

#include <mutex>

#include <CGAL/convex_hull_3.h>

typedef Exact_Kernel::Segment_3 S3_E;
typedef Exact_Kernel::Intersect_3 I3;

typedef K::Segment_3 S3;
typedef K::Intersect_3 I3_I;

typedef Polyhedron::Halfedge_iterator halfedge_iterator;

typedef Polyhedron_I::Halfedge_iterator halfedge_iterator_i;

void Divide_Polyhedron ( P3_E const centre, multimap<double, P3_E>const pts, Polyhedron poly, vector<B_Poly>& final_polys, int zone_limit );

void Divide_Polyhedron_I ( P3 const centre, multimap<double, P3>const pts, Polyhedron_I poly, int starting_zone, vector<B_Poly_I>& final_polys, int zone_limit );
