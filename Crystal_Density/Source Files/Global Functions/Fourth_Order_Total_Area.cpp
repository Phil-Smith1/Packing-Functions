#include "Four_Circle_Intersection_Area_Within_Cell.h"
#include "Frame.h"

int Factorial ( int n )
{
    if (n <= 0) return 1;
    
    else return n * Factorial( n - 1 );
}

int Binomial_Coeff ( int n, int k )
{
    return Factorial( n ) / (Factorial( n - k ) * Factorial( k ));
}

void Fourth_Order_Total_Area ( Frame& f )
{
    for (int counter_1 = 0; counter_1 < f.cell.num_pts - 3; ++counter_1)
    {
        for (int counter_2 = counter_1 + 1; counter_2 < f.cell.num_pts - 2; ++counter_2)
        {
            for (int counter_3 = counter_2 + 1; counter_3 < f.cell.num_pts - 1; ++counter_3)
            {
                for (int counter_4 = counter_3 + 1; counter_4 < f.cell.num_pts; ++counter_4)
                {
                    int a = (int)f.c3c.size(), b = f.cell.num_pts - counter_1, c = b - 1, d = c - counter_2 + 1 + counter_1, e = c - counter_3 + 1 + counter_1, g = f.cell.num_pts - counter_2;
                    
                    int index_1 = a - Binomial_Coeff( b, 3 ) + Binomial_Coeff( b - 1, 2 ) - Binomial_Coeff( d, 2 ) + counter_3 - counter_2 - 1;
                    int index_2 = a - Binomial_Coeff( b, 3 ) + Binomial_Coeff( b - 1, 2 ) - Binomial_Coeff( d, 2 ) + counter_4 - counter_2 - 1;
                    int index_3 = a - Binomial_Coeff( b, 3 ) + Binomial_Coeff( b - 1, 2 ) - Binomial_Coeff( e, 2 ) + counter_4 - counter_3 - 1;
                    int index_4 = a - Binomial_Coeff( g, 3 ) + Binomial_Coeff( g - 1, 2 ) - Binomial_Coeff( e, 2 ) + counter_4 - counter_3 - 1;
                    
                    f.c4c.push_back( Cell_4Circles( f.c3c[index_1], f.c3c[index_2], f.c3c[index_3], f.c3c[index_4] ) );
                }
            }
        }
    }
    
    /*f.c4c.push_back( Cell_4Circles( f.c3c[0], f.c3c[1], f.c3c[3], f.c3c[6] ) );
    f.c4c.push_back( Cell_4Circles( f.c3c[0], f.c3c[2], f.c3c[4], f.c3c[7] ) );
    f.c4c.push_back( Cell_4Circles( f.c3c[1], f.c3c[2], f.c3c[5], f.c3c[8] ) );
    f.c4c.push_back( Cell_4Circles( f.c3c[3], f.c3c[4], f.c3c[5], f.c3c[9] ) );
    f.c4c.push_back( Cell_4Circles( f.c3c[6], f.c3c[7], f.c3c[8], f.c3c[9] ) );*/
    
    for (auto& c4c : f.c4c)
    {
        c4c.area = Four_Circle_Intersection_Area_Within_Cell( c4c );
        
        f.total_area[3] += c4c.area;
    }
}
