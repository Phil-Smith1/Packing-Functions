#pragma once

#include <string>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 P3;

class Input3D
{
    public:
    
    bool interior_points;
    int sample_rate, deformation_type, iterations;
    double max_radius;
    string function_type, lattice_type;
    vector<double> scale;
    vector<P3> pts, interior_pts;
    
    Input3D ( string const& f_t, string const& l_t, vector<P3>const& p, vector<double>const& s, bool int_p, vector<P3> i_p, int d_t, int i, int s_r );
    
    Input3D();
    ~Input3D();
};
