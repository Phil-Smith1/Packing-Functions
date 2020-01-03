#include "General_Spherical_Cone.h"

double Parallel_Planes_Case ( Sphere const& s, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3, Pl3 const& p4 )
{
    if (p2.oriented_side( p1.point() ) == ON_ORIENTED_BOUNDARY)
    {
        P3 pt = P3( 0, 0, 0 ) + p1.orthogonal_vector();
        
        if (p2.oriented_side( pt ) == ON_NEGATIVE_SIDE) return 0;
        
        else return General_Spherical_Cone( s, p1, p3, p4 );
    }
    
    else if (p2.oriented_side( p1.point() ) == ON_NEGATIVE_SIDE && p1.oriented_side( p2.point() ) == ON_NEGATIVE_SIDE) return 0;
    
    else if (p2.oriented_side( p1.point() ) == ON_NEGATIVE_SIDE) return General_Spherical_Cone( s, p2, p3, p4 );
    
    else if (p1.oriented_side( p2.point() ) == ON_NEGATIVE_SIDE) return General_Spherical_Cone( s, p1, p3, p4 );
    
    //else return Spherical_Cap( s, p1 ) + Spherical_Cap( s, p2 ) + Spherical_Cap( s, p3 ) + Spherical_Cap( s, p4 ) - General_Spherical_Wedge( s, p1, p3 ) - General_Spherical_Wedge( s, p1, p4 ) - General_Spherical_Wedge( s, p2, p3 ) - General_Spherical_Wedge( s, p2, p4 ) - General_Spherical_Wedge( s, p3, p4 ) + General_Spherical_Cone( s, p1, p3, p4 ) + General_Spherical_Cone( s, p2, p3, p4 );
    
    else return Spherical_Cap( s, p1 ) + Spherical_Cap( s, p2 ) - s.vol - Spherical_Cap( s, p3.opposite() ) - Spherical_Cap( s, p4.opposite() ) + General_Spherical_Wedge( s, p1.opposite(), p3.opposite() ) + General_Spherical_Wedge( s, p1.opposite(), p4.opposite() ) + General_Spherical_Wedge( s, p2.opposite(), p3.opposite() ) + General_Spherical_Wedge( s, p2.opposite(), p4.opposite() ) + General_Spherical_Wedge( s, p3.opposite(), p4.opposite() ) - General_Spherical_Cone( s, p1.opposite(), p3.opposite(), p4.opposite() ) - General_Spherical_Cone( s, p2.opposite(), p3.opposite(), p4.opposite() );
}

double Fourth_Plane_Parallel_To_Line ( Sphere const& s, L3 const& l, P3 const& i1, P3 const& i2, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3, Pl3 const& p4, Pl3 const& p5 )
{
    if (squared_distance( l.point(), p4 ) < tiny_num)
    {
        L3 l2 = Line_Of_Intersection_Of_Two_Planes( p1, p3 );
        L3 l3 = Line_Of_Intersection_Of_Two_Planes( p2, p3 );
        
        P3 pt2 = l2.point();
        P3 pt3 = l3.point();
        
        if (squared_distance( pt2, p5 ) < tiny_num) pt2 += l2.to_vector();
        if (squared_distance( pt3, p5 ) < tiny_num) pt3 += l3.to_vector();
        
        if (p5.oriented_side( pt2 ) == p4.oriented_side( pt2 ) && p5.oriented_side( pt3 ) == p4.oriented_side( pt3 ))
        {
            return General_Spherical_Cone( s, p1, p2, p3 );
        }
        
        else if (p5.oriented_side( pt2 ) != p4.oriented_side( pt2 ) && p5.oriented_side( pt3 ) != p4.oriented_side( pt3 ))
        {
            return 0;
        }
        
        else if (p5.oriented_side( pt2 ) == p4.oriented_side( pt2 )) return General_Spherical_Cone( s, p1, p3, p4 );
        
        else return General_Spherical_Cone( s, p2, p3, p4 );
    }
    
    else if (p4.oriented_side( l.point() ) == ON_POSITIVE_SIDE)
    {
        if (p5.oriented_side( i1 ) == ON_POSITIVE_SIDE)
        {
            if (p5.oriented_side( i2 ) == ON_POSITIVE_SIDE)
            {
                return General_Spherical_Cone( s, p1, p2, p3 ) - Spherical_Cap( s, p4.opposite() ) + General_Spherical_Wedge( s, p1.opposite(), p4.opposite() ) + General_Spherical_Wedge( s, p2.opposite(), p4.opposite() ) + General_Spherical_Wedge( s, p3.opposite(), p4.opposite() ) - General_Spherical_Cone( s, p2.opposite(), p3.opposite(), p4.opposite() ) - General_Spherical_Cone( s, p1.opposite(), p3.opposite(), p4.opposite() );
            }
            
            else
            {
                return General_Spherical_Cone( s, p1, p2, p3 ) - General_Spherical_Cone( s, p1, p3, p4.opposite() );
            }
        }
        
        else
        {
            if (p5.oriented_side( i2 ) == ON_POSITIVE_SIDE)
            {
                return General_Spherical_Cone( s, p1, p2, p3 ) - General_Spherical_Cone( s, p2, p3, p4.opposite() );
            }
            
            else return General_Spherical_Cone( s, p1, p2, p3 );
        }
    }
    
    else
    {
        if (p5.oriented_side( i1 ) == ON_POSITIVE_SIDE)
        {
            if (p5.oriented_side( i2 ) == ON_POSITIVE_SIDE)
            {
                return Spherical_Cap( s, p4 ) - General_Spherical_Wedge( s, p1.opposite(), p4 ) - General_Spherical_Wedge( s, p2.opposite(), p4 ) - General_Spherical_Wedge( s, p3.opposite(), p4 ) + General_Spherical_Cone( s, p2.opposite(), p3.opposite(), p4 ) + General_Spherical_Cone( s, p1.opposite(), p3.opposite(), p4 );
            }
            
            else return General_Spherical_Cone( s, p1, p3, p4 );
        }
        
        else
        {
            if (p5.oriented_side( i2 ) == ON_POSITIVE_SIDE) return General_Spherical_Cone( s, p2, p3, p4 );
            
            else return 0;
        }
    }
}

double Non_Parallel_Lines_Case ( Sphere const& s, L3 const& l1, L3 const& l2, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3, Pl3 const& p4 )
{
    L3 l3 = Line_Of_Intersection_Of_Two_Planes( p2, p3 );
    
    P3 vertex = Intersection_Of_Two_Lines3D( l1, l2 );
    
    P3 pt1 = vertex + l1.to_vector();
    P3 pt2 = vertex + l2.to_vector();
    P3 pt3 = vertex + l3.to_vector();
    
    if (p3.oriented_side( pt1 ) == ON_NEGATIVE_SIDE) pt1 = vertex - l1.to_vector();
    if (p2.oriented_side( pt2 ) == ON_NEGATIVE_SIDE) pt2 = vertex - l2.to_vector();
    if (p1.oriented_side( pt3 ) == ON_NEGATIVE_SIDE) pt3 = vertex - l3.to_vector();
    
    Pl3 p5( pt1, pt2, pt3 );
    
    if (p5.oriented_side( vertex ) == ON_POSITIVE_SIDE) p5 = p5.opposite();
    
    p5 = Pl3( vertex, p5.orthogonal_vector() );
    
    P3 i1, i2, i3;
    
    bool intersection1 = Intersection_Of_Line_And_Plane( p4, l1, i1 );
    bool intersection2 = Intersection_Of_Line_And_Plane( p4, l2, i2 );
    bool intersection3 = Intersection_Of_Line_And_Plane( p4, l3, i3 );
    
    if (!intersection1) return Fourth_Plane_Parallel_To_Line( s, l1, i2, i3, p1, p2, p3, p4, p5 );
    else if (!intersection2) return Fourth_Plane_Parallel_To_Line( s, l2, i1, i3, p1, p3, p2, p4, p5 );
    else if (!intersection3) return Fourth_Plane_Parallel_To_Line( s, l3, i1, i2, p2, p3, p1, p4, p5 );
    
    else
    {
        if (squared_distance( vertex, p4 ) < tiny_num * 1e7) // Changed for T2 experiment dataset. Changed from 1e6 to 1e7 for T2 Dataset No.313.
        {
            if (p4.oriented_side( pt1 ) == ON_POSITIVE_SIDE)
            {
                if (p4.oriented_side( pt2 ) == ON_POSITIVE_SIDE)
                {
                    if (p4.oriented_side( pt3 ) == ON_POSITIVE_SIDE) return General_Spherical_Cone( s, p1, p2, p3 );
                    
                    else return General_Spherical_Cone( s, p1, p2, p3 ) - General_Spherical_Cone( s, p4.opposite(), p2, p3 );
                }
                
                else
                {
                    if (p4.oriented_side( pt3 ) == ON_POSITIVE_SIDE) return General_Spherical_Cone( s, p1, p2, p3 ) - General_Spherical_Cone( s, p4.opposite(), p1, p3 );
                    
                    else return General_Spherical_Cone( s, p1, p2, p4 );
                }
            }
            
            else
            {
                if (p4.oriented_side( pt2 ) == ON_POSITIVE_SIDE)
                {
                    if (p4.oriented_side( pt3 ) == ON_POSITIVE_SIDE) return General_Spherical_Cone( s, p1, p2, p3 ) - General_Spherical_Cone( s, p4.opposite(), p1, p2 );
                    
                    else return General_Spherical_Cone( s, p1, p3, p4 );
                }
                
                else
                {
                    if (p4.oriented_side( pt3 ) == ON_POSITIVE_SIDE) return General_Spherical_Cone( s, p2, p3, p4 );
                    
                    else return 0;
                }
            }
        }
        
        else if (p4.oriented_side( vertex ) == ON_POSITIVE_SIDE)
        {
            if (p5.oriented_side( i1 ) == ON_POSITIVE_SIDE)
            {
                if (p5.oriented_side( i2 ) == ON_POSITIVE_SIDE)
                {
                    if (p5.oriented_side( i3 ) == ON_POSITIVE_SIDE)
                    {
                        return General_Spherical_Cone( s, p1, p2, p3 ) - Spherical_Cap( s, p4.opposite() ) + General_Spherical_Wedge( s, p1.opposite(), p4.opposite() ) + General_Spherical_Wedge( s, p2.opposite(), p4.opposite() ) + General_Spherical_Wedge( s, p3.opposite(), p4.opposite() ) - General_Spherical_Cone( s, p1.opposite(), p2.opposite(), p4.opposite() ) - General_Spherical_Cone( s, p1.opposite(), p3.opposite(), p4.opposite() ) - General_Spherical_Cone( s, p2.opposite(), p3.opposite(), p4.opposite() );
                    }
                    
                    else
                    {
                        return General_Spherical_Cone( s, p1, p2, p3 ) - Spherical_Cap( s, p4.opposite() ) + General_Spherical_Wedge( s, p1.opposite(), p4.opposite() ) + General_Spherical_Wedge( s, p2.opposite(), p4.opposite() ) + General_Spherical_Wedge( s, p3.opposite(), p4.opposite() ) - General_Spherical_Cone( s, p1.opposite(), p2.opposite(), p4.opposite() ) - General_Spherical_Cone( s, p1.opposite(), p3.opposite(), p4.opposite() );
                    }
                }
                
                else
                {
                    if (p5.oriented_side( i3 ) == ON_POSITIVE_SIDE)
                    {
                        return General_Spherical_Cone( s, p1, p2, p3 ) - Spherical_Cap( s, p4.opposite() ) + General_Spherical_Wedge( s, p1.opposite(), p4.opposite() ) + General_Spherical_Wedge( s, p2.opposite(), p4.opposite() ) + General_Spherical_Wedge( s, p3.opposite(), p4.opposite() ) - General_Spherical_Cone( s, p1.opposite(), p2.opposite(), p4.opposite() ) - General_Spherical_Cone( s, p2.opposite(), p3.opposite(), p4.opposite() );
                    }
                    
                    else return General_Spherical_Cone( s, p1, p2, p3 ) - General_Spherical_Cone( s, p1, p2, p4.opposite() );
                }
            }
            
            else
            {
                if (p5.oriented_side( i2 ) == ON_POSITIVE_SIDE)
                {
                    if (p5.oriented_side( i3 ) == ON_POSITIVE_SIDE)
                    {
                        return General_Spherical_Cone( s, p1, p2, p3 ) - Spherical_Cap( s, p4.opposite() ) + General_Spherical_Wedge( s, p1.opposite(), p4.opposite() ) + General_Spherical_Wedge( s, p2.opposite(), p4.opposite() ) + General_Spherical_Wedge( s, p3.opposite(), p4.opposite() ) - General_Spherical_Cone( s, p1.opposite(), p3.opposite(), p4.opposite() ) - General_Spherical_Cone( s, p2.opposite(), p3.opposite(), p4.opposite() );
                    }
                    
                    else return General_Spherical_Cone( s, p1, p2, p3 ) - General_Spherical_Cone( s, p1, p3, p4.opposite() );
                }
                
                else
                {
                    if (p5.oriented_side( i3 ) == ON_POSITIVE_SIDE)
                    {
                        return General_Spherical_Cone( s, p1, p2, p3 ) - General_Spherical_Cone( s, p2, p3, p4.opposite() );
                    }
                    
                    else return General_Spherical_Cone( s, p1, p2, p3 );
                }
            }
        }
        
        
        else
        {
            if (p5.oriented_side( i1 ) == ON_POSITIVE_SIDE)
            {
                if (p5.oriented_side( i2 ) == ON_POSITIVE_SIDE)
                {
                    if (p5.oriented_side( i3 ) == ON_POSITIVE_SIDE)
                    {
                        return Spherical_Cap( s, p4 ) - General_Spherical_Wedge( s, p1.opposite(), p4 ) - General_Spherical_Wedge( s, p2.opposite(), p4 ) - General_Spherical_Wedge( s, p3.opposite(), p4 ) + General_Spherical_Cone( s, p1.opposite(), p2.opposite(), p4 ) + General_Spherical_Cone( s, p1.opposite(), p3.opposite(), p4 ) + General_Spherical_Cone( s, p2.opposite(), p3.opposite(), p4 );
                    }
                    
                    else
                    {
                        return Spherical_Cap( s, p4 ) - General_Spherical_Wedge( s, p1.opposite(), p4 ) - General_Spherical_Wedge( s, p2.opposite(), p4 ) - General_Spherical_Wedge( s, p3.opposite(), p4 ) + General_Spherical_Cone( s, p1.opposite(), p2.opposite(), p4 ) + General_Spherical_Cone( s, p1.opposite(), p3.opposite(), p4 );
                    }
                }
                
                else
                {
                    if (p5.oriented_side( i3 ) == ON_POSITIVE_SIDE)
                    {
                        return Spherical_Cap( s, p4 ) - General_Spherical_Wedge( s, p1.opposite(), p4 ) - General_Spherical_Wedge( s, p2.opposite(), p4 ) - General_Spherical_Wedge( s, p3.opposite(), p4 ) + General_Spherical_Cone( s, p1.opposite(), p2.opposite(), p4 ) + General_Spherical_Cone( s, p2.opposite(), p3.opposite(), p4 );
                    }
                    
                    else return General_Spherical_Cone( s, p1, p2, p4 );
                }
            }
            
            else
            {
                if (p5.oriented_side( i2 ) == ON_POSITIVE_SIDE)
                {
                    if (p5.oriented_side( i3 ) == ON_POSITIVE_SIDE)
                    {
                        return Spherical_Cap( s, p4 ) - General_Spherical_Wedge( s, p1.opposite(), p4 ) - General_Spherical_Wedge( s, p2.opposite(), p4 ) - General_Spherical_Wedge( s, p3.opposite(), p4 ) + General_Spherical_Cone( s, p1.opposite(), p3.opposite(), p4 ) + General_Spherical_Cone( s, p2.opposite(), p3.opposite(), p4 );
                    }
                    
                    else return General_Spherical_Cone( s, p1, p3, p4 );
                }
                
                else
                {
                    if (p5.oriented_side( i3 ) == ON_POSITIVE_SIDE) return General_Spherical_Cone( s, p2, p3, p4 );
                    
                    else return 0;
                }
            }
        }
    }
}

double Shared_Line( Sphere const& s, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3, Pl3 const& p4 )
{
    double volume = General_Spherical_Cone( s, p1, p2, p3 );
    
    if (volume < tiny_num) return 0;
    
    L3 l = Line_Of_Intersection_Of_Two_Planes( p1, p2 );
    
    if (squared_distance( l.point(), p4 ) < tiny_num)
    {
        double volume_1 = General_Spherical_Cone( s, p1, p2, p3 );
        double volume_2 = General_Spherical_Cone( s, p1, p2, p4 );
        double volume_3 = General_Spherical_Cone( s, p1, p3, p4 );
        
        if (volume_2 < volume_1) volume_1 = volume_2;
        if (volume_3 < volume_1) volume_1 = volume_3;
        
        return volume_1;
    }
    
    else
    {
        L3 l = Line_Of_Intersection_Of_Two_Planes( p1, p2 );
        L3 l1 = Line_Of_Intersection_Of_Two_Planes( p1, p4 );
        L3 l2 = Line_Of_Intersection_Of_Two_Planes( p2, p4 );
        L3 l3 = Line_Of_Intersection_Of_Two_Planes( p3, p4 );
        
        bool i1 = false, i2 = false, i3 = false;
        
        if (p2.oriented_side( l1.point() ) == ON_POSITIVE_SIDE && p3.oriented_side( l1.point() ) == ON_POSITIVE_SIDE) i1 = true;
        if (p1.oriented_side( l2.point() ) == ON_POSITIVE_SIDE && p3.oriented_side( l2.point() ) == ON_POSITIVE_SIDE) i2 = true;
        if (p1.oriented_side( l3.point() ) == ON_POSITIVE_SIDE && p2.oriented_side( l3.point() ) == ON_POSITIVE_SIDE) i3 = true;
        
        int counter = 0;
        
        if (i1) ++counter;
        if (i2) ++counter;
        if (i3) ++counter;
        
        if (counter == 0)
        {
            if (p4.oriented_side( l.point() ) == ON_POSITIVE_SIDE) return volume;
            
            else return 0;
        }
        
        else if (counter == 1)
        {
            if (i1)
            {
                if (p4.oriented_side( l.point() ) == ON_POSITIVE_SIDE) return volume - General_Spherical_Wedge( s, p1, p4.opposite() );
                
                else return General_Spherical_Wedge( s, p1, p4 );
            }
            
            else if (i2)
            {
                if (p4.oriented_side( l.point() ) == ON_POSITIVE_SIDE) return volume - General_Spherical_Wedge( s, p2, p4.opposite() );
                
                else return General_Spherical_Wedge( s, p2, p4 );
            }
            
            else
            {
                if (p4.oriented_side( l.point() ) == ON_POSITIVE_SIDE) return volume - General_Spherical_Wedge( s, p3, p4.opposite() );
                
                else return General_Spherical_Wedge( s, p3, p4 );
            }
        }
        
        else if (counter == 2)
        {
            if (!i1)
            {
                if (p4.oriented_side( l.point() ) == ON_POSITIVE_SIDE) return volume - Spherical_Cap( s, p4.opposite() ) + General_Spherical_Wedge( s, p2.opposite(), p4.opposite() ) + General_Spherical_Wedge( s, p3.opposite(), p4.opposite() );
                
                else return Spherical_Cap( s, p4 ) - General_Spherical_Wedge( s, p2.opposite(), p4 ) - General_Spherical_Wedge( s, p3.opposite(), p4 );
            }
            
            else if (!i2)
            {
                if (p4.oriented_side( l.point() ) == ON_POSITIVE_SIDE) return volume - Spherical_Cap( s, p4.opposite() ) + General_Spherical_Wedge( s, p1.opposite(), p4.opposite() ) + General_Spherical_Wedge( s, p3.opposite(), p4.opposite() );
                
                else return Spherical_Cap( s, p4 ) - General_Spherical_Wedge( s, p1.opposite(), p4 ) - General_Spherical_Wedge( s, p3.opposite(), p4 );
            }
            
            else
            {
                if (p4.oriented_side( l.point() ) == ON_POSITIVE_SIDE) return volume - Spherical_Cap( s, p4.opposite() ) + General_Spherical_Wedge( s, p1.opposite(), p4.opposite() ) + General_Spherical_Wedge( s, p2.opposite(), p4.opposite() );
                
                else return Spherical_Cap( s, p4 ) - General_Spherical_Wedge( s, p1.opposite(), p4 ) - General_Spherical_Wedge( s, p2.opposite(), p4 );
            }
        }
        
        else return 0;
    }
}

double Three_Wedges ( Sphere const& s, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3, Pl3 const& p4 )
{
    L3 l1 = Line_Of_Intersection_Of_Two_Planes( p1, p2 );
    L3 l2 = Line_Of_Intersection_Of_Two_Planes( p1, p3 );
    L3 l3 = Line_Of_Intersection_Of_Two_Planes( p1, p4 );
    L3 l4 = Line_Of_Intersection_Of_Two_Planes( p2, p3 );
    L3 l5 = Line_Of_Intersection_Of_Two_Planes( p2, p4 );
    L3 l6 = Line_Of_Intersection_Of_Two_Planes( p3, p4 );
    
    bool line_1 = false, line_2 = false, line_3 = false, line_4 = false, line_5 = false, line_6 = false;
    
    if (p3.oriented_side( l1.point() ) == ON_POSITIVE_SIDE && p4.oriented_side( l1.point() ) == ON_POSITIVE_SIDE) line_1 = true;
    if (p2.oriented_side( l2.point() ) == ON_POSITIVE_SIDE && p4.oriented_side( l2.point() ) == ON_POSITIVE_SIDE) line_2 = true;
    if (p2.oriented_side( l3.point() ) == ON_POSITIVE_SIDE && p3.oriented_side( l3.point() ) == ON_POSITIVE_SIDE) line_3 = true;
    if (p1.oriented_side( l4.point() ) == ON_POSITIVE_SIDE && p4.oriented_side( l4.point() ) == ON_POSITIVE_SIDE) line_4 = true;
    if (p1.oriented_side( l5.point() ) == ON_POSITIVE_SIDE && p3.oriented_side( l5.point() ) == ON_POSITIVE_SIDE) line_5 = true;
    if (p1.oriented_side( l6.point() ) == ON_POSITIVE_SIDE && p2.oriented_side( l6.point() ) == ON_POSITIVE_SIDE) line_6 = true;
    
    if (line_1)
    {
        if (line_2 || line_3)
        {
            if (line_4 || line_5)
            {
                if (line_2) return General_Spherical_Wedge( s, p1, p2 ) - General_Spherical_Wedge( s, p1, p3.opposite() ) - General_Spherical_Wedge( s, p2, p4.opposite() );
                
                else return General_Spherical_Wedge( s, p1, p2 ) - General_Spherical_Wedge( s, p1, p4.opposite() ) - General_Spherical_Wedge( s, p2, p3.opposite() );
            }
            
            else if (line_2) return General_Spherical_Wedge( s, p1, p3 ) - General_Spherical_Wedge( s, p1, p2.opposite() ) - General_Spherical_Wedge( s, p3, p4.opposite() );
            
            else return General_Spherical_Wedge( s, p1, p4 ) - General_Spherical_Wedge( s, p1, p2.opposite() ) - General_Spherical_Wedge( s, p4, p3.opposite() );
        }
        
        else if (line_4) return General_Spherical_Wedge( s, p2, p3 ) - General_Spherical_Wedge( s, p2, p1.opposite() ) - General_Spherical_Wedge( s, p3, p4.opposite() );
        
        else return General_Spherical_Wedge( s, p2, p4 ) - General_Spherical_Wedge( s, p2, p1.opposite() ) - General_Spherical_Wedge( s, p4, p3.opposite() );
    }
    
    else if (line_2)
    {
        if (line_3)
        {
            if (line_4) return General_Spherical_Wedge( s, p1, p3 ) - General_Spherical_Wedge( s, p3, p2.opposite() ) - General_Spherical_Wedge( s, p1, p4.opposite() );
            
            else return General_Spherical_Wedge( s, p1, p4 ) - General_Spherical_Wedge( s, p1, p3.opposite() ) - General_Spherical_Wedge( s, p4, p2.opposite() );
        }
        
        else if (line_4) return General_Spherical_Wedge( s, p2, p3 ) - General_Spherical_Wedge( s, p3, p1.opposite() ) - General_Spherical_Wedge( s, p2, p4.opposite() );
        
        else return General_Spherical_Wedge( s, p3, p4 ) - General_Spherical_Wedge( s, p3, p1.opposite() ) - General_Spherical_Wedge( s, p4, p2.opposite() );
    }
    
    else
    {
        if (line_5) return General_Spherical_Wedge( s, p2, p4 ) - General_Spherical_Wedge( s, p2, p3.opposite() ) - General_Spherical_Wedge( s, p4, p1.opposite() );
        
        else return General_Spherical_Wedge( s, p3, p4 ) - General_Spherical_Wedge( s, p3, p2.opposite() ) - General_Spherical_Wedge( s, p4, p1.opposite() );
    }
}

double All_Lines_Parallel ( Sphere const& s, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3, Pl3 const& p4 )
{
    L3 l1 = Line_Of_Intersection_Of_Two_Planes( p1, p2 );
    L3 l2 = Line_Of_Intersection_Of_Two_Planes( p1, p3 );
    L3 l3 = Line_Of_Intersection_Of_Two_Planes( p1, p4 );
    L3 l4 = Line_Of_Intersection_Of_Two_Planes( p2, p3 );
    L3 l5 = Line_Of_Intersection_Of_Two_Planes( p2, p4 );
    L3 l6 = Line_Of_Intersection_Of_Two_Planes( p3, p4 );
    
    if (squared_distance( l1.point(), p3 ) < tiny_num) return Shared_Line( s, p1, p2, p3, p4 );
    else if (squared_distance( l1.point(), p4 ) < tiny_num) return Shared_Line( s, p1, p2, p4, p3 );
    else if (squared_distance( l6.point(), p1 ) < tiny_num) return Shared_Line( s, p1, p3, p4, p2 );
    else if (squared_distance( l6.point(), p2 ) < tiny_num) return Shared_Line( s, p2, p3, p4, p1 );
    
    else if (p4.oriented_side( l1.point() ) == ON_POSITIVE_SIDE && p1.oriented_side( l5.point() ) == ON_NEGATIVE_SIDE && p2.oriented_side( l3.point() ) == ON_NEGATIVE_SIDE) return General_Spherical_Cone( s, p1, p2, p3 );
    else if (p4.oriented_side( l2.point() ) == ON_POSITIVE_SIDE && p1.oriented_side( l6.point() ) == ON_NEGATIVE_SIDE && p3.oriented_side( l3.point() ) == ON_NEGATIVE_SIDE) return General_Spherical_Cone( s, p1, p2, p3 );
    else if (p4.oriented_side( l4.point() ) == ON_POSITIVE_SIDE && p2.oriented_side( l6.point() ) == ON_NEGATIVE_SIDE && p3.oriented_side( l5.point() ) == ON_NEGATIVE_SIDE) return General_Spherical_Cone( s, p1, p2, p3 );
    
    else if (p3.oriented_side( l1.point() ) == ON_POSITIVE_SIDE && p1.oriented_side( l4.point() ) == ON_NEGATIVE_SIDE && p2.oriented_side( l2.point() ) == ON_NEGATIVE_SIDE) return General_Spherical_Cone( s, p1, p2, p4 );
    else if (p3.oriented_side( l3.point() ) == ON_POSITIVE_SIDE && p1.oriented_side( l6.point() ) == ON_NEGATIVE_SIDE && p4.oriented_side( l2.point() ) == ON_NEGATIVE_SIDE) return General_Spherical_Cone( s, p1, p2, p4 );
    else if (p3.oriented_side( l5.point() ) == ON_POSITIVE_SIDE && p2.oriented_side( l6.point() ) == ON_NEGATIVE_SIDE && p4.oriented_side( l4.point() ) == ON_NEGATIVE_SIDE) return General_Spherical_Cone( s, p1, p2, p4 );
    
    else if (p2.oriented_side( l2.point() ) == ON_POSITIVE_SIDE && p1.oriented_side( l4.point() ) == ON_NEGATIVE_SIDE && p3.oriented_side( l1.point() ) == ON_NEGATIVE_SIDE) return General_Spherical_Cone( s, p1, p3, p4 );
    else if (p2.oriented_side( l3.point() ) == ON_POSITIVE_SIDE && p1.oriented_side( l5.point() ) == ON_NEGATIVE_SIDE && p4.oriented_side( l1.point() ) == ON_NEGATIVE_SIDE) return General_Spherical_Cone( s, p1, p3, p4 );
    else if (p2.oriented_side( l6.point() ) == ON_POSITIVE_SIDE && p3.oriented_side( l5.point() ) == ON_NEGATIVE_SIDE && p4.oriented_side( l4.point() ) == ON_NEGATIVE_SIDE) return General_Spherical_Cone( s, p1, p3, p4 );
    
    else if (p1.oriented_side( l4.point() ) == ON_POSITIVE_SIDE && p2.oriented_side( l2.point() ) == ON_NEGATIVE_SIDE && p3.oriented_side( l1.point() ) == ON_NEGATIVE_SIDE) return General_Spherical_Cone( s, p2, p3, p4 );
    else if (p1.oriented_side( l5.point() ) == ON_POSITIVE_SIDE && p2.oriented_side( l3.point() ) == ON_NEGATIVE_SIDE && p4.oriented_side( l1.point() ) == ON_NEGATIVE_SIDE) return General_Spherical_Cone( s, p2, p3, p4 );
    else if (p1.oriented_side( l6.point() ) == ON_POSITIVE_SIDE && p3.oriented_side( l3.point() ) == ON_NEGATIVE_SIDE && p4.oriented_side( l2.point() ) == ON_NEGATIVE_SIDE) return General_Spherical_Cone( s, p2, p3, p4 );
    
    else return Three_Wedges( s, p1, p2, p3, p4 );
}

double Sphere_Four_Plane_Intersection_Volume ( Sphere const& s, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3, Pl3 const& p4 )
{
    if (Parallel_Planes( p1, p2 ) || Parallel_Planes( p1, p3 ) || Parallel_Planes( p1, p4 ) || Parallel_Planes( p2, p3 ) || Parallel_Planes( p2, p4 ) || Parallel_Planes( p3, p4 ))
    {
        if (Parallel_Planes( p1, p2 )) return Parallel_Planes_Case( s, p1, p2, p3, p4 );
        else if (Parallel_Planes( p1, p3 )) return Parallel_Planes_Case( s, p1, p3, p2, p4 );
        else if (Parallel_Planes( p1, p4 )) return Parallel_Planes_Case( s, p1, p4, p2, p3 );
        else if (Parallel_Planes( p2, p3 )) return Parallel_Planes_Case( s, p2, p3, p1, p4 );
        else if (Parallel_Planes( p2, p4 )) return Parallel_Planes_Case( s, p2, p4, p1, p3 );
        else return Parallel_Planes_Case( s, p3, p4, p1, p2 );
    }
    
    else
    {
        L3 l1 = Line_Of_Intersection_Of_Two_Planes( p1, p2 );
        L3 l2 = Line_Of_Intersection_Of_Two_Planes( p1, p3 );
        L3 l3 = Line_Of_Intersection_Of_Two_Planes( p1, p4 );
        
        if (!Parallel_Lines( l1, l2 )) return Non_Parallel_Lines_Case( s, l1, l2, p1, p2, p3, p4 );
        else if (!Parallel_Lines( l1, l3 )) return Non_Parallel_Lines_Case( s, l1, l3, p1, p2, p4, p3 );
        
        else return All_Lines_Parallel( s, p1, p2, p3, p4 );
    }
}
