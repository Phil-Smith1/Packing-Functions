#include "Frame.h"

Frame::Frame ( Cell const& cel, vector<double>const& r )
{
    cell = cel;
    
    c.reserve( (int)cell.pts.size() );
    
    for (int counter = 0; counter < cell.pts.size(); ++counter)
    {
        c.push_back( Circle( cell.pts[counter], r[counter] ) );
    }
    
    Order_Circles( c );
    
    cc.reserve( (int)cell.pts.size() );
    
    for (int counter = 0; counter < cell.pts.size(); ++counter)
    {
        c[counter].index = counter;
        cc.push_back( Cell_Circle( cell, c[counter] ) );
        cc[counter].index = counter;
    }
}

Frame::Frame(){}
Frame::~Frame(){}
