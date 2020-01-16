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
    
    bool T2, experimental_T2, pts_at_vertices, interior_points, auto_max_radius, parallelepiped;
    int sample_rate, deformation_type, iterations;
    double max_radius;
    string type_of_experiment, experimental_T2_label, function_type, lattice_type;
    vector<double> scale;
    vector<P3> parallelepiped_vectors, interior_pts;
    
    Input3D ( bool t, string const& t_o_e, bool e_T2, string const& e_T2_l, string const& f_t, string const& l_t, vector<P3>const& p_v, bool p_a_v, vector<double>const& s, bool int_p, vector<P3> i_p, int d_t, int i, int s_r, bool a_m_r, double m_r, bool par );
    
    Input3D();
    ~Input3D();
};
