#include "Edge3D.h"

Edge3D::Edge3D ( L3 const& l, P3 const& s, P3 const& e, int i )
{
    line = l;
    startpt = s;
    endpt = e;
    index = i;
}

Edge3D::Edge3D(){}
Edge3D::~Edge3D(){}
