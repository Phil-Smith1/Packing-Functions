#pragma once

#include "Cell_2Circles.h"
#include "Three_Circles.h"

class Cell_3Circles
{
    public:
    
    double area;
    vector<int> indices;
    Cell cell;
    vector<Cell_Circle> cc;
    vector<Cell_2Circles> c2c;
    Three_Circles thc;
    
    Cell_3Circles ( Cell_2Circles const& c2c1, Cell_2Circles const& c2c2, Cell_2Circles c2c3 );
    
    Cell_3Circles();
    ~Cell_3Circles();
};
