#include "Four_Circles.h"

Four_Circles::Four_Circles ( Three_Circles const& thc1, Three_Circles const& thc2, Three_Circles const& thc3, Three_Circles const& thc4 )
{
    c.reserve( 4 );
    
    c.push_back( thc1.c[0] );
    c.push_back( thc1.c[1] );
    c.push_back( thc1.c[2] );
    c.push_back( thc2.c[2] );
    
    tc.reserve( 6 );
    
    tc.push_back( Two_Circles( c[0], c[1] ) );
    tc.push_back( Two_Circles( c[0], c[2] ) );
    tc.push_back( Two_Circles( c[0], c[3] ) );
    tc.push_back( Two_Circles( c[1], c[2] ) );
    tc.push_back( Two_Circles( c[1], c[3] ) );
    tc.push_back( Two_Circles( c[2], c[3] ) );
    
    thc.reserve( 4 );
    
    thc.push_back( thc4 );
    thc.push_back( thc3 );
    thc.push_back( thc2 );
    thc.push_back( thc1 );
}

Four_Circles::Four_Circles(){}
Four_Circles::~Four_Circles(){}
