#pragma once

#include "Cell_3Circles.h"
#include "Four_Circles.h"

class Cell_4Circles
{
    public:
    
    double area;
    vector<int> indices;
    Cell cell;
    vector<Cell_Circle> cc;
    vector<Cell_2Circles> c2c;
    vector<Cell_3Circles> c3c;
    Four_Circles fc;
    
    Cell_4Circles ( Cell_3Circles const& c3c1, Cell_3Circles const& c3c2, Cell_3Circles const& c3c3, Cell_3Circles const& c3c4 );
    
    Cell_4Circles();
    ~Cell_4Circles();
};
