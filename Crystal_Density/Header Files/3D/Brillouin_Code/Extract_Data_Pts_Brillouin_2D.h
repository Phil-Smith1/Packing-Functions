#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangle_2.h>

#include <thread>
#include <fstream>

#include "Input3D.h"

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;
typedef K::Vector_2 V2;
typedef K::Triangle_2 Tri;
typedef K::Line_2 L2;
typedef K::Segment_2 S2;

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

typedef K::Intersect_2 I2;

#include "Disk_Triangle_Intersection.h"

void Extract_Data_Pts_Brillouin_2D ( string const& directory3D, Input3D& input, int index, vector<P2> const& centres, vector<vector<vector<Tri>>> triangles, vector<double>const& cell_volume, vector<vector<double>>const& max_radii );
