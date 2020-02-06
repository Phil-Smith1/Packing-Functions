#include "Cell3D.h"
#include "Norm3D.h"

typedef K::Segment_3 S3;

double Distance_To_Cell ( Cell3D const& cell, P3 const& p )
{
    vector<bool> bdry = { false, false, false, false, false, false };
    vector<bool> pos = { false, false, false, false, false, false };
    
    if (cell.planes[0].oriented_side( p ) == ON_ORIENTED_BOUNDARY) bdry[0] = true;
    if (cell.planes[1].oriented_side( p ) == ON_ORIENTED_BOUNDARY) bdry[1] = true;
    if (cell.planes[2].oriented_side( p ) == ON_ORIENTED_BOUNDARY) bdry[2] = true;
    if (cell.planes[3].oriented_side( p ) == ON_ORIENTED_BOUNDARY) bdry[3] = true;
    if (cell.planes[4].oriented_side( p ) == ON_ORIENTED_BOUNDARY) bdry[4] = true;
    if (cell.planes[5].oriented_side( p ) == ON_ORIENTED_BOUNDARY) bdry[5] = true;
    
    int num_bdry = 0, num_neg = 0;
    
    for (int counter = 0; counter < 6; ++counter) if (bdry[counter]) ++num_bdry;
    
    if (num_bdry >= 2) return 0;
    
    if (cell.planes[0].oriented_side( p ) == ON_POSITIVE_SIDE) pos[0] = true;
    if (cell.planes[1].oriented_side( p ) == ON_POSITIVE_SIDE) pos[1] = true;
    if (cell.planes[2].oriented_side( p ) == ON_POSITIVE_SIDE) pos[2] = true;
    if (cell.planes[3].oriented_side( p ) == ON_POSITIVE_SIDE) pos[3] = true;
    if (cell.planes[4].oriented_side( p ) == ON_POSITIVE_SIDE) pos[4] = true;
    if (cell.planes[5].oriented_side( p ) == ON_POSITIVE_SIDE) pos[5] = true;
    
    for (int counter = 0; counter < 6; ++counter) if (!pos[counter]) ++num_neg;
    
    if (num_bdry == 1)
    {
        int boundry;
        
        for (int counter = 0; counter < 6; ++counter) if (bdry[counter])
        {
            boundry = counter;
            break;
        }
        
        if (num_neg == 1) return 0;
        
        else if (num_neg == 2)
        {
            for (int counter_1 = 0; counter_1 < 6; ++counter_1)
            {
                if (!pos[counter_1])
                {
                    if (cell.planes[counter_1].oriented_side( p ) == ON_ORIENTED_BOUNDARY) continue;
                    
                    P3 proj = cell.planes[counter_1].projection( p );
                    
                    bool still_neg = false;
                    
                    for (int counter_2 = 0; counter_2 < 6; ++counter_2)
                    {
                        if (counter_2 == counter_1) continue;
                        
                        if (cell.planes[counter_2].oriented_side( proj ) == ON_NEGATIVE_SIDE)
                        {
                            still_neg = true;
                            break;
                        }
                    }
                    
                    if (!still_neg) return sqrt( squared_distance( cell.planes[counter_1], p ) );
                    
                    else
                    {
                        S3 s1, s2, s3, s4;
                        
                        if (counter_1 == 0)
                        {
                            s1 = S3( cell.vertices[0], cell.vertices[1] );
                            s2 = S3( cell.vertices[1], cell.vertices[2] );
                            s3 = S3( cell.vertices[2], cell.vertices[3] );
                            s4 = S3( cell.vertices[3], cell.vertices[0] );
                        }
                        
                        if (counter_1 == 1)
                        {
                            s1 = S3( cell.vertices[0], cell.vertices[1] );
                            s2 = S3( cell.vertices[1], cell.vertices[5] );
                            s3 = S3( cell.vertices[5], cell.vertices[4] );
                            s4 = S3( cell.vertices[4], cell.vertices[0] );
                        }
                        
                        if (counter_1 == 2)
                        {
                            s1 = S3( cell.vertices[4], cell.vertices[5] );
                            s2 = S3( cell.vertices[5], cell.vertices[6] );
                            s3 = S3( cell.vertices[6], cell.vertices[7] );
                            s4 = S3( cell.vertices[7], cell.vertices[0] );
                        }
                        
                        if (counter_1 == 3)
                        {
                            s1 = S3( cell.vertices[3], cell.vertices[2] );
                            s2 = S3( cell.vertices[2], cell.vertices[6] );
                            s3 = S3( cell.vertices[6], cell.vertices[7] );
                            s4 = S3( cell.vertices[7], cell.vertices[2] );
                        }
                        
                        if (counter_1 == 4)
                        {
                            s1 = S3( cell.vertices[0], cell.vertices[4] );
                            s2 = S3( cell.vertices[4], cell.vertices[7] );
                            s3 = S3( cell.vertices[7], cell.vertices[3] );
                            s4 = S3( cell.vertices[3], cell.vertices[0] );
                        }
                        
                        if (counter_1 == 5)
                        {
                            s1 = S3( cell.vertices[1], cell.vertices[5] );
                            s2 = S3( cell.vertices[5], cell.vertices[6] );
                            s3 = S3( cell.vertices[6], cell.vertices[2] );
                            s4 = S3( cell.vertices[2], cell.vertices[1] );
                        }
                        
                        double dist_1 = sqrt( squared_distance( s1, p ) );
                        double dist_2 = sqrt( squared_distance( s2, p ) );
                        double dist_3 = sqrt( squared_distance( s3, p ) );
                        double dist_4 = sqrt( squared_distance( s4, p ) );
                        
                        double dist = std::min( dist_1, dist_2 );
                        dist = std::min( dist, dist_3 );
                        dist = std::min( dist, dist_4 );
                        
                        return dist;
                    }
                }
            }
        }
        
        else if (num_neg == 3)
        {
            int neg_1 = -1, neg_2 = -1;
            
            for (int counter = 0; counter < 6; ++counter)
            {
                if (!pos[counter])
                {
                    if (cell.planes[counter].oriented_side( p ) == ON_ORIENTED_BOUNDARY) continue;
                    
                    if (neg_1 == -1) neg_1 = counter;
                    
                    else
                    {
                        neg_2 = counter;
                        break;
                    }
                }
            }
            
            if (neg_1 == 0 && neg_2 == 1)
            {
                S3 s = S3( cell.vertices[0], cell.vertices[1] );
                
                return sqrt( squared_distance( s, p ) );
            }
            
            else if (neg_1 == 0 && neg_2 == 3)
            {
                S3 s = S3( cell.vertices[2], cell.vertices[3] );
                
                return sqrt( squared_distance( s, p ) );
            }
            
            else if (neg_1 == 0 && neg_2 == 4)
            {
                S3 s = S3( cell.vertices[0], cell.vertices[3] );
                
                return sqrt( squared_distance( s, p ) );
            }
            
            else if (neg_1 == 0 && neg_2 == 5)
            {
                S3 s = S3( cell.vertices[1], cell.vertices[2] );
                
                return sqrt( squared_distance( s, p ) );
            }
            
            else if (neg_1 == 1 && neg_2 == 2)
            {
                S3 s = S3( cell.vertices[4], cell.vertices[5] );
                
                return sqrt( squared_distance( s, p ) );
            }
            
            else if (neg_1 == 1 && neg_2 == 4)
            {
                S3 s = S3( cell.vertices[0], cell.vertices[4] );
                
                return sqrt( squared_distance( s, p ) );
            }
            
            else if (neg_1 == 1 && neg_2 == 5)
            {
                S3 s = S3( cell.vertices[1], cell.vertices[5] );
                
                return sqrt( squared_distance( s, p ) );
            }
            
            else if (neg_1 == 2 && neg_2 == 3)
            {
                S3 s = S3( cell.vertices[6], cell.vertices[7] );
                
                return sqrt( squared_distance( s, p ) );
            }
            
            else if (neg_1 == 2 && neg_2 == 4)
            {
                S3 s = S3( cell.vertices[4], cell.vertices[7] );
                
                return sqrt( squared_distance( s, p ) );
            }
            
            else if (neg_1 == 2 && neg_2 == 5)
            {
                S3 s = S3( cell.vertices[5], cell.vertices[6] );
                
                return sqrt( squared_distance( s, p ) );
            }
            
            else if (neg_1 == 3 && neg_2 == 4)
            {
                S3 s = S3( cell.vertices[3], cell.vertices[7] );
                
                return sqrt( squared_distance( s, p ) );
            }
            
            else
            {
                S3 s = S3( cell.vertices[2], cell.vertices[6] );
                
                return sqrt( squared_distance( s, p ) );
            }
        }
        
        else if (num_neg == 3)
        {
            int neg_1 = -1, neg_2 = -1, neg_3 = -1;
            
            for (int counter = 0; counter < 6; ++counter)
            {
                if (!pos[counter])
                {
                    if (cell.planes[counter].oriented_side( p ) == ON_ORIENTED_BOUNDARY) continue;
                    
                    if (neg_1 == -1) neg_1 = counter;
                    
                    else if (neg_2 == -1) neg_2 = counter;
                    
                    else
                    {
                        neg_3 = counter;
                        break;
                    }
                }
            }
            
            if (neg_1 == 0 && neg_2 == 1 && neg_3 == 4) return Norm( cell.vertices[0], p );
            
            else if (neg_1 == 0 && neg_2 == 1 && neg_3 == 5) return Norm( cell.vertices[1], p );
            
            else if (neg_1 == 0 && neg_2 == 3 && neg_3 == 4) return Norm( cell.vertices[3], p );
            
            else if (neg_1 == 0 && neg_2 == 3 && neg_3 == 5) return Norm( cell.vertices[2], p );
            
            else if (neg_1 == 1 && neg_2 == 2 && neg_3 == 4) return Norm( cell.vertices[4], p );
            
            else if (neg_1 == 1 && neg_2 == 2 && neg_3 == 5) return Norm( cell.vertices[5], p );
            
            else if (neg_1 == 2 && neg_2 == 3 && neg_3 == 4) return Norm( cell.vertices[7], p );
            
            else return Norm( cell.vertices[6], p );
        }
    }
    
    else
    {
        if (num_neg == 0) return 0;
        
        else if (num_neg == 1)
        {
            for (int counter_1 = 0; counter_1 < 6; ++counter_1)
            {
                if (!pos[counter_1])
                {
                    P3 proj = cell.planes[counter_1].projection( p );
                    
                    bool still_neg = false;
                    
                    for (int counter_2 = 0; counter_2 < 6; ++counter_2)
                    {
                        if (counter_2 == counter_1) continue;
                        
                        if (cell.planes[counter_2].oriented_side( proj ) == ON_NEGATIVE_SIDE)
                        {
                            still_neg = true;
                            break;
                        }
                    }
                    
                    if (!still_neg) return sqrt( squared_distance( cell.planes[counter_1], p ) );
                    
                    else
                    {
                        S3 s1, s2, s3, s4;
                        
                        if (counter_1 == 0)
                        {
                            s1 = S3( cell.vertices[0], cell.vertices[1] );
                            s2 = S3( cell.vertices[1], cell.vertices[2] );
                            s3 = S3( cell.vertices[2], cell.vertices[3] );
                            s4 = S3( cell.vertices[3], cell.vertices[0] );
                        }
                        
                        if (counter_1 == 1)
                        {
                            s1 = S3( cell.vertices[0], cell.vertices[1] );
                            s2 = S3( cell.vertices[1], cell.vertices[5] );
                            s3 = S3( cell.vertices[5], cell.vertices[4] );
                            s4 = S3( cell.vertices[4], cell.vertices[0] );
                        }
                        
                        if (counter_1 == 2)
                        {
                            s1 = S3( cell.vertices[4], cell.vertices[5] );
                            s2 = S3( cell.vertices[5], cell.vertices[6] );
                            s3 = S3( cell.vertices[6], cell.vertices[7] );
                            s4 = S3( cell.vertices[7], cell.vertices[0] );
                        }
                        
                        if (counter_1 == 3)
                        {
                            s1 = S3( cell.vertices[3], cell.vertices[2] );
                            s2 = S3( cell.vertices[2], cell.vertices[6] );
                            s3 = S3( cell.vertices[6], cell.vertices[7] );
                            s4 = S3( cell.vertices[7], cell.vertices[2] );
                        }
                        
                        if (counter_1 == 4)
                        {
                            s1 = S3( cell.vertices[0], cell.vertices[4] );
                            s2 = S3( cell.vertices[4], cell.vertices[7] );
                            s3 = S3( cell.vertices[7], cell.vertices[3] );
                            s4 = S3( cell.vertices[3], cell.vertices[0] );
                        }
                        
                        if (counter_1 == 5)
                        {
                            s1 = S3( cell.vertices[1], cell.vertices[5] );
                            s2 = S3( cell.vertices[5], cell.vertices[6] );
                            s3 = S3( cell.vertices[6], cell.vertices[2] );
                            s4 = S3( cell.vertices[2], cell.vertices[1] );
                        }
                        
                        double dist_1 = sqrt( squared_distance( s1, p ) );
                        double dist_2 = sqrt( squared_distance( s2, p ) );
                        double dist_3 = sqrt( squared_distance( s3, p ) );
                        double dist_4 = sqrt( squared_distance( s4, p ) );
                        
                        double dist = std::min( dist_1, dist_2 );
                        dist = std::min( dist, dist_3 );
                        dist = std::min( dist, dist_4 );
                        
                        return dist;
                    }
                }
            }
        }
        
        else if (num_neg == 2)
        {
            int neg_1 = -1, neg_2 = -1;
            
            for (int counter = 0; counter < 6; ++counter)
            {
                if (!pos[counter])
                {
                    if (neg_1 == -1) neg_1 = counter;
                    
                    else
                    {
                        neg_2 = counter;
                        break;
                    }
                }
            }
            
            if (neg_1 == 0 && neg_2 == 1)
            {
                S3 s = S3( cell.vertices[0], cell.vertices[1] );
                
                return sqrt( squared_distance( s, p ) );
            }
            
            else if (neg_1 == 0 && neg_2 == 3)
            {
                S3 s = S3( cell.vertices[2], cell.vertices[3] );
                
                return sqrt( squared_distance( s, p ) );
            }
            
            else if (neg_1 == 0 && neg_2 == 4)
            {
                S3 s = S3( cell.vertices[0], cell.vertices[3] );
                
                return sqrt( squared_distance( s, p ) );
            }
            
            else if (neg_1 == 0 && neg_2 == 5)
            {
                S3 s = S3( cell.vertices[1], cell.vertices[2] );
                
                return sqrt( squared_distance( s, p ) );
            }
            
            else if (neg_1 == 1 && neg_2 == 2)
            {
                S3 s = S3( cell.vertices[4], cell.vertices[5] );
                
                return sqrt( squared_distance( s, p ) );
            }
            
            else if (neg_1 == 1 && neg_2 == 4)
            {
                S3 s = S3( cell.vertices[0], cell.vertices[4] );
                
                return sqrt( squared_distance( s, p ) );
            }
            
            else if (neg_1 == 1 && neg_2 == 5)
            {
                S3 s = S3( cell.vertices[1], cell.vertices[5] );
                
                return sqrt( squared_distance( s, p ) );
            }
            
            else if (neg_1 == 2 && neg_2 == 3)
            {
                S3 s = S3( cell.vertices[6], cell.vertices[7] );
                
                return sqrt( squared_distance( s, p ) );
            }
            
            else if (neg_1 == 2 && neg_2 == 4)
            {
                S3 s = S3( cell.vertices[4], cell.vertices[7] );
                
                return sqrt( squared_distance( s, p ) );
            }
            
            else if (neg_1 == 2 && neg_2 == 5)
            {
                S3 s = S3( cell.vertices[5], cell.vertices[6] );
                
                return sqrt( squared_distance( s, p ) );
            }
            
            else if (neg_1 == 3 && neg_2 == 4)
            {
                S3 s = S3( cell.vertices[3], cell.vertices[7] );
                
                return sqrt( squared_distance( s, p ) );
            }
            
            else
            {
                S3 s = S3( cell.vertices[2], cell.vertices[6] );
                
                return sqrt( squared_distance( s, p ) );
            }
        }
        
        else if (num_neg == 3)
        {
            int neg_1 = -1, neg_2 = -1, neg_3 = -1;
            
            for (int counter = 0; counter < 6; ++counter)
            {
                if (!pos[counter])
                {
                    if (neg_1 == -1) neg_1 = counter;
                    
                    else if (neg_2 == -1) neg_2 = counter;
                    
                    else
                    {
                        neg_3 = counter;
                        break;
                    }
                }
            }
            
            if (neg_1 == 0 && neg_2 == 1 && neg_3 == 4) return Norm( cell.vertices[0], p );
            
            else if (neg_1 == 0 && neg_2 == 1 && neg_3 == 5) return Norm( cell.vertices[1], p );
            
            else if (neg_1 == 0 && neg_2 == 3 && neg_3 == 4) return Norm( cell.vertices[3], p );
            
            else if (neg_1 == 0 && neg_2 == 3 && neg_3 == 5) return Norm( cell.vertices[2], p );
            
            else if (neg_1 == 1 && neg_2 == 2 && neg_3 == 4) return Norm( cell.vertices[4], p );
            
            else if (neg_1 == 1 && neg_2 == 2 && neg_3 == 5) return Norm( cell.vertices[5], p );
            
            else if (neg_1 == 2 && neg_2 == 3 && neg_3 == 4) return Norm( cell.vertices[7], p );
            
            else return Norm( cell.vertices[6], p );
        }
    }
    
    return 0;
}
