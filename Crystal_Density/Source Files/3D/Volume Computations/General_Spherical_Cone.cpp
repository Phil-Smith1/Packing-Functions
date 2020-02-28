#include "Cone_Parallel_Planes.h"
#include "Parallel_Lines.h"
#include "Cone_Parallel_Lines.h"
#include "Intersection_Of_Two_Lines3D.h"
#include "General_Spherical_Cone_Exterior_Vertex.h"
#include "Tetrahedron_Volume.h"

double General_Spherical_Cone ( Sphere const& s, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3 )
{
    double plane_dist_1 = sqrt( squared_distance( s.c, p1 ) );
    
    if (plane_dist_1 > s.r - tiny_num)
    {
        if (p1.oriented_side( s.c ) == ON_NEGATIVE_SIDE) return 0;
        
        else return General_Spherical_Wedge( s, p2, p3 );
    }
    
    double plane_dist_2 = sqrt( squared_distance( s.c, p2 ) );
    
    if (plane_dist_2 > s.r - tiny_num)
    {
        if (p2.oriented_side( s.c ) == ON_NEGATIVE_SIDE) return 0;
        
        else return General_Spherical_Wedge( s, p1, p3 );
    }
    
    double plane_dist_3 = sqrt( squared_distance( s.c, p3 ) );
    
    if (plane_dist_3 > s.r - tiny_num)
    {
        if (p3.oriented_side( s.c ) == ON_NEGATIVE_SIDE) return 0;
        
        else return General_Spherical_Wedge( s, p1, p2 );
    }
    
    if (Parallel_Planes( p1, p2 )) return Cone_Parallel_Planes( s, p1, p2, p3 );
    else if (Parallel_Planes( p1, p3 )) return Cone_Parallel_Planes( s, p1, p3, p2 );
    else if (Parallel_Planes( p2, p3 )) return Cone_Parallel_Planes( s, p2, p3, p1 );
    
    L3 l3 = Line_Of_Intersection_Of_Two_Planes( p1, p2 );
    L3 l2 = Line_Of_Intersection_Of_Two_Planes( p1, p3 );
    
    if (Parallel_Lines( l2, l3 )) return Cone_Parallel_Lines( s, l3, l2, p1, p2, p3 );
    
    P3 vertex = Intersection_Of_Two_Lines3D( l2, l3 );
    
    if (Norm( s.c, vertex ) >= s.r - 0.002) return General_Spherical_Cone_Exterior_Vertex( s, vertex, p1, p2, p3 ); // Changed for T2 dataset: 0.002 or 0.0005 or 0.00005.
    
    Circle3D c = Circular_Intersection_Of_Sphere_And_Plane( s, p1 );
    
    P3 pt1, pt2, pt3, i1, i2;
    
    Intersection_Pts_Of_Plane_And_Circle( p2, c, i1, i2 );
    
    if (Norm( i1, i2 ) < tiny_num || p3.oriented_side( i1 ) == p3.oriented_side( i2 ) || p3.oriented_side( i1 ) == ON_ORIENTED_BOUNDARY || p3.oriented_side( i2 ) == ON_ORIENTED_BOUNDARY) return General_Spherical_Cone_Exterior_Vertex( s, vertex, p1, p2, p3 );
    else if (p3.oriented_side( i1 ) == ON_POSITIVE_SIDE) pt3 = i1;
    else pt3 = i2;
    
    Intersection_Pts_Of_Plane_And_Circle( p3, c, i1, i2 );
    
    if (Norm( i1, i2 ) < tiny_num || p2.oriented_side( i1 ) == p2.oriented_side( i2 ) || p2.oriented_side( i1 ) == ON_ORIENTED_BOUNDARY || p2.oriented_side( i2 ) == ON_ORIENTED_BOUNDARY) return General_Spherical_Cone_Exterior_Vertex( s, vertex, p1, p2, p3 );
    else if (p2.oriented_side( i1 ) == ON_POSITIVE_SIDE) pt2 = i1;
    else pt2 = i2;
    
    c = Circular_Intersection_Of_Sphere_And_Plane( s, p2 );
    
    Intersection_Pts_Of_Plane_And_Circle( p3, c, i1, i2 );
    
    if (Norm( i1, i2 ) < tiny_num || p1.oriented_side( i1 ) == p1.oriented_side( i2 ) || p1.oriented_side( i1 ) == ON_ORIENTED_BOUNDARY || p1.oriented_side( i2 ) == ON_ORIENTED_BOUNDARY) return General_Spherical_Cone_Exterior_Vertex( s, vertex, p1, p2, p3 );
    else if (p1.oriented_side( i1 ) == ON_POSITIVE_SIDE) pt1 = i1;
    else pt1 = i2;
    
    double tet_volume = Tetrahedron_Volume( vertex, pt1, pt2, pt3 );
    
    Pl3 p4( pt1, pt2, pt3 );
    
    if (p4.oriented_side( vertex ) == ON_POSITIVE_SIDE) p4 = p4.opposite();
    
    double cap_volume = Spherical_Cap( s, p4 );
    
    Pl3 p5 = p1.opposite();
    Pl3 p6 = p2.opposite();
    Pl3 p7 = p3.opposite();
    
    double wedge_volume1 = General_Spherical_Wedge( s, p5, p4 );
    double wedge_volume2 = General_Spherical_Wedge( s, p6, p4 );
    double wedge_volume3 = General_Spherical_Wedge( s, p7, p4 );
    
    return tet_volume + cap_volume - wedge_volume1 - wedge_volume2 - wedge_volume3;
}
