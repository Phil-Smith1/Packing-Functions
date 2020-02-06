#include "Cell_2Circles.h"

Cell_2Circles::Cell_2Circles ( Cell_Circle const& cc1, Cell_Circle const& cc2 )
{
    cc.reserve( 2 );
    indices.reserve( 2 );
    
    cc.push_back( cc1 );
    indices.push_back( cc[0].index );
    cc.push_back( cc2 );
    indices.push_back( cc[1].index );
    
    tc = Two_Circles( cc1.c, cc2.c );
    
    cell = cc[0].cell;
}

Cell_2Circles::Cell_2Circles(){}
Cell_2Circles::~Cell_2Circles(){}
