#pragma once

#include <string>

using namespace std;

class Graph_Parameters
{
    public:
    
    bool title;
    double yrange;
    string title_str;
    
    Graph_Parameters ( bool t, double yr, string const& t_s );
    
    Graph_Parameters();
    ~Graph_Parameters();
};
