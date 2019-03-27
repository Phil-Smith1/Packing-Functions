#include "Intersection_Of_Two_Circles.h"
#include "Segment_Area.h"
#include "Triangle_Area.h"

using namespace std;

double Non_Trivial_Four_Circle_Intersection_Area ( Circle const& c1, Circle const& c2, Circle const& c3, Circle const& c4 )
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
    
    double segment_area_1 = Segment_Area( c1, i[0], i[1] );
    double segment_area_2 = Segment_Area( c2, i[c2_arc[0]], i[c2_arc[1]] );
    double segment_area_3 = Segment_Area( c3, i[c3_arc[0]], i[c3_arc[1]] );
    double segment_area_4 = Segment_Area( c4, i[c4_arc[0]], i[c4_arc[1]] );
    
    double triangle_area_1 = Triangle_Area( i[0], i[1], i[2] );
    
    double triangle_area_2 = Triangle_Area( i[1], i[2], i[3] );
    
    return segment_area_1 + segment_area_2 + segment_area_3 + segment_area_4 + triangle_area_1 + triangle_area_2;
}
