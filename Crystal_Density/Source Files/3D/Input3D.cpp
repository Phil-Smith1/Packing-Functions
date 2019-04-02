#include "Input3D.h"

Input3D::Input3D ( string const& f_t, string const& l_t, vector<P3>const& p, vector<double>const& s, bool int_p, vector<P3> i_p, int d_t, int i, int s_r )
{
    function_type = f_t;
    lattice_type = l_t;
    pts = p;
    scale = s;
    interior_points = int_p;
    interior_pts = i_p;
    deformation_type = d_t;
    iterations = i;
    sample_rate = s_r;
}


Input3D::Input3D(){}
Input3D::~Input3D(){}
