#pragma once

#include "Cell_Circle.h"
#include "Two_Circles.h"

class Cell_2Circles
{
    public:
    
    double area;
    vector<int> indices;
    Cell cell;
    vector<Cell_Circle> cc;
    Two_Circles tc;
    
    Cell_2Circles ( Cell_Circle const& cc1, Cell_Circle const& cc2 );
    
    Cell_2Circles();
    ~Cell_2Circles();
};
