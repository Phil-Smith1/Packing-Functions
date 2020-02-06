#include "B_Poly.h"

using namespace std;

typedef Exact_Kernel::Point_3 P3_E;

double Max_Radius_Of_Space ( P3_E const& centre, vector<B_Poly>& polys )
{
    double max_radius = 0;
    
    for (int counter = 0; counter < polys.size(); ++counter)
    {
        if (polys[counter].dist > max_radius) max_radius = polys[counter].dist;
    }
    
    return max_radius;
}
