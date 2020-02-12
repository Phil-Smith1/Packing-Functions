#include "Input3D.h"

Input3D::Input3D ( bool t, string const& t_o_e, bool e_T2, string const& e_T2_l, string const& f_t, string const& l_t, vector<P3>const& p_v, bool p_a_v, vector<double>const& s, bool int_p, vector<P3> i_p, int d_t, int i, int s_r, bool a_m_r, double m_r, bool par, int p, int z_l )
{
    T2 = t;
    type_of_experiment = t_o_e;
    experimental_T2 = e_T2;
    experimental_T2_label = e_T2_l;
    function_type = f_t;
    lattice_type = l_t;
    parallelepiped_vectors = p_v;
    pts_at_vertices = p_a_v;
    scale = s;
    interior_points = int_p;
    interior_pts = i_p;
    deformation_type = d_t;
    iterations = i;
    sample_rate = s_r;
    auto_max_radius = a_m_r;
    max_radius = m_r;
    parallelepiped = par;
    perim = p;
    zone_limit = z_l;
}


Input3D::Input3D(){}
Input3D::~Input3D(){}
