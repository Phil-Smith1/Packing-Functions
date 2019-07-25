#pragma once

#include "Edge3D.h"

typedef K::Plane_3 Pl3;

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
    vector<Pl3> planes;
    
    Cell3D();
    ~Cell3D();
};
