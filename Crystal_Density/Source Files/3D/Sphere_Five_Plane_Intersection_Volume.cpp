#include "Sphere_Four_Plane_Intersection_Volume.h"

double Parallel_Planes_Case5 ( Sphere const& s, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3, Pl3 const& p4, Pl3 const& p5 )
{
    if (p2.oriented_side( p1.point() ) == ON_ORIENTED_BOUNDARY)
    {
        P3 pt = P3( 0, 0, 0 ) + p1.orthogonal_vector();
        
        if (p2.oriented_side( pt ) == ON_NEGATIVE_SIDE) return 0;
        
        else return Sphere_Four_Plane_Intersection_Volume( s, p1, p3, p4, p5 );
    }
    
    else if (p2.oriented_side( p1.point() ) == ON_NEGATIVE_SIDE && p1.oriented_side( p2.point() ) == ON_NEGATIVE_SIDE) return 0;
    
    else if (p2.oriented_side( p1.point() ) == ON_NEGATIVE_SIDE) return Sphere_Four_Plane_Intersection_Volume( s, p2, p3, p4, p5 );
    
    else if (p1.oriented_side( p2.point() ) == ON_NEGATIVE_SIDE) return Sphere_Four_Plane_Intersection_Volume( s, p1, p3, p4, p5 );
    
    else return Spherical_Cap( s, p1 ) + Spherical_Cap( s, p2 ) + Spherical_Cap( s, p3 ) + Spherical_Cap( s, p4 ) + Spherical_Cap( s, p5 ) - General_Spherical_Wedge( s, p1, p3 ) - General_Spherical_Wedge( s, p1, p4 ) - General_Spherical_Wedge( s, p1, p5 ) - General_Spherical_Wedge( s, p2, p3 ) - General_Spherical_Wedge( s, p2, p4 ) - General_Spherical_Wedge( s, p2, p5 ) - General_Spherical_Wedge( s, p3, p4 ) - General_Spherical_Wedge( s, p3, p5 ) - General_Spherical_Wedge( s, p4, p5 ) + General_Spherical_Cone( s, p1, p3, p4 ) + General_Spherical_Cone( s, p1, p3, p5 ) + General_Spherical_Cone( s, p1, p4, p5 ) + General_Spherical_Cone( s, p2, p3, p4 ) + General_Spherical_Cone( s, p2, p3, p5 ) + General_Spherical_Cone( s, p2, p4, p5 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p3, p4, p5 ) - Sphere_Four_Plane_Intersection_Volume( s, p2, p3, p4, p5 );
}

double Sphere_Five_Plane_Intersection_Volume ( Sphere const& s, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3, Pl3 const& p4, Pl3 const& p5 )
{
    if (Parallel_Planes( p1, p2 )) return Parallel_Planes_Case5( s, p1, p2, p3, p4, p5 );
    else if (Parallel_Planes( p1, p3 )) return Parallel_Planes_Case5( s, p1, p3, p2, p4, p5 );
    else if (Parallel_Planes( p1, p4 )) return Parallel_Planes_Case5( s, p1, p4, p2, p3, p5 );
    else if (Parallel_Planes( p1, p5 )) return Parallel_Planes_Case5( s, p1, p5, p2, p3, p4 );
    else if (Parallel_Planes( p2, p3 )) return Parallel_Planes_Case5( s, p2, p3, p1, p4, p5 );
    else if (Parallel_Planes( p2, p4 )) return Parallel_Planes_Case5( s, p2, p4, p1, p3, p5 );
    else if (Parallel_Planes( p2, p5 )) return Parallel_Planes_Case5( s, p2, p5, p1, p3, p4 );
    else if (Parallel_Planes( p3, p4 )) return Parallel_Planes_Case5( s, p3, p4, p1, p2, p5 );
    else if (Parallel_Planes( p3, p5 )) return Parallel_Planes_Case5( s, p3, p5, p1, p2, p4 );
    else if (Parallel_Planes( p4, p5 )) return Parallel_Planes_Case5( s, p4, p5, p1, p2, p3 );
        
    else return 0;
}
