#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;

#ifndef Pi
#define Pi
const double PI = 3.14159265359;
#endif

bool Deformation ( int deformation_type, int iterations, int counter, P2& p2, P2& p3, P2 const& p4, vector<P2>& interior_pts )
{
    if (deformation_type == 0) return false;
    
    else if (deformation_type == 1)
    {
        double angle = 0.5 * PI - counter * PI / (double)(6 * (iterations - 1));
        
        if (counter != 0)
        {
            p2 = P2( cos( angle ), sin( angle ) );
            p3 = P2( p2.x() + p4.x(), p2.y() + p4.y() );
        }
    }
    
    else if (deformation_type == 2)
    {
        double angle = counter * PI / (double)(iterations - 1);
        
        interior_pts.clear();
        
        interior_pts.push_back( P2( 0.5 + 0.25 * cos( angle ), 0.5 + 0.25 * sin( angle ) ) );
    }
    
    else if (deformation_type == 3)
    {
        double param = counter * 0.9 / (double)(iterations - 1);
        
        interior_pts.clear();
        
        interior_pts.push_back( P2( 0.05 + param, 0.05 + param ) );
    }
    
    else if (deformation_type == 4)
    {
        double param = counter * 0.9 / (double)(iterations - 1);
        
        interior_pts.clear();
        
        interior_pts.push_back( P2( 0.05 + param, 0.95 - param ) );
    }
    
    cout << "Iteration: " << counter << "." << endl;
    
    return true;
}
