#include "Frame.h"
#include "Two_Circle_Intersection_Area_Within_Cell.h"

void Second_Order_Total_Area ( Frame& f )
{
    f.c2c.reserve( 0.5 * f.cell.num_pts * (f.cell.num_pts - 1) );
    
    for (int counter_1 = 0; counter_1 < f.cell.num_pts - 1; ++counter_1)
    {
        for (int counter_2 = counter_1 + 1; counter_2 < f.cell.num_pts; ++counter_2)
        {
            f.c2c.push_back( Cell_2Circles( f.cc[counter_1], f.cc[counter_2] ) );
        }
    }
    
    //f.c2c.push_back( Cell_2Circles( f.cc[0], f.cc[4] ) );
    /*f.c2c.push_back( Cell_2Circles( f.cc[0], f.cc[2] ) );
    f.c2c.push_back( Cell_2Circles( f.cc[0], f.cc[3] ) );
    f.c2c.push_back( Cell_2Circles( f.cc[1], f.cc[2] ) );
    f.c2c.push_back( Cell_2Circles( f.cc[1], f.cc[3] ) );
    f.c2c.push_back( Cell_2Circles( f.cc[2], f.cc[3] ) );
    f.c2c.push_back( Cell_2Circles( f.cc[4], f.cc[0] ) );
    f.c2c.push_back( Cell_2Circles( f.cc[4], f.cc[1] ) );
    f.c2c.push_back( Cell_2Circles( f.cc[4], f.cc[2] ) );
    f.c2c.push_back( Cell_2Circles( f.cc[4], f.cc[3] ) );*/

    
    for (auto& c2c : f.c2c)
    {
        c2c.area = Two_Circle_Intersection_Area_Within_Cell( c2c );
        
        f.total_area[1] += c2c.area;
    }
    
    if (f.total_area[1] < 0 && f.total_area[1] > -tiny_num) f.total_area[1] = 0;
}
