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

#include "Irregular_Sector_Area.h"
#include "Edge_Circle_Intersections.h"

double Sec_Area ( Circle const& c, P2 const& vertex, Edge const& e1, Edge const& e2, double volume1, double volume2 );

double Intersect_Area ( Circle const& c, vector<Edge>& edges, vector<P2> const& vertices );

double Disk_Triangle_Intersection ( Circle const& c, Tri const& t );
