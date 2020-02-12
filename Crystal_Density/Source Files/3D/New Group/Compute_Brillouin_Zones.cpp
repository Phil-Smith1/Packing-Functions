#include "Initialise_Cubes.h"
#include "Dividing_Space.h"
#include "Triangulate_Zones.h"

#include <fstream>

void Compute_Brillouin_Zones ( multimap<double, P3_E> const& pts, int zone_limit, P3_E const& centre, vector<vector<Tetrahedron>>& zones_of_tetras )
{
    vector<B_Poly> polys;
    
    Dividing_Space( centre, pts, polys, zone_limit );
    
    cout << polys.size() << endl;
    
    /*for (int counter_1 = 0; counter_1 < polys.size(); ++counter_1)
    {
        ofstream ofs( "/Users/philsmith/Documents/Work/Xcode Projects/Crystal_Density/3D/Data/Test/" + to_string( counter_1 ) + ".txt");
        
        ofs << polys[counter_1].zone - 1 << endl;
        
        ofs << polys[counter_1].poly << endl;
    }*/
    
    Triangulate_Zones( polys, zone_limit, zones_of_tetras );
}
