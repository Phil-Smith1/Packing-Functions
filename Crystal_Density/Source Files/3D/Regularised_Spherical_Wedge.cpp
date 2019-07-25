#include "Line_Of_Intersection_Of_Two_Planes.h"
#include "Angle_Between_Vectors3D.h"
#include "Spherical_Cap.h"

#include <CGAL/squared_distance_3.h>

double Regularised_Spherical_Wedge ( Sphere const& s, Pl3 const& p1, Pl3 const& p2 )
{
    L3 l = Line_Of_Intersection_Of_Two_Planes( p1, p2 );
    
    double d = sqrt( squared_distance( s.c, l ) );
    
    P3 pt1 = P3( 0, 0, 0 ) + p1.orthogonal_vector();
    P3 pt2 = P3( 0, 0, 0 ) - p2.orthogonal_vector();
    
    double angle = Angle_Between_Vectors( pt1, pt2 );
    
    if (angle <= 0.5 * PI)
    {
        double a = d * sin( angle );
        double b = sqrt( s.r * s.r - d * d );
        double c = d * cos( angle );
        
        double volume = a * b * c / (double)3 + a * (a * a / (double)3 - s.r * s.r) * atan( b / (double)c) + 2 * s.r * s.r * s.r * atan( b * sin( angle ) / (double)(s.r * cos( angle ))) / (double)3;
        
        return volume;
    }
    
    else
    {
        angle = PI - angle;
        
        double a = d * sin( angle );
        double b = sqrt( s.r * s.r - d * d );
        double c = d * cos( angle );
        
        double volume = a * b * c / (double)3 + a * (a * a / (double)3 - s.r * s.r) * atan( b / (double)c) + 2 * s.r * s.r * s.r * atan( b * sin( angle ) / (double)(s.r * cos( angle ))) / (double)3;
        
        return Spherical_Cap( s, p1 ) - volume;
    }
}
