#include "Circle.h"

using namespace std;

void Order_Circles ( vector<Circle>& circles )
{
    for (int counter_1 = 0; counter_1 < circles.size(); ++counter_1)
    {
        int marker = counter_1;
        double radius = 1e10;
        Circle c = circles[0];
        
        for (int counter_2 = counter_1; counter_2 < circles.size(); ++counter_2)
        {
            if (circles[counter_2].r < radius)
            {
                marker = counter_2;
                radius = circles[counter_2].r;
                c = circles[counter_2];
            }
        }
        
        circles[marker] = circles[counter_1];
        circles[counter_1] = c;
    }
}
