#include "General_Spherical_Wedge.h"

double Cone_Parallel_Planes ( Sphere const& s, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3 )
{
    if (p2.oriented_side( p1.point() ) == ON_ORIENTED_BOUNDARY)
    {
        P3 pt = P3( 0, 0, 0 ) + p1.orthogonal_vector();
        
        if (p2.oriented_side( pt ) == ON_NEGATIVE_SIDE) return 0;
        
        else return General_Spherical_Wedge( s, p1, p3 );
    }
    
    else if (p2.oriented_side( p1.point() ) == ON_NEGATIVE_SIDE && p1.oriented_side( p2.point() ) == ON_NEGATIVE_SIDE) return 0;
    
    else if (p2.oriented_side( p1.point() ) == ON_NEGATIVE_SIDE) return General_Spherical_Wedge( s, p2, p3 );
    
    else if (p1.oriented_side( p2.point() ) == ON_NEGATIVE_SIDE) return General_Spherical_Wedge( s, p1, p3 );
    
    else return Spherical_Cap( s, p1 ) + Spherical_Cap( s, p2 ) - s.vol - Spherical_Cap( s, p3.opposite() ) + General_Spherical_Wedge( s, p1.opposite(), p3.opposite() ) + General_Spherical_Wedge( s, p2.opposite(), p3.opposite() );
}
