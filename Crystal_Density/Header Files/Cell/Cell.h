#pragma once

#include "Edge.h"

using namespace std;

class Cell
{
    public:
    
    bool interior_pts = false;
    int num_pts;
    double area;
    vector<P2> vertices;
    vector<P2> pts;
    vector<Edge> edges;
    
    Cell();
    ~Cell();
};
