#include "Sphere.h"

using namespace std;

void Sphere_Ordering ( vector<Sphere>& spheres )
{
    for (int counter_1 = 0; counter_1 < spheres.size(); ++counter_1)
    {
        int marker = counter_1;
        double radius = 1e10;
        Sphere s = spheres[0];
        
        for (int counter_2 = counter_1; counter_2 < spheres.size(); ++counter_2)
        {
            if (spheres[counter_2].r < radius)
            {
                marker = counter_2;
                radius = spheres[counter_2].r;
                s = spheres[counter_2];
            }
        }
        
        spheres[marker] = spheres[counter_1];
        spheres[counter_1] = s;
    }
}
