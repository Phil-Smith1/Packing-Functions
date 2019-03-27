#include "Same_Side.h"
#include "Concave_Cone_Area.h"
#include "Cell_3Circles.h"

double Three_Circle_Intersection_Concave_Cone_Area ( Circle const& c1, Circle const& c2, Circle const& c3, Edge const& e1, Edge const& e2, Edge const& e3, Edge const& e4, Edge const& e5, Edge const& e6 )
{
    P2 v, i1, i2;
    
    if (Norm( e1.startpt, c1.c ) > c1.r + tiny_num || Norm( e1.startpt, c2.c ) > c2.r + tiny_num || Norm( e1.startpt, c3.c ) > c3.r + tiny_num )
    {
        v = e1.startpt;
    }
    
    else v = e1.endpt;
    
    int t1, t2;
    
    if (e1.intersection_type != 1 && Norm( e1.i1, c2.c ) < c2.r - tiny_num && Norm( e1.i1, c3.c ) < c3.r - tiny_num)
    {
        i1 = e1.i1;
        t1 = 1;
    }
    
    else if (e2.intersection_type != 1 && Norm( e2.i1, c1.c ) < c1.r - tiny_num && Norm( e2.i1, c3.c ) < c3.r - tiny_num)
    {
        i1 = e2.i1;
        t1 = 2;
    }
    
    else if (e3.intersection_type != 1 && Norm( e3.i1, c1.c ) < c1.r - tiny_num && Norm( e3.i1, c2.c ) < c2.r - tiny_num)
    {
        i1 = e3.i1;
        t1 = 3;
    }
    
    else if (e2.intersection_type != 1 && Norm( e2.i1, c1.c ) < c1.r - tiny_num)
    {
        i1 = e2.i1;
        t1 = 4;
    }
    
    else if (e1.intersection_type != 1 && Norm( e1.i1, c2.c ) < c2.r - tiny_num)
    {
        i1 = e1.i1;
        t1 = 5;
    }
    
    else
    {
        i1 = e1.i1;
        t1 = 6;
    }
    
    if (e4.intersection_type != 1 && Norm( e4.i1, c2.c ) < c2.r - tiny_num && Norm( e4.i1, c3.c ) < c3.r - tiny_num)
    {
        i2 = e4.i1;
        t2 = 1;
    }
    
    else if (e5.intersection_type != 1 && Norm( e5.i1, c1.c ) < c1.r - tiny_num && Norm( e5.i1, c3.c ) < c3.r - tiny_num)
    {
        i2 = e5.i1;
        t2 = 2;
    }
    
    else if (e6.intersection_type != 1 && Norm( e6.i1, c1.c ) < c1.r - tiny_num && Norm( e6.i1, c2.c ) < c2.r - tiny_num)
    {
        i2 = e6.i1;
        t2 = 3;
    }
    
    else if (e5.intersection_type != 1 && Norm( e5.i1, c1.c ) < c1.r - tiny_num)
    {
        i2 = e5.i1;
        t2 = 4;
    }
    
    else if (e4.intersection_type != 1 && Norm( e4.i1, c2.c ) < c2.r - tiny_num)
    {
        i2 = e4.i1;
        t2 = 5;
    }
    
    else
    {
        i2 = e4.i1;
        t2 = 6;
    }
    
    if ((t1 == 4 && t2 == 5) || (t1 == 5 && t2 == 4)) return Concave_Cone_Area( c3, e3, e6 );
    
    else if ((t1 == 4 && t2 == 6) || (t1 == 6 && t2 == 4)) return Concave_Cone_Area( c2, e2, e5 );
    
    else if ((t1 == 5 && t2 == 6) || (t1 == 6 && t2 == 5)) return Concave_Cone_Area( c1, e1, e4 );
    
    else if ((t1 == 4 && t2 == 2) || (t1 == 2 && t2 == 4)) return Concave_Cone_Area( c2, e2, e5 );
    
    else if ((t1 == 4 && t2 == 3) || (t1 == 3 && t2 == 4)) return Concave_Cone_Area( c3, e3, e6 );
    
    else if ((t1 == 4 && t2 == 1) || (t1 == 1 && t2 == 4))
    {
        P2 i3, j1, j2;
        
        Intersection_Of_Two_Circles( c1, c2, j1, j2 );
        
        L2 l( i1, i2 );
        
        if (Same_Side( l, j1, v )) i3 = j1;
        else i3 = j2;
        
        Edge e( L2( v, i3 ), v, i3, 0 );
        
        if (t1 == 1) return Concave_Cone_Area( c1, e1, e ) + Concave_Cone_Area( c2, e5, e );
        
        else return Concave_Cone_Area( c1, e4, e ) + Concave_Cone_Area( c2, e2, e );
    }
    
    else if ((t1 == 5 && t2 == 1) || (t1 == 1 && t2 == 5)) return Concave_Cone_Area( c1, e1, e4 );
    
    else if ((t1 == 5 && t2 == 3) || (t1 == 3 && t2 == 5)) return Concave_Cone_Area( c3, e3, e6 );
    
    else if ((t1 == 5 && t2 == 2) || (t1 == 2 && t2 == 5))
    {
        P2 i3, j1, j2;
        
        Intersection_Of_Two_Circles( c1, c2, j1, j2 );
        
        L2 l( i1, i2 );
        
        if (Same_Side( l, j1, v )) i3 = j1;
        else i3 = j2;
        
        Edge e( L2( v, i3 ), v, i3, 0 );
        
        if (t1 == 2) return Concave_Cone_Area( c2, e2, e ) + Concave_Cone_Area( c1, e4, e );
        
        else return Concave_Cone_Area( c2, e5, e ) + Concave_Cone_Area( c1, e1, e );
    }
    
    else if ((t1 == 6 && t2 == 1) || (t1 == 1 && t2 == 6)) return Concave_Cone_Area( c1, e1, e4 );
    
    else if ((t1 == 6 && t2 == 2) || (t1 == 2 && t2 == 6)) return Concave_Cone_Area( c2, e2, e5 );
    
    else if ((t1 == 6 && t2 == 3) || (t1 == 3 && t2 == 6))
    {
        P2 i3, j1, j2;
        
        Intersection_Of_Two_Circles( c1, c3, j1, j2 );
        
        L2 l( i1, i2 );
        
        if (Same_Side( l, j1, v )) i3 = j1;
        else i3 = j2;
        
        Edge e( L2( v, i3 ), v, i3, 0 );
        
        if (t1 == 3) return Concave_Cone_Area( c3, e3, e ) + Concave_Cone_Area( c1, e4, e );
        
        else return Concave_Cone_Area( c3, e6, e ) + Concave_Cone_Area( c1, e1, e );
    }
    
    else if (t1 == t2)
    {
        if (t1 == 1) return Concave_Cone_Area( c1, e1, e4 );
        
        else if (t1 == 2) return Concave_Cone_Area( c2, e2, e5 );
        
        else return Concave_Cone_Area( c3, e3, e6 );
    }
    
    else if ((t1 == 1 && t2 == 2) || (t1 == 2 && t2 == 1))
    {
        P2 i3, j1, j2;
        
        Intersection_Of_Two_Circles( c1, c2, j1, j2 );
        
        L2 l( i1, i2 );
        
        if (Same_Side( l, j1, v )) i3 = j1;
        else i3 = j2;
        
        Edge e( L2( v, i3 ), v, i3, 0 );
        
        if (t1 == 1) return Concave_Cone_Area( c1, e1, e ) + Concave_Cone_Area( c2, e5, e );
        
        else return Concave_Cone_Area( c1, e4, e ) + Concave_Cone_Area( c2, e2, e );
    }
    
    else if ((t1 == 1 && t2 == 3) || (t1 == 3 && t2 == 1))
    {
        P2 i3, j1, j2;
        
        Intersection_Of_Two_Circles( c1, c3, j1, j2 );
        
        L2 l( i1, i2 );
        
        if (Same_Side( l, j1, v )) i3 = j1;
        else i3 = j2;
        
        Edge e( L2( v, i3 ), v, i3, 0 );
        
        if (t1 == 1) return Concave_Cone_Area( c1, e1, e ) + Concave_Cone_Area( c3, e6, e );
        
        else return Concave_Cone_Area( c1, e4, e ) + Concave_Cone_Area( c3, e3, e );
    }
    
    else
    {
        P2 i3, j1, j2;
        
        Intersection_Of_Two_Circles( c2, c3, j1, j2 );
        
        L2 l( i1, i2 );
        
        if (Same_Side( l, j1, v )) i3 = j1;
        else i3 = j2;
        
        Edge e( L2( v, i3 ), v, i3, 0 );
        
        if (t1 == 2) return Concave_Cone_Area( c2, e2, e ) + Concave_Cone_Area( c3, e6, e );
        
        else return Concave_Cone_Area( c2, e5, e ) + Concave_Cone_Area( c3, e3, e );
    }
}

double Three_Circle_Intersection_Concave_Cone_Area ( Cell_3Circles const& c3c, Edge const& e1, Edge const& e2, Edge const& e3, Edge const& e4, Edge const& e5, Edge const& e6 )
{
    Circle c1 = c3c.thc.c[0], c2 = c3c.thc.c[1], c3 = c3c.thc.c[2];
    
    P2 v, i1, i2;
    
    if (Norm( e1.startpt, c1.c ) > c1.r + tiny_num || Norm( e1.startpt, c2.c ) > c2.r + tiny_num || Norm( e1.startpt, c3.c ) > c3.r + tiny_num )
    {
        v = e1.startpt;
    }
    
    else v = e1.endpt;
    
    int t1, t2;
    
    if (e1.intersection_type != 1 && Norm( e1.i1, c2.c ) < c2.r - tiny_num && Norm( e1.i1, c3.c ) < c3.r - tiny_num)
    {
        i1 = e1.i1;
        t1 = 1;
    }
    
    else if (e2.intersection_type != 1 && Norm( e2.i1, c1.c ) < c1.r - tiny_num && Norm( e2.i1, c3.c ) < c3.r - tiny_num)
    {
        i1 = e2.i1;
        t1 = 2;
    }
    
    else if (e3.intersection_type != 1 && Norm( e3.i1, c1.c ) < c1.r - tiny_num && Norm( e3.i1, c2.c ) < c2.r - tiny_num)
    {
        i1 = e3.i1;
        t1 = 3;
    }
    
    else if (e2.intersection_type != 1 && Norm( e2.i1, c1.c ) < c1.r - tiny_num)
    {
        i1 = e2.i1;
        t1 = 4;
    }
    
    else if (e1.intersection_type != 1 && Norm( e1.i1, c2.c ) < c2.r - tiny_num)
    {
        i1 = e1.i1;
        t1 = 5;
    }
    
    else
    {
        i1 = e1.i1;
        t1 = 6;
    }
    
    if (e4.intersection_type != 1 && Norm( e4.i1, c2.c ) < c2.r - tiny_num && Norm( e4.i1, c3.c ) < c3.r - tiny_num)
    {
        i2 = e4.i1;
        t2 = 1;
    }
    
    else if (e5.intersection_type != 1 && Norm( e5.i1, c1.c ) < c1.r - tiny_num && Norm( e5.i1, c3.c ) < c3.r - tiny_num)
    {
        i2 = e5.i1;
        t2 = 2;
    }
    
    else if (e6.intersection_type != 1 && Norm( e6.i1, c1.c ) < c1.r - tiny_num && Norm( e6.i1, c2.c ) < c2.r - tiny_num)
    {
        i2 = e6.i1;
        t2 = 3;
    }
    
    else if (e5.intersection_type != 1 && Norm( e5.i1, c1.c ) < c1.r - tiny_num)
    {
        i2 = e5.i1;
        t2 = 4;
    }
    
    else if (e4.intersection_type != 1 && Norm( e4.i1, c2.c ) < c2.r - tiny_num)
    {
        i2 = e4.i1;
        t2 = 5;
    }
    
    else
    {
        i2 = e4.i1;
        t2 = 6;
    }
    
    if ((t1 == 4 && t2 == 5) || (t1 == 5 && t2 == 4)) return Concave_Cone_Area( c3, e3, e6 );
    
    else if ((t1 == 4 && t2 == 6) || (t1 == 6 && t2 == 4)) return Concave_Cone_Area( c2, e2, e5 );
    
    else if ((t1 == 5 && t2 == 6) || (t1 == 6 && t2 == 5)) return Concave_Cone_Area( c1, e1, e4 );
    
    else if ((t1 == 4 && t2 == 2) || (t1 == 2 && t2 == 4)) return Concave_Cone_Area( c2, e2, e5 );
    
    else if ((t1 == 4 && t2 == 3) || (t1 == 3 && t2 == 4)) return Concave_Cone_Area( c3, e3, e6 );
    
    else if ((t1 == 4 && t2 == 1) || (t1 == 1 && t2 == 4))
    {
        P2 i3, j1 = c3c.c2c[0].tc.i1, j2 = c3c.c2c[0].tc.i2;
        
        L2 l( i1, i2 );
        
        if (Same_Side( l, j1, v )) i3 = j1;
        else i3 = j2;
        
        Edge e( L2( v, i3 ), v, i3, 0 );
        
        if (t1 == 1) return Concave_Cone_Area( c1, e1, e ) + Concave_Cone_Area( c2, e5, e );
        
        else return Concave_Cone_Area( c1, e4, e ) + Concave_Cone_Area( c2, e2, e );
    }
    
    else if ((t1 == 5 && t2 == 1) || (t1 == 1 && t2 == 5)) return Concave_Cone_Area( c1, e1, e4 );
    
    else if ((t1 == 5 && t2 == 3) || (t1 == 3 && t2 == 5)) return Concave_Cone_Area( c3, e3, e6 );
    
    else if ((t1 == 5 && t2 == 2) || (t1 == 2 && t2 == 5))
    {
        P2 i3, j1 = c3c.c2c[0].tc.i1, j2 = c3c.c2c[0].tc.i2;
        
        L2 l( i1, i2 );
        
        if (Same_Side( l, j1, v )) i3 = j1;
        else i3 = j2;
        
        Edge e( L2( v, i3 ), v, i3, 0 );
        
        if (t1 == 2) return Concave_Cone_Area( c2, e2, e ) + Concave_Cone_Area( c1, e4, e );
        
        else return Concave_Cone_Area( c2, e5, e ) + Concave_Cone_Area( c1, e1, e );
    }
    
    else if ((t1 == 6 && t2 == 1) || (t1 == 1 && t2 == 6)) return Concave_Cone_Area( c1, e1, e4 );
    
    else if ((t1 == 6 && t2 == 2) || (t1 == 2 && t2 == 6)) return Concave_Cone_Area( c2, e2, e5 );
    
    else if ((t1 == 6 && t2 == 3) || (t1 == 3 && t2 == 6))
    {
        P2 i3, j1 = c3c.c2c[1].tc.i1, j2 = c3c.c2c[1].tc.i2;
        
        L2 l( i1, i2 );
        
        if (Same_Side( l, j1, v )) i3 = j1;
        else i3 = j2;
        
        Edge e( L2( v, i3 ), v, i3, 0 );
        
        if (t1 == 3) return Concave_Cone_Area( c3, e3, e ) + Concave_Cone_Area( c1, e4, e );
        
        else return Concave_Cone_Area( c3, e6, e ) + Concave_Cone_Area( c1, e1, e );
    }
    
    else if (t1 == t2)
    {
        if (t1 == 1) return Concave_Cone_Area( c1, e1, e4 );
        
        else if (t1 == 2) return Concave_Cone_Area( c2, e2, e5 );
        
        else return Concave_Cone_Area( c3, e3, e6 );
    }
    
    else if ((t1 == 1 && t2 == 2) || (t1 == 2 && t2 == 1))
    {
        P2 i3, j1 = c3c.c2c[0].tc.i1, j2 = c3c.c2c[0].tc.i2;
        
        L2 l( i1, i2 );
        
        if (Same_Side( l, j1, v )) i3 = j1;
        else i3 = j2;
        
        Edge e( L2( v, i3 ), v, i3, 0 );
        
        if (t1 == 1) return Concave_Cone_Area( c1, e1, e ) + Concave_Cone_Area( c2, e5, e );
        
        else return Concave_Cone_Area( c1, e4, e ) + Concave_Cone_Area( c2, e2, e );
    }
    
    else if ((t1 == 1 && t2 == 3) || (t1 == 3 && t2 == 1))
    {
        P2 i3, j1 = c3c.c2c[1].tc.i1, j2 = c3c.c2c[1].tc.i2;
        
        L2 l( i1, i2 );
        
        if (Same_Side( l, j1, v )) i3 = j1;
        else i3 = j2;
        
        Edge e( L2( v, i3 ), v, i3, 0 );
        
        if (t1 == 1) return Concave_Cone_Area( c1, e1, e ) + Concave_Cone_Area( c3, e6, e );
        
        else return Concave_Cone_Area( c1, e4, e ) + Concave_Cone_Area( c3, e3, e );
    }
    
    else
    {
        P2 i3, j1 = c3c.c2c[2].tc.i1, j2 = c3c.c2c[2].tc.i2;
        
        L2 l( i1, i2 );
        
        if (Same_Side( l, j1, v )) i3 = j1;
        else i3 = j2;
        
        Edge e( L2( v, i3 ), v, i3, 0 );
        
        if (t1 == 2) return Concave_Cone_Area( c2, e2, e ) + Concave_Cone_Area( c3, e6, e );
        
        else return Concave_Cone_Area( c2, e5, e ) + Concave_Cone_Area( c3, e3, e );
    }
}
