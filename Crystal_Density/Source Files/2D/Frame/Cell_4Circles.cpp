#include "Cell_4Circles.h"

Cell_4Circles::Cell_4Circles ( Cell_3Circles const& c3c1, Cell_3Circles const& c3c2, Cell_3Circles const& c3c3, Cell_3Circles const& c3c4 )
{
    c3c.reserve( 4 );
    
    c3c.push_back( c3c1 );
    c3c.push_back( c3c2 );
    c3c.push_back( c3c3 );
    c3c.push_back( c3c4 );
    
    c2c.reserve( 6 );
    
    c2c.push_back( c3c[0].c2c[0] );
    c2c.push_back( c3c[0].c2c[1] );
    c2c.push_back( c3c[1].c2c[1] );
    c2c.push_back( c3c[0].c2c[2] );
    c2c.push_back( c3c[3].c2c[1] );
    c2c.push_back( c3c[3].c2c[2] );
    
    cc.reserve( 4 );
    
    cc.push_back( c2c[0].cc[0] );
    cc.push_back( c2c[0].cc[1] );
    cc.push_back( c2c[1].cc[1] );
    cc.push_back( c2c[2].cc[1] );
    
    fc = Four_Circles( c3c[0].thc, c3c[1].thc, c3c[2].thc, c3c[3].thc );
    
    cell = cc[0].cell;
}

Cell_4Circles::Cell_4Circles(){}
Cell_4Circles::~Cell_4Circles(){}

