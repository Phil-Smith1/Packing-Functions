#pragma once

#include "Edge3D.h"

using namespace std;

class Cell3D
{
    public:
    
    bool interior_pts = false;
    int num_pts;
    double vol;
    vector<P3> vertices;
    vector<P3> pts;
    vector<Edge3D> edges;
    
    Cell3D();
    ~Cell3D();
};
