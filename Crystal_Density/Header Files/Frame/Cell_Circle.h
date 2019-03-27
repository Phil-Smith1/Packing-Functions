#pragma once

#include "Cell.h"
#include "Circle.h"

class Cell_Circle
{
    public:
    
    bool intersection = false, centre_within_cell;
    int index, num_vertices_within_circle = 0;
    double area;
    Circle c;
    Cell cell;
    
    Cell_Circle ( Cell const& cel, Circle const& cir );
    
    Cell_Circle();
    ~Cell_Circle();
};
