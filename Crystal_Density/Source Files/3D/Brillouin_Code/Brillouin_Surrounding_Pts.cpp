#include "Frac_To_Cart_Coords.h"

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

using namespace std;

typedef Exact_predicates_exact_constructions_kernel Exact_Kernel;
typedef Exact_Kernel::Point_3 P3_E;
typedef Exact_Kernel::Vector_3 V3_E;

typedef K::Vector_3 V3;

void Brillouin_Surrounding_Pts ( int perim, double ** matrix, int index, vector<P3>const& pts, multimap<double, P3_E>& surrounding_pts )
{
    P3 p1 = P3( 1, 0, 0 );
    P3 p2 = P3( 0, 1, 0 );
    P3 p3 = P3( 0, 0, 1 );
    
    Frac_To_Cart_Coords( matrix, p1 );
    Frac_To_Cart_Coords( matrix, p2 );
    Frac_To_Cart_Coords( matrix, p3 );
    
    V3_E v1_E = V3_E( p1.x(), p1.y(), p1.z() );
    V3_E v2_E = V3_E( p2.x(), p2.y(), p2.z() );
    V3_E v3_E = V3_E( p3.x(), p3.y(), p3.z() );
    
    vector<P3_E> pts_E;
    pts_E.reserve( pts.size() );
    
    for (int counter = 0; counter < pts.size(); ++counter)
    {
        pts_E.push_back( P3_E( pts[counter].x(), pts[counter].y(), pts[counter].z() ) );
    }
    
    for (int counter_1 = -perim; counter_1 < perim + 1; ++counter_1)
    {
        for (int counter_2 = -perim; counter_2 < perim + 1; ++counter_2)
        {
            for (int counter_3 = -perim; counter_3 < perim + 1; ++counter_3)
            {
                V3_E v = counter_1 * v1_E + counter_2 * v2_E + counter_3 * v3_E;
                
                for (int counter_4 = 0; counter_4 < pts.size(); ++counter_4)
                {
                    if (counter_1 == 0 && counter_2 == 0 && counter_3 == 0 && counter_4 == index) continue;
                    
                    P3_E p = pts_E[counter_4] + v;
                    
                    double dist = to_double( squared_distance( pts_E[index], p ) );
                    
                    surrounding_pts.insert( pair<double, P3_E>( dist, p ) );
                }
            }
        }
    }
}

void Brillouin_Surrounding_Pts_I ( int perim, double ** matrix, int index, vector<P3>const& pts, multimap<double, P3>& surrounding_pts )
{
    P3 p1 = P3( 1, 0, 0 );
    P3 p2 = P3( 0, 1, 0 );
    P3 p3 = P3( 0, 0, 1 );
    
    Frac_To_Cart_Coords( matrix, p1 );
    Frac_To_Cart_Coords( matrix, p2 );
    Frac_To_Cart_Coords( matrix, p3 );
    
    V3 v1 = V3( p1.x(), p1.y(), p1.z() );
    V3 v2 = V3( p2.x(), p2.y(), p2.z() );
    V3 v3 = V3( p3.x(), p3.y(), p3.z() );
    
    for (int counter_1 = -perim; counter_1 < perim + 1; ++counter_1)
    {
        for (int counter_2 = -perim; counter_2 < perim + 1; ++counter_2)
        {
            for (int counter_3 = -perim; counter_3 < perim + 1; ++counter_3)
            {
                V3 v = counter_1 * v1 + counter_2 * v2 + counter_3 * v3;
                
                for (int counter_4 = 0; counter_4 < pts.size(); ++counter_4)
                {
                    if (counter_1 == 0 && counter_2 == 0 && counter_3 == 0 && counter_4 == index) continue;
                    
                    P3 p = pts[counter_4] + v;
                    
                    double dist = to_double( squared_distance( pts[index], p ) );
                    
                    surrounding_pts.insert( pair<double, P3>( dist, p ) );
                }
            }
        }
    }
}
