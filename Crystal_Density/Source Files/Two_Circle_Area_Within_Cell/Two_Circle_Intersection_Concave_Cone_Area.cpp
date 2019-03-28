#include "Cell_2Circles.h"
#include "Same_Side.h"
#include "Concave_Cone_Area.h"

double Two_Circle_Intersection_Concave_Cone_Area ( Cell_2Circles const& c2c, Edge const& e1, Edge const& e2, Edge const& e3, Edge const& e4 )
{
    Circle c1 = c2c.tc.c[0], c2 = c2c.tc.c[1];
    
    P2 v, i1, i2;
    
    if (Norm( e1.startpt, c1.c ) > c1.r + tiny_num || Norm( e1.startpt, c2.c ) > c2.r + tiny_num)
    {
        v = e1.startpt;
    }
    
    else v = e1.endpt;
    
    int t1, t2;
    
    if (e1.intersection_type != 1 && Norm( e1.i1, c2.c ) < c2.r - tiny_num)
    {
        i1 = e1.i1;
        t1 = 1;
    }
    
    else if (e2.intersection_type != 1 && Norm( e2.i1, c1.c ) < c1.r - tiny_num)
    {
        i1 = e2.i1;
        t1 = 2;
    }
    
    else
    {
        i1 = e1.i1;
        t1 = 3;
    }
    
    if (e3.intersection_type != 1 && Norm( e3.i1, c2.c ) < c2.r - tiny_num)
    {
        i2 = e3.i1;
        t2 = 1;
    }
    
    else if (e4.intersection_type != 1 && Norm( e4.i1, c1.c ) < c1.r - tiny_num)
    {
        i2 = e4.i1;
        t2 = 2;
    }
    
    else
    {
        i2 = e3.i1;
        t2 = 3;
    }
    
    if (t1 == 3)
    {
        if (t2 == 1)
        {
            return Concave_Cone_Area( c1, e1, e3 );
        }
        
        else return Concave_Cone_Area( c2, e2, e4 );
    }
    
    else if (t2 == 3)
    {
        if (t1 == 1)
        {
            return Concave_Cone_Area( c1, e1, e3 );
        }
        
        else return Concave_Cone_Area( c2, e2, e4 );
    }
    
    else if (t1 == t2)
    {
        if (t1 == 1)
        {
            return Concave_Cone_Area( c1, e1, e3 );
        }
        
        else return Concave_Cone_Area( c2, e2, e4 );
    }
    
    else
    {
        P2 i3, j1 = c2c.tc.i1, j2 = c2c.tc.i2;
        
        L2 l( i1, i2 );
        
        if (Same_Side( l, j1, v )) i3 = j1;
        else i3 = j2;
        
        Edge e( L2( v, i3 ), v, i3, 0 );
        
        if (t1 == 1) return Concave_Cone_Area( c1, e1, e ) + Concave_Cone_Area( c2, e4, e );
        
        else return Concave_Cone_Area( c1, e3, e ) + Concave_Cone_Area( c2, e2, e );
    }
}
