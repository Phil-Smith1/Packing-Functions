#include "Frame.h"
#include "Circle_Area_Within_Cell.h"

void First_Order_Total_Area ( Frame& f )
{
    for (auto& cc : f.cc)
    {
        cc.area = Circle_Area_Within_Cell( cc );
        
        f.total_area[0] += cc.area;
    }
}
