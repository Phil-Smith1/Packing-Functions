#include "General_Spherical_Wedge.h"

double Cone_Shared_Line_Orthogonal_Planes ( Sphere const& s, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3, P3 const& pt, P3 const& i1, P3 const& i2 )
{
    if (p1.oriented_side( pt ) == ON_POSITIVE_SIDE)
    {
        if (p3.oriented_side( i2 ) == ON_POSITIVE_SIDE)
        {
            if (p2.oriented_side( pt ) == ON_POSITIVE_SIDE) return General_Spherical_Wedge( s, p2, p3 );
            
            else return General_Spherical_Wedge( s, p1, p2 );
        }
        
        else
        {
            if (p2.oriented_side( pt ) == ON_POSITIVE_SIDE) return General_Spherical_Wedge( s, p1, p3 );
            
            else return 0;
        }
    }
    
    else
    {
        if (p3.oriented_side( i2 ) == ON_POSITIVE_SIDE)
        {
            if (p2.oriented_side( pt ) == ON_POSITIVE_SIDE) return 0;
            
            else return General_Spherical_Wedge( s, p1, p3 );
        }
        
        else
        {
            if (p2.oriented_side( pt ) == ON_POSITIVE_SIDE) return General_Spherical_Wedge( s, p1, p2 );
            
            else return General_Spherical_Wedge( s, p2, p3 );
        }
    }
}

double Cone_Shared_Line ( Sphere const& s, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3, P3 const& pt, P3 const& i1, P3 const& i2 )
{
    if (p3.oriented_side( i1 ) == ON_POSITIVE_SIDE)
    {
        if (p3.oriented_side( i2 ) == ON_POSITIVE_SIDE)
        {
            if (p1.oriented_side( pt ) == ON_POSITIVE_SIDE)
            {
                if (p2.oriented_side( pt ) == ON_POSITIVE_SIDE)
                {
                    if (p1.oriented_side( i2 ) == ON_POSITIVE_SIDE) return General_Spherical_Wedge( s, p2, p3 );
                    
                    else return General_Spherical_Wedge( s, p1, p3 );
                }
                
                else
                {
                    if (p1.oriented_side( i2 ) == ON_POSITIVE_SIDE) return General_Spherical_Wedge( s, p1, p2 );
                    
                    else return 0;
                }
            }
            
            else
            {
                if (p2.oriented_side( pt ) == ON_POSITIVE_SIDE)
                {
                    if (p1.oriented_side( i2 ) == ON_POSITIVE_SIDE) return General_Spherical_Wedge( s, p1, p2 );
                    
                    else return 0;
                }
                
                else
                {
                    if (p1.oriented_side( i2 ) == ON_POSITIVE_SIDE) return General_Spherical_Wedge( s, p2, p3 );
                    
                    else return General_Spherical_Wedge( s, p1, p3 );
                }
            }
        }
        
        else
        {
            if (p1.oriented_side( pt ) == ON_POSITIVE_SIDE)
            {
                if (p2.oriented_side( pt ) == ON_POSITIVE_SIDE) return General_Spherical_Wedge( s, p1, p3 );
                
                else return 0;
            }
            
            else
            {
                if (p2.oriented_side( pt ) == ON_POSITIVE_SIDE) return General_Spherical_Wedge( s, p1, p2 );
                
                else return General_Spherical_Wedge( s, p2, p3 );
            }
        }
    }
    
    else
    {
        if (p3.oriented_side( i2 ) == ON_POSITIVE_SIDE)
        {
            if (p1.oriented_side( pt ) == ON_POSITIVE_SIDE)
            {
                if (p2.oriented_side( pt ) == ON_POSITIVE_SIDE) return General_Spherical_Wedge( s, p2, p3 );
                
                else return General_Spherical_Wedge( s, p1, p2 );
            }
            
            else
            {
                if (p2.oriented_side( pt ) == ON_POSITIVE_SIDE) return 0;
                
                else return General_Spherical_Wedge( s, p1, p3 );
            }
        }
        
        else
        {
            if (p1.oriented_side( pt ) == ON_POSITIVE_SIDE)
            {
                if (p2.oriented_side( pt ) == ON_POSITIVE_SIDE)
                {
                    if (p1.oriented_side( i2 ) == ON_POSITIVE_SIDE) return General_Spherical_Wedge( s, p1, p3 );
                    
                    else return General_Spherical_Wedge( s, p2, p3 );
                }
                
                else
                {
                    if (p1.oriented_side( i2 ) == ON_POSITIVE_SIDE) return 0;
                    
                    else return General_Spherical_Wedge( s, p1, p2 );
                }
            }
            
            else
            {
                if (p2.oriented_side( pt ) == ON_POSITIVE_SIDE)
                {
                    if (p1.oriented_side( i2 ) == ON_POSITIVE_SIDE) return 0;
                    
                    else return General_Spherical_Wedge( s, p1, p2 );
                }
                
                else
                {
                    if (p1.oriented_side( i2 ) == ON_POSITIVE_SIDE) return General_Spherical_Wedge( s, p1, p3 );
                    
                    else return General_Spherical_Wedge( s, p2, p3 );
                }
            }
        }
    }
}

double Cone_Parallel_Lines ( Sphere const& s, L3 const& l3, L3 const& l2, Pl3 const& p1, Pl3 const& p2, Pl3 const& p3 )
{
    if (squared_distance( l3.point(), p3 ) < tiny_num)
    {
        P3 pt = p3.point();
        
        if (squared_distance( pt, l3 ) < tiny_num) pt += p3.base1();
        if (squared_distance( pt, l3 ) < tiny_num) pt += p3.base2();
        
        L3 l4( pt, p3.orthogonal_vector() );
        
        bool intersection1, intersection2;
        P3 i1, i2;
        
        intersection1 = Intersection_Of_Line_And_Plane( p1, l4, i1 );
        intersection2 = Intersection_Of_Line_And_Plane( p2, l4, i2 );
        
        if (!intersection1) return Cone_Shared_Line_Orthogonal_Planes( s, p1, p2, p3, pt, i1, i2 );
        
        else if (!intersection2) return Cone_Shared_Line_Orthogonal_Planes( s, p2, p1, p3, pt, i2, i1 );
        
        else return Cone_Shared_Line( s, p1, p2, p3, pt, i1, i2 );
    }
    
    L3 l1 = Line_Of_Intersection_Of_Two_Planes( p2, p3 );
    
    if (p3.oriented_side( l3.point() ) == ON_NEGATIVE_SIDE)
    {
        if (p2.oriented_side( l2.point() ) == ON_NEGATIVE_SIDE)
        {
            if (p1.oriented_side( l1.point() ) == ON_NEGATIVE_SIDE) return 0;
            
            else return General_Spherical_Wedge( s, p2, p3 );
        }
        
        else
        {
            if (p1.oriented_side( l1.point() ) == ON_NEGATIVE_SIDE) return General_Spherical_Wedge( s, p1, p3 );
            
            else return Spherical_Cap( s, p3 ) - General_Spherical_Wedge( s, p1.opposite(), p3 ) - General_Spherical_Wedge( s, p2.opposite(), p3 );
        }
    }
    
    else
    {
        if (p2.oriented_side( l2.point() ) == ON_NEGATIVE_SIDE)
        {
            if (p1.oriented_side( l1.point() ) == ON_NEGATIVE_SIDE) return General_Spherical_Wedge( s, p1, p2 );
            
            else return Spherical_Cap( s, p2 ) - General_Spherical_Wedge( s, p1.opposite(), p2 ) - General_Spherical_Wedge( s, p2, p3.opposite() );
        }
        
        else
        {
            if (p1.oriented_side( l1.point() ) == ON_NEGATIVE_SIDE) return Spherical_Cap( s, p1 ) - General_Spherical_Wedge( s, p1, p2.opposite() ) - General_Spherical_Wedge( s, p1, p3.opposite() );
            
            else return s.vol - Spherical_Cap( s, p1.opposite() ) - Spherical_Cap( s, p2.opposite() ) - Spherical_Cap( s, p3.opposite() ) + General_Spherical_Wedge( s, p1.opposite(), p2.opposite() ) + General_Spherical_Wedge( s, p1.opposite(), p3.opposite() ) + General_Spherical_Wedge( s, p2.opposite(), p3.opposite() );
        }
    }
}
