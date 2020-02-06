#include "Sphere_Four_Plane_Intersection_Volume.h"

double Sphere_Five_Plane_Intersection_Volume ( Sphere const& s, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3, Pl3 const& p4, Pl3 const& p5, int iter );

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
    
    //else return Spherical_Cap( s, p1 ) + Spherical_Cap( s, p2 ) + Spherical_Cap( s, p3 ) + Spherical_Cap( s, p4 ) + Spherical_Cap( s, p5 ) - General_Spherical_Wedge( s, p1, p3 ) - General_Spherical_Wedge( s, p1, p4 ) - General_Spherical_Wedge( s, p1, p5 ) - General_Spherical_Wedge( s, p2, p3 ) - General_Spherical_Wedge( s, p2, p4 ) - General_Spherical_Wedge( s, p2, p5 ) - General_Spherical_Wedge( s, p3, p4 ) - General_Spherical_Wedge( s, p3, p5 ) - General_Spherical_Wedge( s, p4, p5 ) + General_Spherical_Cone( s, p1, p3, p4 ) + General_Spherical_Cone( s, p1, p3, p5 ) + General_Spherical_Cone( s, p1, p4, p5 ) + General_Spherical_Cone( s, p2, p3, p4 ) + General_Spherical_Cone( s, p2, p3, p5 ) + General_Spherical_Cone( s, p2, p4, p5 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p3, p4, p5 ) - Sphere_Four_Plane_Intersection_Volume( s, p2, p3, p4, p5 );
    
    else return Spherical_Cap( s, p1 ) + Spherical_Cap( s, p2 ) - s.vol - Spherical_Cap( s, p3.opposite() ) - Spherical_Cap( s, p4.opposite() ) - Spherical_Cap( s, p5.opposite() ) + General_Spherical_Wedge( s, p1.opposite(), p3.opposite() ) + General_Spherical_Wedge( s, p1.opposite(), p4.opposite() ) + General_Spherical_Wedge( s, p1.opposite(), p5.opposite() ) + General_Spherical_Wedge( s, p2.opposite(), p3.opposite() ) + General_Spherical_Wedge( s, p2.opposite(), p4.opposite() ) + General_Spherical_Wedge( s, p2.opposite(), p5.opposite() ) + General_Spherical_Wedge( s, p3.opposite(), p4.opposite() ) + General_Spherical_Wedge( s, p3.opposite(), p5.opposite() ) + General_Spherical_Wedge( s, p4.opposite(), p5.opposite() ) - General_Spherical_Cone( s, p1.opposite(), p3.opposite(), p4.opposite() ) - General_Spherical_Cone( s, p1.opposite(), p3.opposite(), p5.opposite() ) - General_Spherical_Cone( s, p1.opposite(), p4.opposite(), p5.opposite() ) - General_Spherical_Cone( s, p2.opposite(), p3.opposite(), p4.opposite() ) - General_Spherical_Cone( s, p2.opposite(), p3.opposite(), p5.opposite() ) - General_Spherical_Cone( s, p2.opposite(), p4.opposite(), p5.opposite() ) - General_Spherical_Cone( s, p3.opposite(), p4.opposite(), p5.opposite() ) + Sphere_Four_Plane_Intersection_Volume( s, p1.opposite(), p3.opposite(), p4.opposite(), p5.opposite() ) + Sphere_Four_Plane_Intersection_Volume( s, p2.opposite(), p3.opposite(), p4.opposite(), p5.opposite() );
}

double Fourth_Plane_Parallel_To_Line5 ( Sphere const& s, L3 const& l, P3 const& i1, P3 const& i2, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3, Pl3 const& p4, Pl3 const& p5, Pl3 const& p6, int iter )
{
    if (squared_distance( l.point(), p4 ) < tiny_num)
    {
        L3 l2 = Line_Of_Intersection_Of_Two_Planes( p1, p3 );
        L3 l3 = Line_Of_Intersection_Of_Two_Planes( p2, p3 );
        
        P3 pt2 = l2.point();
        P3 pt3 = l3.point();
        
        if (squared_distance( pt2, p6 ) < tiny_num) pt2 += l2.to_vector();
        if (squared_distance( pt3, p6 ) < tiny_num) pt3 += l3.to_vector();
        
        if (p6.oriented_side( pt2 ) == p4.oriented_side( pt2 ) && p6.oriented_side( pt3 ) == p4.oriented_side( pt3 ))
        {
            return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5 );
        }
        
        else if (p6.oriented_side( pt2 ) != p4.oriented_side( pt2 ) && p6.oriented_side( pt3 ) != p4.oriented_side( pt3 ))
        {
            return 0;
        }
        
        else if (p6.oriented_side( pt2 ) == p4.oriented_side( pt2 )) return Sphere_Four_Plane_Intersection_Volume( s, p1, p3, p4, p5 );
        
        else return Sphere_Four_Plane_Intersection_Volume( s, p2, p3, p4, p5 );
    }
    
    else if (p4.oriented_side( l.point() ) == ON_POSITIVE_SIDE)
    {
        if (p6.oriented_side( i1 ) == ON_POSITIVE_SIDE)
        {
            if (p6.oriented_side( i2 ) == ON_POSITIVE_SIDE)
            {
                return Sphere_Five_Plane_Intersection_Volume( s, p2, p3, p4, p5, p1, iter );
            }
            
            else
            {
                return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p3, p4.opposite(), p5 );
            }
        }
        
        else
        {
            if (p6.oriented_side( i2 ) == ON_POSITIVE_SIDE)
            {
                return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5 ) - Sphere_Four_Plane_Intersection_Volume( s, p2, p3, p4.opposite(), p5 );
            }
            
            else return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5 );
        }
    }
    
    else
    {
        if (p6.oriented_side( i1 ) == ON_POSITIVE_SIDE)
        {
            if (p6.oriented_side( i2 ) == ON_POSITIVE_SIDE)
            {
                return Sphere_Five_Plane_Intersection_Volume( s, p2, p3, p4, p5, p1, iter );
            }
            
            else return Sphere_Four_Plane_Intersection_Volume( s, p1, p3, p4, p5 );
        }
        
        else
        {
            if (p6.oriented_side( i2 ) == ON_POSITIVE_SIDE) return Sphere_Four_Plane_Intersection_Volume( s, p2, p3, p4, p5 );
            
            else return 0;
        }
    }
}

double Non_Parallel_Lines_Case5A ( Sphere const& s, L3 const& l1, L3 const& l2, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3, Pl3 const& p4, Pl3 const& p5, int iter )
{
    L3 l3 = Line_Of_Intersection_Of_Two_Planes( p2, p3 );
    
    P3 vertex = Intersection_Of_Two_Lines3D( l1, l2 );
    
    P3 pt1 = vertex + l1.to_vector();
    P3 pt2 = vertex + l2.to_vector();
    P3 pt3 = vertex + l3.to_vector();
    
    if (p3.oriented_side( pt1 ) == ON_NEGATIVE_SIDE) pt1 = vertex - l1.to_vector();
    if (p2.oriented_side( pt2 ) == ON_NEGATIVE_SIDE) pt2 = vertex - l2.to_vector();
    if (p1.oriented_side( pt3 ) == ON_NEGATIVE_SIDE) pt3 = vertex - l3.to_vector();
    
    Pl3 p6( pt1, pt2, pt3 );
    
    if (p6.oriented_side( vertex ) == ON_POSITIVE_SIDE) p6 = p6.opposite();
    
    p6 = Pl3( vertex, p6.orthogonal_vector() );
    
    P3 i1, i2, i3;
    
    bool intersection1 = Intersection_Of_Line_And_Plane( p4, l1, i1 );
    bool intersection2 = Intersection_Of_Line_And_Plane( p4, l2, i2 );
    bool intersection3 = Intersection_Of_Line_And_Plane( p4, l3, i3 );
    
    if (!intersection1) return Fourth_Plane_Parallel_To_Line5( s, l1, i2, i3, p1, p2, p3, p4, p5, p6, iter );
    else if (!intersection2) return Fourth_Plane_Parallel_To_Line5( s, l2, i1, i3, p1, p3, p2, p4, p5, p6, iter );
    else if (!intersection3) return Fourth_Plane_Parallel_To_Line5( s, l3, i1, i2, p2, p3, p1, p4, p5, p6, iter );
    
    else
    {
        if (squared_distance( vertex, p4 ) < tiny_num)
        {
            if (p4.oriented_side( pt1 ) == ON_POSITIVE_SIDE)
            {
                if (p4.oriented_side( pt2 ) == ON_POSITIVE_SIDE)
                {
                    if (p4.oriented_side( pt3 ) == ON_POSITIVE_SIDE) return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5 );
                    
                    else return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5 ) - Sphere_Four_Plane_Intersection_Volume( s, p2, p3, p4.opposite(), p5 );
                }
                
                else
                {
                    if (p4.oriented_side( pt3 ) == ON_POSITIVE_SIDE) return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p3, p4.opposite(), p5 );
                    
                    else return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p4, p5 );
                }
            }
            
            else
            {
                if (p4.oriented_side( pt2 ) == ON_POSITIVE_SIDE)
                {
                    if (p4.oriented_side( pt3 ) == ON_POSITIVE_SIDE) return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p4.opposite(), p5 );
                    
                    else return Sphere_Four_Plane_Intersection_Volume( s, p1, p3, p4, p5 );
                }
                
                else
                {
                    if (p4.oriented_side( pt3 ) == ON_POSITIVE_SIDE) return Sphere_Four_Plane_Intersection_Volume( s, p2, p3, p4, p5 );
                    
                    else return 0;
                }
            }
        }
        
        else if (p4.oriented_side( vertex ) == ON_POSITIVE_SIDE)
        {
            if (squared_distance( i1, p6 ) < 1e-6 || squared_distance( i2, p6 ) < 1e-6 || squared_distance( i3, p6 ) < 1e-6)
            {
                return Sphere_Five_Plane_Intersection_Volume( s, p2, p3, p4, p5, p1, iter );
            }
            
            else if (p6.oriented_side( i1 ) == ON_POSITIVE_SIDE)
            {
                if (p6.oriented_side( i2 ) == ON_POSITIVE_SIDE)
                {
                    if (p6.oriented_side( i3 ) == ON_POSITIVE_SIDE)
                    {
                        return Sphere_Five_Plane_Intersection_Volume( s, p2, p3, p4, p5, p1, iter );
                    }
                    
                    else
                    {
                        return Sphere_Five_Plane_Intersection_Volume( s, p2, p3, p4, p5, p1, iter );
                    }
                }
                
                else
                {
                    if (p6.oriented_side( i3 ) == ON_POSITIVE_SIDE)
                    {
                        return Sphere_Five_Plane_Intersection_Volume( s, p2, p3, p4, p5, p1, iter );
                    }
                    
                    else return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p4.opposite(), p5 );
                }
            }
            
            else
            {
                if (p6.oriented_side( i2 ) == ON_POSITIVE_SIDE)
                {
                    if (p6.oriented_side( i3 ) == ON_POSITIVE_SIDE)
                    {
                        return Sphere_Five_Plane_Intersection_Volume( s, p2, p3, p4, p5, p1, iter );
                    }
                    
                    else return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p3, p4.opposite(), p5 );
                }
                
                else
                {
                    if (p6.oriented_side( i3 ) == ON_POSITIVE_SIDE)
                    {
                        return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5 ) - Sphere_Four_Plane_Intersection_Volume( s, p2, p3, p4.opposite(), p5 );
                    }
                    
                    else return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5 );
                }
            }
        }
        
        
        else
        {
            if (squared_distance( i1, p6 ) < 1e-6 || squared_distance( i2, p6 ) < 1e-6 || squared_distance( i3, p6 ) < 1e-6)
            {
                return Sphere_Five_Plane_Intersection_Volume( s, p2, p3, p4, p5, p1, iter );
            }
            
            else if (p6.oriented_side( i1 ) == ON_POSITIVE_SIDE)
            {
                if (p6.oriented_side( i2 ) == ON_POSITIVE_SIDE)
                {
                    if (p6.oriented_side( i3 ) == ON_POSITIVE_SIDE)
                    {
                        return Sphere_Five_Plane_Intersection_Volume( s, p2, p3, p4, p5, p1, iter );
                    }
                    
                    else
                    {
                        return Sphere_Five_Plane_Intersection_Volume( s, p2, p3, p4, p5, p1, iter );
                    }
                }
                
                else
                {
                    if (p6.oriented_side( i3 ) == ON_POSITIVE_SIDE)
                    {
                        return Sphere_Five_Plane_Intersection_Volume( s, p2, p3, p4, p5, p1, iter );
                    }
                    
                    return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p4, p5 );
                }
            }
            
            else
            {
                if (p6.oriented_side( i2 ) == ON_POSITIVE_SIDE)
                {
                    if (p6.oriented_side( i3 ) == ON_POSITIVE_SIDE)
                    {
                        return Sphere_Five_Plane_Intersection_Volume( s, p2, p3, p4, p5, p1, iter );
                    }
                    
                    else return Sphere_Four_Plane_Intersection_Volume( s, p1, p3, p4, p5 );
                }
                
                else
                {
                    if (p6.oriented_side( i3 ) == ON_POSITIVE_SIDE) return Sphere_Four_Plane_Intersection_Volume( s, p2, p3, p4, p5 );
                    
                    else return 0;
                }
            }
        }
    }
}

double Non_Parallel_Lines_Case5B ( Sphere const& s, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3, Pl3 const& p4, Pl3 const& p5, int iter )
{
    /*double volume_1 = Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p4 );
    double volume_2 = Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5 );
    double volume_3 = Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p4, p5 );
    double volume_4 = Sphere_Four_Plane_Intersection_Volume( s, p1, p3, p4, p5 );
    double volume_5 = Sphere_Four_Plane_Intersection_Volume( s, p2, p3, p4, p5 );
    
    if (volume_1 > volume_2) volume_1 = volume_2;
    if (volume_1 > volume_3) volume_1 = volume_3;
    if (volume_1 > volume_4) volume_1 = volume_4;
    if (volume_1 > volume_5) volume_1 = volume_5;
    
    return volume_1;*/
    
    L3 l1 = Line_Of_Intersection_Of_Two_Planes( p1, p2 );
    L3 l2 = Line_Of_Intersection_Of_Two_Planes( p1, p3 );
    L3 l3 = Line_Of_Intersection_Of_Two_Planes( p2, p3 );
    
    if (Parallel_Lines( l1, l2 )) return Sphere_Five_Plane_Intersection_Volume( s, p2, p3, p4, p5, p1, iter );
    
    P3 vertex = Intersection_Of_Two_Lines3D( l1, l2 );
    
    P3 pt1 = vertex + l1.to_vector();
    P3 pt2 = vertex + l2.to_vector();
    P3 pt3 = vertex + l3.to_vector();
    
    if (p3.oriented_side( pt1 ) == ON_NEGATIVE_SIDE) pt1 = vertex - l1.to_vector();
    if (p2.oriented_side( pt2 ) == ON_NEGATIVE_SIDE) pt2 = vertex - l2.to_vector();
    if (p1.oriented_side( pt3 ) == ON_NEGATIVE_SIDE) pt3 = vertex - l3.to_vector();
    
    Pl3 p6( pt1, pt2, pt3 );
    
    if (p6.oriented_side( vertex ) == ON_POSITIVE_SIDE) p6 = p6.opposite();
    
    p6 = Pl3( vertex, p6.orthogonal_vector() );
    
    P3 i1, i2, i3, i4, i5, i6;
    
    Intersection_Of_Line_And_Plane( p4, l1, i1 );
    Intersection_Of_Line_And_Plane( p4, l2, i2 );
    Intersection_Of_Line_And_Plane( p4, l3, i3 );
    Intersection_Of_Line_And_Plane( p5, l1, i4 );
    Intersection_Of_Line_And_Plane( p5, l2, i5 );
    Intersection_Of_Line_And_Plane( p5, l3, i6 );
    
    if (p5.oriented_side( i1 ) == ON_POSITIVE_SIDE && p5.oriented_side( i2 ) == ON_POSITIVE_SIDE && p5.oriented_side( i3 ) == ON_POSITIVE_SIDE && p5.oriented_side( vertex ) == ON_NEGATIVE_SIDE && squared_distance( p5, vertex ) > 1e-3)
    {
        if (p6.oriented_side( i1 ) == ON_POSITIVE_SIDE)
        {
            if (p6.oriented_side( i2 ) == ON_POSITIVE_SIDE)
            {
                if (p6.oriented_side( i3 ) == ON_POSITIVE_SIDE)
                {
                    if (p4.oriented_side( vertex ) == ON_POSITIVE_SIDE)
                    {
                        return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p4 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5.opposite() );
                    }
                    
                    else return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p4 );
                }
                
                else
                {
                    if (p4.oriented_side( vertex ) == ON_POSITIVE_SIDE)
                    {
                        return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p4 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5.opposite() ) + Sphere_Four_Plane_Intersection_Volume( s, p2, p3, p4.opposite(), p5.opposite() );
                    }
                    
                    else return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p4 ) - Sphere_Four_Plane_Intersection_Volume( s, p2, p3, p4, p5.opposite() );
                }
            }
            
            else
            {
                if (p6.oriented_side( i3 ) == ON_POSITIVE_SIDE)
                {
                    if (p4.oriented_side( vertex ) == ON_POSITIVE_SIDE)
                    {
                        return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p4 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5.opposite() ) + Sphere_Four_Plane_Intersection_Volume( s, p1, p3, p4.opposite(), p5.opposite() );
                    }
                    
                    else return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p4 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p3, p4, p5.opposite() );
                }
                
                else
                {
                    if (p4.oriented_side( vertex ) == ON_POSITIVE_SIDE)
                    {
                        return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p4 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5.opposite() ) + Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p4.opposite(), p5.opposite() );
                    }
                    
                    else return General_Spherical_Cone( s, p1, p2, p4 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p4, p5.opposite() );
                }
            }
        }
        
        else
        {
            if (p6.oriented_side( i2 ) == ON_POSITIVE_SIDE)
            {
                if (p6.oriented_side( i3 ) == ON_POSITIVE_SIDE)
                {
                    if (p4.oriented_side( vertex ) == ON_POSITIVE_SIDE)
                    {
                        return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p4 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5.opposite() ) + Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p4.opposite(), p5.opposite() );
                    }
                    
                    else return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p4 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p4, p5.opposite() );
                }
                
                else
                {
                    if (p4.oriented_side( vertex ) == ON_POSITIVE_SIDE)
                    {
                        return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p4 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5.opposite() ) + Sphere_Four_Plane_Intersection_Volume( s, p1, p3, p4.opposite(), p5.opposite() );
                    }
                    
                    else return General_Spherical_Cone( s, p1, p3, p4 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p3, p4, p5.opposite() );
                }
            }
            
            else
            {
                if (p6.oriented_side( i3 ) == ON_POSITIVE_SIDE)
                {
                    if (p4.oriented_side( vertex ) == ON_POSITIVE_SIDE)
                    {
                        return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p4 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5.opposite() ) + Sphere_Four_Plane_Intersection_Volume( s, p2, p3, p4.opposite(), p5.opposite() );
                    }
                    
                    else return General_Spherical_Cone( s, p2, p3, p4 ) - Sphere_Four_Plane_Intersection_Volume( s, p2, p3, p4, p5.opposite() );
                }
                
                else
                {
                    if (p4.oriented_side( vertex ) == ON_POSITIVE_SIDE)
                    {
                        return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5 );
                    }
                    
                    else return 0;
                }
            }
        }
    }
    
    else if (p4.oriented_side( i4 ) == ON_POSITIVE_SIDE && p4.oriented_side( i5 ) == ON_POSITIVE_SIDE && p4.oriented_side( i6 ) == ON_POSITIVE_SIDE && p4.oriented_side( vertex ) == ON_NEGATIVE_SIDE && squared_distance( p4, vertex ) > 1e-3)
    {
        if (p6.oriented_side( i4 ) == ON_POSITIVE_SIDE)
        {
            if (p6.oriented_side( i5 ) == ON_POSITIVE_SIDE)
            {
                if (p6.oriented_side( i6 ) == ON_POSITIVE_SIDE)
                {
                    if (p5.oriented_side( vertex ) == ON_POSITIVE_SIDE)
                    {
                        return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p4.opposite() );
                    }
                    
                    else return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5 );
                }
                
                else
                {
                    if (p5.oriented_side( vertex ) == ON_POSITIVE_SIDE)
                    {
                        return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p4.opposite() ) + Sphere_Four_Plane_Intersection_Volume( s, p2, p3, p4.opposite(), p5.opposite() );
                    }
                    
                    else return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5 ) - Sphere_Four_Plane_Intersection_Volume( s, p2, p3, p4.opposite(), p5 );
                }
            }
            
            else
            {
                if (p6.oriented_side( i6 ) == ON_POSITIVE_SIDE)
                {
                    if (p5.oriented_side( vertex ) == ON_POSITIVE_SIDE)
                    {
                        return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p4.opposite() ) + Sphere_Four_Plane_Intersection_Volume( s, p1, p3, p4.opposite(), p5.opposite() );
                    }
                    
                    else return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p3, p4.opposite(), p5 );
                }
                
                else
                {
                    if (p5.oriented_side( vertex ) == ON_POSITIVE_SIDE)
                    {
                        return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p4.opposite() ) + Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p4.opposite(), p5.opposite() );
                    }
                    
                    else return General_Spherical_Cone( s, p1, p2, p5 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p4.opposite(), p5 );
                }
            }
        }
        
        else
        {
            if (p6.oriented_side( i5 ) == ON_POSITIVE_SIDE)
            {
                if (p6.oriented_side( i6 ) == ON_POSITIVE_SIDE)
                {
                    if (p5.oriented_side( vertex ) == ON_POSITIVE_SIDE)
                    {
                        return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p4.opposite() ) + Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p4.opposite(), p5.opposite() );
                    }
                    
                    else return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p4.opposite(), p5 );
                }
                
                else
                {
                    if (p5.oriented_side( vertex ) == ON_POSITIVE_SIDE)
                    {
                        return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p4.opposite() ) + Sphere_Four_Plane_Intersection_Volume( s, p1, p3, p4.opposite(), p5.opposite() );
                    }
                    
                    else return General_Spherical_Cone( s, p1, p3, p5 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p3, p4.opposite(), p5 );
                }
            }
            
            else
            {
                if (p6.oriented_side( i6 ) == ON_POSITIVE_SIDE)
                {
                    if (p5.oriented_side( vertex ) == ON_POSITIVE_SIDE)
                    {
                        return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p5 ) - Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p4.opposite() ) + Sphere_Four_Plane_Intersection_Volume( s, p2, p3, p4.opposite(), p5.opposite() );
                    }
                    
                    else return General_Spherical_Cone( s, p2, p3, p5 ) - Sphere_Four_Plane_Intersection_Volume( s, p2, p3, p4.opposite(), p5 );
                }
                
                else
                {
                    if (p5.oriented_side( vertex ) == ON_POSITIVE_SIDE)
                    {
                        return Sphere_Four_Plane_Intersection_Volume( s, p1, p2, p3, p4 );
                    }
                    
                    else return 0;
                }
            }
        }
    }
    
    else return Sphere_Five_Plane_Intersection_Volume( s, p2, p3, p4, p5, p1, iter );
}

double Sphere_Five_Plane_Intersection_Volume ( Sphere const& s, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3, Pl3 const& p4, Pl3 const& p5, int iter )
{
    ++iter;
    
    if (iter >= 21)
    {
        std::cout << "Repeated call of function." << std::endl << std::endl;
        
        return 0;
    }
    
    if (iter >= 16) return Non_Parallel_Lines_Case5B( s, p3, p1, p4, p2, p5, iter );
    
    if (iter >= 11) return Non_Parallel_Lines_Case5B( s, p1, p2, p3, p4, p5, iter );
    
    if (iter == 1)
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
    }
    
    if (iter >= 6)
    {
        L3 l1 = Line_Of_Intersection_Of_Two_Planes( p3, p1 );
        L3 l2 = Line_Of_Intersection_Of_Two_Planes( p3, p4 );
        L3 l3 = Line_Of_Intersection_Of_Two_Planes( p3, p2 );
        
        if (!Parallel_Lines( l1, l2 )) return Non_Parallel_Lines_Case5A( s, l1, l2, p3, p1, p4, p2, p5, iter );
        else if (!Parallel_Lines( l1, l3 )) return Non_Parallel_Lines_Case5A( s, l1, l3, p3, p1, p2, p4, p5, iter );
        
        else return 0;
    }
    
    L3 l1 = Line_Of_Intersection_Of_Two_Planes( p1, p2 );
    L3 l2 = Line_Of_Intersection_Of_Two_Planes( p1, p3 );
    L3 l3 = Line_Of_Intersection_Of_Two_Planes( p1, p4 );
    
    if (!Parallel_Lines( l1, l2 )) return Non_Parallel_Lines_Case5A( s, l1, l2, p1, p2, p3, p4, p5, iter );
    else if (!Parallel_Lines( l1, l3 )) return Non_Parallel_Lines_Case5A( s, l1, l3, p1, p2, p4, p3, p5, iter );
    
    else return 0;
}
