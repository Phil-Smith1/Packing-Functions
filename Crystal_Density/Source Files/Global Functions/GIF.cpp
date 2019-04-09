#include <string>

using namespace std;

void GIF ( int iterations )
{
    string str_1 = "Deform0.png";
    
    for (int counter = 1; counter < iterations; ++counter)
    {
        str_1 += " Deform" + to_string( counter ) + ".png";
    }
    
    string str_2 = "cd && cd 'Documents/Xcode Projects/Crystal_Density/Graphs/Deformation' && /usr/local/Cellar/imagemagick/7.0.8-35/bin/convert -delay 15 " + str_1 + " -loop 0 animation.gif";
    
    system( str_2.c_str() );
}
