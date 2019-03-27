#include "Frame.h"

void Areas ( Frame& f )
{
    f.area_at_least[0] = (f.total_area[0] - f.total_area[1] + f.total_area[2] - f.total_area[3]) / (double)f.cell.area;
    f.area_at_least[1] = (f.total_area[1] - 2 * f.total_area[2] + 3 * f.total_area[3]) / (double)f.cell.area;
    f.area_at_least[2] = (f.total_area[2] - 3 * f.total_area[3]) / (double)f.cell.area;
    f.area_at_least[3] = f.total_area[3] / (double)f.cell.area;
    
    if (f.cell.interior_pts)
    {
        if (f.cell.num_pts == 5)
        {
            f.total_area.push_back( f.c4c[0].area );
            
            f.area_at_least[0] += f.total_area[4] / (double)f.cell.area;
            f.area_at_least[1] -= 4 * f.total_area[4] / (double)f.cell.area;
            f.area_at_least[2] += 6 * f.total_area[4] / (double)f.cell.area;
            f.area_at_least[3] -= 4 * f.total_area[4] / (double)f.cell.area;
        }
        
        else
        {
            f.total_area.push_back( 0 );
            f.total_area.push_back( 0 );
            
            f.total_area[4] += 2 * f.c4c[0].area;
            f.total_area[4] += (f.c4c[1].area <= f.c4c[2].area) ? f.c4c[1].area : f.c4c[2].area;
            f.total_area[4] += (f.c4c[3].area <= f.c4c[4].area) ? f.c4c[3].area : f.c4c[4].area;
            f.total_area[4] += (f.c4c[6].area <= f.c4c[7].area) ? f.c4c[6].area : f.c4c[7].area;
            f.total_area[4] += (f.c4c[10].area <= f.c4c[11].area) ? f.c4c[10].area : f.c4c[11].area;
            
            f.total_area[5] += f.c4c[0].area;
            
            f.area_at_least[0] += (f.total_area[4] - f.total_area[5]) / (double)f.cell.area;
            f.area_at_least[1] -= (4 * f.total_area[4] - 5 * f.total_area[5]) / (double)f.cell.area;
            f.area_at_least[2] += (6 * f.total_area[4] - 10 * f.total_area[5]) / (double)f.cell.area;
            f.area_at_least[3] -= (4 * f.total_area[4] - 10 * f.total_area[5]) / (double)f.cell.area;
        }
    }
    
    f.area_exact[0] = f.area_at_least[0] - f.area_at_least[1];
    f.area_exact[1] = f.area_at_least[1] - f.area_at_least[2];
    f.area_exact[2] = f.area_at_least[2] - f.area_at_least[3];
    f.area_exact[3] = f.area_at_least[3];
}
