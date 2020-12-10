#include "Initialise_Cubes.h"
#include "Dividing_Space.h"
#include "Triangulate_Zones.h"

#include <fstream>

void Compute_Brillouin_Zones ( multimap<double, P3_E>const& pts, int zone_limit, P3_E const& centre, vector<vector<Tetrahedron>>& zones_of_tetras )
{
    vector<B_Poly> polys;
    
    Dividing_Space( centre, pts, polys, zone_limit );
    
    cout << "Number of polyhedrons: " << polys.size() << "." << endl;
    
    /*for (int counter_1 = 0; counter_1 < polys.size(); ++counter_1)
    {
        ofstream ofs( "/Users/philsmith/Documents/Work/Xcode Projects/Crystal_Density/3D/Data/Test/" + to_string( counter_1 ) + ".txt");
        
        ofs << polys[counter_1].zone - 1 << endl;
        
        ofs << polys[counter_1].poly << endl;
    }*/
    
    Triangulate_Zones( polys, zone_limit, zones_of_tetras );
}

void Compute_Brillouin_Zones_I ( multimap<double, P3>const& pts, int zone_limit, P3 const& centre, vector<vector<Tetrahedron_I>>& zones_of_tetras, vector<double>& max_radii )
{
    vector<B_Poly_I> polys;
    polys.reserve( 3000 );
    
    Dividing_Space_I( centre, pts, polys, zone_limit, max_radii );
    
    cout << "Number of polyhedrons: " << polys.size() << "." << endl;
    
    Triangulate_Zones_I( polys, zone_limit, zones_of_tetras );
}

void Compute_Brillouin_Zones_IT ( multimap<double, P3>const pts, int zone_limit, P3 const centre, vector<vector<Tetrahedron_I>>& zones_of_tetras, vector<double>& max_radii )
{
    vector<B_Poly_I> polys;
    polys.reserve( 3000 );
    
    Dividing_Space_I( centre, pts, polys, zone_limit, max_radii );
    
    cout << "Number of polyhedrons: " << polys.size() << "." << endl;
    
    Triangulate_Zones_I( polys, zone_limit, zones_of_tetras );
}
