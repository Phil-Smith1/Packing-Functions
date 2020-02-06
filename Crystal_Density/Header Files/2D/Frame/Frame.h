#pragma once

#include "Cell_4Circles.h"
#include "Order_Circles.h"

class Frame
{
    public:
    
    vector<double> total_area = { 0, 0, 0, 0 };
    vector<double> area_at_least = { 0, 0, 0, 0 };
    vector<double> area_exact = { 0, 0, 0, 0 };
    Cell cell;
    vector<Circle> c;
    vector<Cell_Circle> cc;
    vector<Cell_2Circles> c2c;
    vector<Cell_3Circles> c3c;
    vector<Cell_4Circles> c4c;
    
    Frame ( Cell const& cel, vector<double>const& r );
    
    Frame();
    ~Frame();
};
