#pragma once

#include <string>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;

class Input
{
    public:
    
    bool interior_points;
    int sample_rate, deformation_type, iterations;
    string function_type, lattice_type;
    vector<double> scale;
    vector<P2> pts, interior_pts;
    
    Input ( string const& f_t, string const& l_t, vector<P2>const& p, vector<double>const& s, bool int_p, vector<P2> i_p, int d_t, int i, int s_r );
    
    Input();
    ~Input();
};
