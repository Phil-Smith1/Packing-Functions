#include "General_Spherical_Wedge.h"
#include "Intersection_Pts_Of_Plane_And_Circle.h"

double No_Intersection_Of_Plane_And_Circle ( Sphere const& s, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3, Circle3D const& c1, Circle3D const& c2 )
{
    if (p2.oriented_side( c1.c ) == ON_NEGATIVE_SIDE && p1.oriented_side( c2.c ) == ON_NEGATIVE_SIDE) return 0;
    
    else if (p2.oriented_side( c1.c ) == ON_NEGATIVE_SIDE) return General_Spherical_Wedge( s, p2, p3 );
    
    else if (p1.oriented_side( c2.c ) == ON_NEGATIVE_SIDE) return General_Spherical_Wedge( s, p1, p3 );
    
    else return s.vol - Spherical_Cap( s, p1.opposite() ) - Spherical_Cap( s, p2.opposite() ) - Spherical_Cap( s, p3.opposite() ) + General_Spherical_Wedge( s, p1.opposite(), p3.opposite() ) + General_Spherical_Wedge( s, p2.opposite(), p3.opposite() );
}

double General_Spherical_Cone_Exterior_Vertex ( Sphere const& s, P3 const& vertex, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3 )
{
    double sp1 = Sphere_Plane_Distance( s, p1 ), sp2 = Sphere_Plane_Distance( s, p2 ), sp3 = Sphere_Plane_Distance( s, p3 );
    
    if (sp1 <= -s.r + tiny_num || sp2 <= -s.r + tiny_num || sp3 <= -s.r + tiny_num) return 0;
    
    else if (sp1 >= s.r - tiny_num && sp2 >= s.r - tiny_num && sp3 >= s.r - tiny_num) return s.vol;
    
    else if (sp1 >= s.r - tiny_num && sp2 >= s.r - tiny_num) return Spherical_Cap( s, p3 );
    
    else if (sp1 >= s.r - tiny_num && sp3 >= s.r - tiny_num) return Spherical_Cap( s, p2 );
    
    else if (sp2 >= s.r - tiny_num && sp3 >= s.r - tiny_num) return Spherical_Cap( s, p1 );
    
    else if (sp1 >= s.r - tiny_num) return General_Spherical_Wedge( s, p2, p3 );
    
    else if (sp2 >= s.r - tiny_num) return General_Spherical_Wedge( s, p1, p3 );
    
    else if (sp3 >= s.r - tiny_num) return General_Spherical_Wedge( s, p1, p2 );
    
    else
    {
        Circle3D c1 = Circular_Intersection_Of_Sphere_And_Plane( s, p1 );
        Circle3D c2 = Circular_Intersection_Of_Sphere_And_Plane( s, p2 );
        Circle3D c3 = Circular_Intersection_Of_Sphere_And_Plane( s, p3 );
        
        if (!Intersection_Of_Plane_And_Circle( p2, c1 )) return No_Intersection_Of_Plane_And_Circle( s, p1, p2, p3, c1, c2 );
        
        else if (!Intersection_Of_Plane_And_Circle( p3, c1 )) return No_Intersection_Of_Plane_And_Circle( s, p1, p3, p2, c1, c3 );
        
        else if (!Intersection_Of_Plane_And_Circle( p2, c3 )) return No_Intersection_Of_Plane_And_Circle( s, p3, p2, p1, c3, c2 );
        
        else
        {
            P3 i1, i2, i3, i4, i5, i6;
            
            Intersection_Pts_Of_Plane_And_Circle( p2, c1, i1, i2 );
            Intersection_Pts_Of_Plane_And_Circle( p3, c1, i3, i4 );
            Intersection_Pts_Of_Plane_And_Circle( p2, c3, i5, i6 );
            
            if (Norm( i1, i2 ) < 1e-6)
            {
                if (p2.oriented_side( c1.c ) == ON_NEGATIVE_SIDE && p1.oriented_side( c2.c ) == ON_NEGATIVE_SIDE) return 0;
                
                else if (p2.oriented_side( c1.c ) == ON_NEGATIVE_SIDE) return General_Spherical_Wedge( s, p2, p3 );
                
                else if (p1.oriented_side( c2.c ) == ON_NEGATIVE_SIDE) return General_Spherical_Wedge( s, p1, p3 );
            }
            
            if (Norm( i3, i4 ) < 1e-6)
            {
                if (p3.oriented_side( c1.c ) == ON_NEGATIVE_SIDE && p1.oriented_side( c3.c ) == ON_NEGATIVE_SIDE) return 0;
                
                else if (p3.oriented_side( c1.c ) == ON_NEGATIVE_SIDE) return General_Spherical_Wedge( s, p2, p3 );
                
                else if (p1.oriented_side( c3.c ) == ON_NEGATIVE_SIDE) return General_Spherical_Wedge( s, p1, p2 );
            }
            
            if (Norm( i5, i6 ) < 1e-6)
            {
                if (p2.oriented_side( c3.c ) == ON_NEGATIVE_SIDE && p3.oriented_side( c2.c ) == ON_NEGATIVE_SIDE) return 0;
                
                else if (p2.oriented_side( c3.c ) == ON_NEGATIVE_SIDE) return General_Spherical_Wedge( s, p1, p2 );
                
                else if (p3.oriented_side( c2.c ) == ON_NEGATIVE_SIDE) return General_Spherical_Wedge( s, p1, p3 );
            }
            
            bool positive_side1 = false, positive_side2 = false, positive_side3 = false;
            
            if (Norm( s.c, vertex ) > s.r)
            {
                /*if ((p1.oriented_side( i5 ) == ON_NEGATIVE_SIDE && p1.oriented_side( i6 ) == ON_NEGATIVE_SIDE) || (p1.oriented_side( i5 ) == ON_NEGATIVE_SIDE && squared_distance( i5, p1 ) > tiny_num * 5e6) || (p1.oriented_side( i6 ) == ON_NEGATIVE_SIDE && squared_distance( i6, p1 ) > tiny_num * 5e6)) positive_side1 = false;
                else positive_side1 = true;
                
                if ((p2.oriented_side( i3 ) == ON_NEGATIVE_SIDE && p2.oriented_side( i4 ) == ON_NEGATIVE_SIDE) || (p2.oriented_side( i3 ) == ON_NEGATIVE_SIDE && squared_distance( i3, p2 ) > tiny_num * 5e6) || (p2.oriented_side( i4 ) == ON_NEGATIVE_SIDE && squared_distance( i4, p2 ) > tiny_num * 5e6)) positive_side2 = false;
                else positive_side2 = true;
                
                if ((p3.oriented_side( i1 ) == ON_NEGATIVE_SIDE && p3.oriented_side( i2 ) == ON_NEGATIVE_SIDE) || (p3.oriented_side( i1 ) == ON_NEGATIVE_SIDE && squared_distance( i1, p3 ) > tiny_num * 5e6) || (p3.oriented_side( i2 ) == ON_NEGATIVE_SIDE && squared_distance( i2, p3 ) > tiny_num * 5e6)) positive_side3 = false;
                else positive_side3 = true;*/
                
                if (p1.oriented_side( i5 ) == ON_NEGATIVE_SIDE && p1.oriented_side( i6 ) == ON_NEGATIVE_SIDE) positive_side1 = false;
                
                else if (p1.oriented_side( i5 ) == ON_NEGATIVE_SIDE && p1.oriented_side( i6 ) == ON_POSITIVE_SIDE)
                {
                    squared_distance( i5, p1 ) > squared_distance( i6, p1 ) ? positive_side1 = false : positive_side1 = true;
                }
                
                else if (p1.oriented_side( i5 ) == ON_POSITIVE_SIDE && p1.oriented_side( i6 ) == ON_NEGATIVE_SIDE)
                {
                    squared_distance( i5, p1 ) > squared_distance( i6, p1 ) ? positive_side1 = true : positive_side1 = false;
                }
                
                else positive_side1 = true;
                
                if (p2.oriented_side( i3 ) == ON_NEGATIVE_SIDE && p2.oriented_side( i4 ) == ON_NEGATIVE_SIDE) positive_side2 = false;
                
                else if (p2.oriented_side( i3 ) == ON_NEGATIVE_SIDE && p2.oriented_side( i4 ) == ON_POSITIVE_SIDE)
                {
                    squared_distance( i3, p2 ) > squared_distance( i4, p2 ) ? positive_side2 = false : positive_side2 = true;
                }
                
                else if (p2.oriented_side( i3 ) == ON_POSITIVE_SIDE && p2.oriented_side( i4 ) == ON_NEGATIVE_SIDE)
                {
                    squared_distance( i3, p2 ) > squared_distance( i4, p2 ) ? positive_side2 = true : positive_side2 = false;
                }
                
                else positive_side2 = true;
                
                if (p3.oriented_side( i1 ) == ON_NEGATIVE_SIDE && p3.oriented_side( i2 ) == ON_NEGATIVE_SIDE) positive_side3 = false;
                
                else if (p3.oriented_side( i1 ) == ON_NEGATIVE_SIDE && p3.oriented_side( i2 ) == ON_POSITIVE_SIDE)
                {
                    squared_distance( i1, p3 ) > squared_distance( i2, p3 ) ? positive_side3 = false : positive_side3 = true;
                }
                
                else if (p3.oriented_side( i1 ) == ON_POSITIVE_SIDE && p3.oriented_side( i2 ) == ON_NEGATIVE_SIDE)
                {
                    squared_distance( i1, p3 ) > squared_distance( i2, p3 ) ? positive_side3 = true : positive_side3 = false;
                }
                
                else positive_side3 = true;
                
                int num_pos = 0;
                
                if (positive_side1) ++num_pos;
                if (positive_side2) ++num_pos;
                if (positive_side3) ++num_pos;
                
                if (num_pos == 0) return 0;
                
                else if (num_pos == 1)
                {
                    if (positive_side1) return General_Spherical_Wedge( s, p2, p3 );
                    
                    else if (positive_side2) return General_Spherical_Wedge( s, p1, p3 );
                    
                    else return General_Spherical_Wedge( s, p1, p2 );
                }
                
                else if (num_pos == 2)
                {
                    if (!positive_side1) return Spherical_Cap( s, p1 ) - General_Spherical_Wedge( s, p1, p2.opposite() ) - General_Spherical_Wedge( s, p1, p3.opposite() );
                    
                    else if (!positive_side2) return Spherical_Cap( s, p2 ) - General_Spherical_Wedge( s, p1.opposite(), p2 ) - General_Spherical_Wedge( s, p2, p3.opposite() );
                    
                    else return Spherical_Cap( s, p3 ) - General_Spherical_Wedge( s, p1.opposite(), p3 ) - General_Spherical_Wedge( s, p2.opposite(), p3 );
                }
                
                else
                {
                    double volume = s.vol - Spherical_Cap( s, p1.opposite() ) - Spherical_Cap( s, p2.opposite() ) - Spherical_Cap( s, p3.opposite() ) + General_Spherical_Wedge( s, p1.opposite(), p2.opposite() ) + General_Spherical_Wedge( s, p1.opposite(), p3.opposite() ) + General_Spherical_Wedge( s, p2.opposite(), p3.opposite() );
                    
                    return volume;
                }
            }
            
            else
            {
                // Changed to *1e5 for T2 dataset. Changed to *5e5 for T2 dataset No.38. New term for T2 dataset No. 180.
                
                P3 i7, i8, i9;
                
                squared_distance( i5, p1 ) > squared_distance( i6, p1 ) ? i7 = i5 : i7 = i6;
                squared_distance( i3, p2 ) > squared_distance( i4, p2 ) ? i8 = i3 : i8 = i4;
                squared_distance( i1, p3 ) > squared_distance( i2, p3 ) ? i9 = i1 : i9 = i2;
                
                if (p1.oriented_side( i7 ) == ON_NEGATIVE_SIDE) positive_side1 = false;
                else positive_side1 = true;
                
                if (p2.oriented_side( i8 ) == ON_NEGATIVE_SIDE) positive_side2 = false;
                else positive_side2 = true;
                
                if (p3.oriented_side( i9 ) == ON_NEGATIVE_SIDE) positive_side3 = false;
                else positive_side3 = true;
                
                int num_pos = 0;
                
                if (positive_side1) ++num_pos;
                if (positive_side2) ++num_pos;
                if (positive_side3) ++num_pos;
                
                if (num_pos == 0) return 0;
                
                else if (num_pos == 1)
                {
                    if (positive_side1) return General_Spherical_Wedge( s, p2, p3 );
                    
                    else if (positive_side2) return General_Spherical_Wedge( s, p1, p3 );
                    
                    else return General_Spherical_Wedge( s, p1, p2 );
                }
                
                else if (num_pos == 2)
                {
                    if (!positive_side1) return Spherical_Cap( s, p1 ) - General_Spherical_Wedge( s, p1, p2.opposite() ) - General_Spherical_Wedge( s, p1, p3.opposite() );
                    
                    else if (!positive_side2) return Spherical_Cap( s, p2 ) - General_Spherical_Wedge( s, p1.opposite(), p2 ) - General_Spherical_Wedge( s, p2, p3.opposite() );
                    
                    else return Spherical_Cap( s, p3 ) - General_Spherical_Wedge( s, p1.opposite(), p3 ) - General_Spherical_Wedge( s, p2.opposite(), p3 );
                }
                
                else
                {
                    double volume = s.vol - Spherical_Cap( s, p1.opposite() ) - Spherical_Cap( s, p2.opposite() ) - Spherical_Cap( s, p3.opposite() ) + General_Spherical_Wedge( s, p1.opposite(), p2.opposite() ) + General_Spherical_Wedge( s, p1.opposite(), p3.opposite() ) + General_Spherical_Wedge( s, p2.opposite(), p3.opposite() );
                    
                    return volume;
                }
            }
        }
    }
}
