#include "Spherical_Cap.h"
#include "General_Spherical_Wedge.h"
#include "Intersection_Of_Two_Lines3D.h"
#include "Circular_Intersection_Of_Sphere_And_Plane.h"
#include "Intersection_Pts_Of_Plane_And_Circle.h"
#include "Tetrahedron_Volume.h"

double General_Spherical_Cone ( Sphere const& s, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3 )
{
    L3 l1 = Line_Of_Intersection_Of_Two_Planes( p1, p2 );
    L3 l2 = Line_Of_Intersection_Of_Two_Planes( p1, p3 );
    
    P3 vertex = Intersection_Of_Two_Lines3D( l1, l2 );
    
    Circle3D c = Circular_Intersection_Of_Sphere_And_Plane( s, p1 );
    
    P3 pt1, pt2, pt3, i1, i2;
    
    Intersection_Pts_Of_Plane_And_Circle( p2, c, i1, i2 );
    
    if (p3.oriented_side( i1 ) == ON_POSITIVE_SIDE) pt3 = i1;
    else pt3 = i2;
    
    Intersection_Pts_Of_Plane_And_Circle( p3, c, i1, i2 );
    
    if (p2.oriented_side( i1 ) == ON_POSITIVE_SIDE) pt2 = i1;
    else pt2 = i2;
    
    c = Circular_Intersection_Of_Sphere_And_Plane( s, p2 );
    
    Intersection_Pts_Of_Plane_And_Circle( p3, c, i1, i2 );
    
    if (p1.oriented_side( i1 ) == ON_POSITIVE_SIDE) pt1 = i1;
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