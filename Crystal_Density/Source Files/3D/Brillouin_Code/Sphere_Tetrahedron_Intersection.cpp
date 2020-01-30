#include "General_Spherical_Cone.h"

using namespace std;

double Sphere_Tetrahedron_Intersection ( Sphere const& s, vector<Pl3>const& tetra )
{
    double volume = General_Spherical_Cone( s, tetra[0], tetra[1], tetra[2] ) - Spherical_Cap( s, tetra[3].opposite() ) + General_Spherical_Wedge( s, tetra[0].opposite(), tetra[3].opposite() ) + General_Spherical_Wedge( s, tetra[1].opposite(), tetra[3].opposite() ) + General_Spherical_Wedge( s, tetra[2].opposite(), tetra[3].opposite() ) - General_Spherical_Cone( s, tetra[0].opposite(), tetra[1].opposite(), tetra[3].opposite() ) - General_Spherical_Cone( s, tetra[0].opposite(), tetra[2].opposite(), tetra[3].opposite() ) - General_Spherical_Cone( s, tetra[1].opposite(), tetra[2].opposite(), tetra[3].opposite() );
    
    return volume;
}
