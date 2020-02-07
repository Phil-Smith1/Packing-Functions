#include "Initialise_Cubes.h"
#include "Dividing_Space.h"
#include "Triangulate_Zones.h"

void Compute_Brillouin_Zones ( multimap<double, P3_E> const& pts, int zone_limit, P3_E const& centre, vector<vector<Tetrahedron>>& zones_of_tetras )
{
    vector<B_Poly> polys;
    
    Dividing_Space( centre, pts, polys, zone_limit );
    
    cout << polys.size() << endl;
    
    Triangulate_Zones( polys, zone_limit, zones_of_tetras );
}
