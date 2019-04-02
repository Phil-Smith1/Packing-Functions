#include "Input.h"

#ifndef Pi
#define Pi
const double PI = 3.14159265359;
#endif

bool Deformation ( Input& input, int counter )
{
    if (input.deformation_type == 0) return false;
    
    else if (input.deformation_type == 1)
    {
        input.pts[0] = P2( 0, 1 );
        
        double angle = 0.5 * PI - counter * PI / (double)(6 * (input.iterations - 1));
        
        if (counter != 0)
        {
            input.pts[0] = P2( cos( angle ), sin( angle ) );
            input.pts[1] = P2( 1, 0 );
        }
    }
    
    else if (input.deformation_type == 2)
    {
        double angle = counter * PI / (double)(input.iterations - 1);
        
        input.interior_pts.clear();
        
        input.interior_pts.push_back( P2( 0.5 + 0.25 * cos( angle ), 0.5 + 0.25 * sin( angle ) ) );
    }
    
    else if (input.deformation_type == 3)
    {
        double param = counter * 0.9 / (double)(input.iterations - 1);
        
        input.interior_pts.clear();
        
        input.interior_pts.push_back( P2( 0.05 + param, 0.05 + param ) );
    }
    
    else if (input.deformation_type == 4)
    {
        double param = counter * 0.9 / (double)(input.iterations - 1);
        
        input.interior_pts.clear();
        
        input.interior_pts.push_back( P2( 0.05 + param, 0.95 - param ) );
    }
    
    cout << "Iteration: " << counter << "." << endl;
    
    return true;
}
