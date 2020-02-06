#include "Centres_In_Cell.h"

void Translate_Centres ( Cell3D& cell )
{
    bool inside = false;
    int counter_1 = 0, counter_2 = 0, counter_3 = 0;
    P3 pt = cell.pts[0];
    
    for (counter_1 = -3; counter_1 < 4; ++counter_1)
    {
        for (counter_2 = -3; counter_2 < 4; ++counter_2)
        {
            for (counter_3 = -3; counter_3 < 4; ++counter_3)
            {
                P3 new_pt = P3( pt.x() + counter_1 * cell.vertices[1].x() + counter_2 * cell.vertices[3].x() + counter_3 * cell.vertices[4].x(), pt.y() + counter_1 * cell.vertices[1].y() + counter_2 * cell.vertices[3].y() + counter_3 * cell.vertices[4].y(), pt.z() + counter_1 * cell.vertices[1].z() + counter_2 * cell.vertices[3].z() + counter_3 * cell.vertices[4].z() );
                
                cell.pts[0] = new_pt;
                
                if (Centres_In_Cell( cell ))
                {
                    inside = true;
                    break;
                }
            }
            
            if (inside) break;
        }
        
        if (inside) break;
    }
    
    cell.pts[0] = pt;
    
    for (int counter = 0; counter < cell.pts.size(); ++counter)
    {
        cell.pts[counter] = P3( cell.pts[counter].x() + counter_1 * cell.vertices[1].x() + counter_2 * cell.vertices[3].x() + counter_3 * cell.vertices[4].x(), cell.pts[counter].y() + counter_1 * cell.vertices[1].y() + counter_2 * cell.vertices[3].y() + counter_3 * cell.vertices[4].y(), cell.pts[counter].z() + counter_1 * cell.vertices[1].z() + counter_2 * cell.vertices[3].z() + counter_3 * cell.vertices[4].z() );
    }
}
