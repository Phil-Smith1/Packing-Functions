#include "Edge.h"

Edge::Edge ( L2 const& l, P2 const& s, P2 const& e, int i )
{
    line = l;
    startpt = s;
    endpt = e;
    index = i;
}

Edge::Edge(){}
Edge::~Edge(){}
