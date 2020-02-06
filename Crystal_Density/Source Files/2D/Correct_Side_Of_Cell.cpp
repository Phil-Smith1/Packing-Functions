#include "Cell.h"
#include "Same_Side.h"

bool Correct_Side_Of_Cell ( Cell const& cell, Edge const& e, P2 const& p )
{
    int index = 0;
    
    if (e.index == 0 || e.index == 3) index = 2;
    
    if (e.line.oriented_side( p ) == e.line.oriented_side( cell.vertices[index] )) return true;
    
    else return false;
}
