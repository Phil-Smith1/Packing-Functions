#include <string>

using namespace std;

void GIF ( string const& directory, string const& type, int iterations )
{
    string str_1 = type + "0.png";
    
    for (int counter = 1; counter < iterations; ++counter)
    {
        str_1 += " " + type + to_string( counter ) + ".png";
    }
    
    string str_2 = "cd && cd '" + directory + "' && /usr/local/Cellar/imagemagick/7.0.8-35/bin/convert -delay 15 " + str_1 + " -loop 0 animation.gif";
    
    system( str_2.c_str() );
}
