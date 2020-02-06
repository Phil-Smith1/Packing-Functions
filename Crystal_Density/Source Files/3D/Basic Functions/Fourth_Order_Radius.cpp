#include "Cell3D.h"
#include "Circumradius.h"

double Fourth_Order_Radius( Cell3D const& cell )
{
    double radius = 1e10;
    
    for (int counter_1 = 0; counter_1 < cell.pts.size(); ++counter_1)
    {
        for (int counter_2 = counter_1 + 1; counter_2 < cell.pts.size(); ++counter_2)
        {
            for (int counter_3 = counter_2 + 1; counter_3 < cell.pts.size(); ++counter_3)
            {
                for (int counter_4 = counter_3 + 1; counter_4 < cell.pts.size(); ++counter_4)
                {
                    double circumradius_1 = Circumradius( cell.pts[counter_1], cell.pts[counter_2], cell.pts[counter_3] );
                    
                    if (circumradius_1 > radius) continue;
                    
                    double circumradius_2 = Circumradius( cell.pts[counter_1], cell.pts[counter_2], cell.pts[counter_4] );
                    
                    if (circumradius_2 > radius) continue;
                    
                    double circumradius_3 = Circumradius( cell.pts[counter_1], cell.pts[counter_3], cell.pts[counter_4] );
                    
                    if (circumradius_3 > radius) continue;
                    
                    double circumradius_4 = Circumradius( cell.pts[counter_2], cell.pts[counter_3], cell.pts[counter_4] );
                    
                    if (circumradius_4 > radius) continue;
                    
                    double circumradius = std::max( circumradius_1, circumradius_2 );
                    circumradius = std::max( circumradius, circumradius_3 );
                    circumradius = std::max( circumradius, circumradius_4 );
                    
                    if (circumradius < radius) radius = circumradius;
                }
            }
        }
    }
    
    return radius;
}
