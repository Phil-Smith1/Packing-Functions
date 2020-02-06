#include "Cell_3Circles.h"

Cell_3Circles::Cell_3Circles ( Cell_2Circles const& c2c1, Cell_2Circles const& c2c2, Cell_2Circles c2c3 )
{
    c2c.reserve( 3 );
    c2c.push_back( c2c1 );
    c2c.push_back( c2c2 );
    c2c.push_back( c2c3 );
    
    cc.reserve( 2 );
    
    cc.push_back( c2c[0].cc[0] );
    cc.push_back( c2c[0].cc[1] );
    cc.push_back( c2c[1].cc[1] );
    
    thc = Three_Circles( c2c[0].tc, c2c[1].tc, c2c[2].tc );
    
    cell = cc[0].cell;
}

Cell_3Circles::Cell_3Circles(){}
Cell_3Circles::~Cell_3Circles(){}
