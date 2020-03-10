#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/convex_hull_2.h>

#include <thread>

#include "B_Poly_2D.h"

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;
typedef K::Vector_2 V2;
typedef K::Triangle_2 Tri;
typedef K::Line_2 L2;
typedef K::Segment_2 S2;

typedef Triangulation_2<K> Triangulation_2D;
typedef Triangulation_2D::Vertex_circulator Vertex_circulator;
typedef Triangulation_2D::Finite_faces_iterator faces_iterator;

typedef Polygon::Vertex_iterator vertex_iterator_2D;

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

typedef K::Intersect_2 I2;

typedef Polygon::Edge_const_iterator edge_iterator;

void Compute_Brillouin_Zones_2D ( multimap<double, P2>const& pts, int zone_limit, P2 const& centre, vector<vector<Tri>>& zones_of_tris, vector<double>& max_radii, vector<double>& cell_volume );
