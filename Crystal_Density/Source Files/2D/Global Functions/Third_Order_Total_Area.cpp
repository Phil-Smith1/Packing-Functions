#include "Frame.h"
#include "Three_Circle_Intersection_Area_Within_Cell.h"

void Third_Order_Total_Area ( Frame& f )
{
    f.c3c.reserve( f.cell.num_pts * (f.cell.num_pts - 1) * (f.cell.num_pts - 2) / (double)6 );
    
    for (int counter_1 = 0; counter_1 < f.cell.num_pts - 2; ++counter_1)
    {
        for (int counter_2 = counter_1 + 1; counter_2 < f.cell.num_pts - 1; ++counter_2)
        {
            for (int counter_3 = counter_2 + 1; counter_3 < f.cell.num_pts; ++counter_3)
            {
                int index_1 = f.c2c.size() - 0.5 * (f.cell.num_pts - counter_1 - 1) * (f.cell.num_pts - counter_1) + counter_2 - counter_1 - 1;
                int index_2 = f.c2c.size() - 0.5 * (f.cell.num_pts - counter_1 - 1) * (f.cell.num_pts - counter_1) + counter_3 - counter_1 - 1;
                int index_3 = f.c2c.size() - 0.5 * (f.cell.num_pts - counter_2 - 1) * (f.cell.num_pts - counter_2) + counter_3 - counter_2 - 1;
                
                f.c3c.push_back( Cell_3Circles( f.c2c[index_1], f.c2c[index_2], f.c2c[index_3] ) );
            }
        }
    }
    
    /*f.c3c.push_back( Cell_3Circles( f.c2c[0], f.c2c[1], f.c2c[3] ) );
    f.c3c.push_back( Cell_3Circles( f.c2c[0], f.c2c[2], f.c2c[4] ) );
    f.c3c.push_back( Cell_3Circles( f.c2c[1], f.c2c[2], f.c2c[5] ) );
    f.c3c.push_back( Cell_3Circles( f.c2c[3], f.c2c[4], f.c2c[5] ) );*/
    
    for (auto& c3c : f.c3c)
    {
        c3c.area = Three_Circle_Intersection_Area_Within_Cell( c3c );
        
        f.total_area[2] += c3c.area;
    }
    
    if (f.total_area[2] < 0 && f.total_area[2] > -tiny_num) f.total_area[2] = 0;
}
