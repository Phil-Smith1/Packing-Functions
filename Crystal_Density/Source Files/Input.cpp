#include "Input.h"

Input::Input ( string const& f_t, string const& l_t, vector<P2>const& p, vector<double>const& s, bool int_p, vector<P2> i_p, int d_t, int i, int s_r )
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

Input::Input(){}
Input::~Input(){}
