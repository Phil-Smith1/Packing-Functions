#include "Intersection_Of_Two_Circles.h"

using namespace std;

void Non_Trivial_Four_Circle_Intersection_Pts ( Circle const& c1, Circle const& c2, Circle const& c3, Circle const& c4, P2& i1, P2& i2, P2& i3, P2& i4, vector<int>& arc_order )
{
    P2 p1, p2;
    vector<int> c2_arc, c3_arc, c4_arc;
    vector<P2> i;
    
    Intersection_Of_Two_Circles( c1, c2, p1, p2 );
    
    if (Norm( c3.c, p1 ) < c3.r && Norm( c4.c, p1 ) < c4.r)
    {
        i.push_back( p1 );
        c2_arc.push_back( (int)i.size() - 1 );
    }
    
    else if (Norm( c3.c, p2 ) < c3.r && Norm( c4.c, p2 ) < c4.r)
    {
        i.push_back( p2 );
        c2_arc.push_back( (int)i.size() - 1 );
    }
    
    Intersection_Of_Two_Circles( c1, c3, p1, p2 );
    
    if (Norm( c2.c, p1 ) < c2.r && Norm( c4.c, p1 ) < c4.r)
    {
        i.push_back( p1 );
        c3_arc.push_back( (int)i.size() - 1 );
    }
    
    else if (Norm( c2.c, p2 ) < c2.r && Norm( c4.c, p2 ) < c4.r)
    {
        i.push_back( p2 );
        c3_arc.push_back( (int)i.size() - 1 );
    }
    
    Intersection_Of_Two_Circles( c1, c4, p1, p2 );
    
    if (Norm( c2.c, p1 ) < c2.r && Norm( c3.c, p1 ) < c3.r)
    {
        i.push_back( p1 );
        c4_arc.push_back( (int)i.size() - 1 );
    }
    
    else if (Norm( c2.c, p2 ) < c2.r && Norm( c3.c, p2 ) < c3.r)
    {
        i.push_back( p2 );
        c4_arc.push_back( (int)i.size() - 1 );
    }
    
    Intersection_Of_Two_Circles( c2, c3, p1, p2 );
    
    if (Norm( c1.c, p1 ) < c1.r && Norm( c4.c, p1 ) < c4.r)
    {
        i.push_back( p1 );
        c2_arc.push_back( (int)i.size() - 1 );
        c3_arc.push_back( (int)i.size() - 1 );
    }
    
    else if (Norm( c1.c, p2 ) < c1.r && Norm( c4.c, p2 ) < c4.r)
    {
        i.push_back( p2 );
        c2_arc.push_back( (int)i.size() - 1 );
        c3_arc.push_back( (int)i.size() - 1 );
    }
    
    Intersection_Of_Two_Circles( c2, c4, p1, p2 );
    
    if (Norm( c1.c, p1 ) < c1.r && Norm( c3.c, p1 ) < c3.r)
    {
        i.push_back( p1 );
        c2_arc.push_back( (int)i.size() - 1 );
        c4_arc.push_back( (int)i.size() - 1 );
    }
    
    else if (Norm( c1.c, p2 ) < c1.r && Norm( c3.c, p2 ) < c3.r)
    {
        i.push_back( p2 );
        c2_arc.push_back( (int)i.size() - 1 );
        c4_arc.push_back( (int)i.size() - 1 );
    }
    
    Intersection_Of_Two_Circles( c3, c4, p1, p2 );
    
    if (Norm( c1.c, p1 ) < c1.r && Norm( c2.c, p1 ) < c2.r)
    {
        i.push_back( p1 );
        c3_arc.push_back( (int)i.size() - 1 );
        c4_arc.push_back( (int)i.size() - 1 );
    }
    
    else if (Norm( c1.c, p2 ) < c1.r && Norm( c2.c, p2 ) < c2.r)
    {
        i.push_back( p2 );
        c3_arc.push_back( (int)i.size() - 1 );
        c4_arc.push_back( (int)i.size() - 1 );
    }
    
    i1 = i[0];
    i2 = i[1];
    i3 = i[3];
    i4 = i[2];
    
    arc_order.push_back( 1 );
    
    if (c3_arc[0] == 1)
    {
        arc_order.push_back( 3 );
        arc_order.push_back( 4 );
        arc_order.push_back( 2 );
    }
    
    else arc_order.push_back( 4 );
    
    if (c3_arc[0] == 0)
    {
        arc_order.push_back( 2 );
        arc_order.push_back( 3 );
    }
    
    else
    {
        arc_order.push_back( 3 );
        arc_order.push_back( 2 );
    }
}
