#include "Cell3D.h"
#include "General_Spherical_Cone.h"
#include "Sphere_Four_Plane_Intersection_Volume.h"

double Spherical_Cap_Volume_Within_Cell ( Cell3D const& cell, Sphere const& s, Pl3 const& p )
{
    double volume = s.vol;
    
    for (auto it = cell.planes.begin(); it != cell.planes.end(); ++it)
    {
        volume -= s.vol - Spherical_Cap( s, *it );
    }
    
    volume -= s.vol - Spherical_Cap( s, p );
    
    volume += General_Spherical_Wedge( s, cell.planes[0].opposite(), cell.planes[1].opposite() );
    volume += General_Spherical_Wedge( s, cell.planes[1].opposite(), cell.planes[2].opposite() );
    volume += General_Spherical_Wedge( s, cell.planes[2].opposite(), cell.planes[3].opposite() );
    volume += General_Spherical_Wedge( s, cell.planes[3].opposite(), cell.planes[0].opposite() );
    volume += General_Spherical_Wedge( s, cell.planes[4].opposite(), cell.planes[0].opposite() );
    volume += General_Spherical_Wedge( s, cell.planes[4].opposite(), cell.planes[1].opposite() );
    volume += General_Spherical_Wedge( s, cell.planes[4].opposite(), cell.planes[2].opposite() );
    volume += General_Spherical_Wedge( s, cell.planes[4].opposite(), cell.planes[3].opposite() );
    volume += General_Spherical_Wedge( s, cell.planes[5].opposite(), cell.planes[0].opposite() );
    volume += General_Spherical_Wedge( s, cell.planes[5].opposite(), cell.planes[1].opposite() );
    volume += General_Spherical_Wedge( s, cell.planes[5].opposite(), cell.planes[2].opposite() );
    volume += General_Spherical_Wedge( s, cell.planes[5].opposite(), cell.planes[3].opposite() );
    
    volume += General_Spherical_Wedge( s, p.opposite(), cell.planes[0].opposite() );
    volume += General_Spherical_Wedge( s, p.opposite(), cell.planes[1].opposite() );
    volume += General_Spherical_Wedge( s, p.opposite(), cell.planes[2].opposite() );
    volume += General_Spherical_Wedge( s, p.opposite(), cell.planes[3].opposite() );
    volume += General_Spherical_Wedge( s, p.opposite(), cell.planes[4].opposite() );
    volume += General_Spherical_Wedge( s, p.opposite(), cell.planes[5].opposite() );
    
    volume -= General_Spherical_Cone( s, cell.planes[0].opposite(), cell.planes[1].opposite(), cell.planes[4].opposite() );
    volume -= General_Spherical_Cone( s, cell.planes[0].opposite(), cell.planes[1].opposite(), cell.planes[5].opposite() );
    volume -= General_Spherical_Cone( s, cell.planes[1].opposite(), cell.planes[2].opposite(), cell.planes[4].opposite() );
    volume -= General_Spherical_Cone( s, cell.planes[1].opposite(), cell.planes[2].opposite(), cell.planes[5].opposite() );
    volume -= General_Spherical_Cone( s, cell.planes[2].opposite(), cell.planes[3].opposite(), cell.planes[4].opposite() );
    volume -= General_Spherical_Cone( s, cell.planes[2].opposite(), cell.planes[3].opposite(), cell.planes[5].opposite() );
    volume -= General_Spherical_Cone( s, cell.planes[3].opposite(), cell.planes[0].opposite(), cell.planes[4].opposite() );
    volume -= General_Spherical_Cone( s, cell.planes[3].opposite(), cell.planes[0].opposite(), cell.planes[5].opposite() );
    
    volume -= General_Spherical_Cone( s, p.opposite(), cell.planes[0].opposite(), cell.planes[1].opposite() );
    volume -= General_Spherical_Cone( s, p.opposite(), cell.planes[1].opposite(), cell.planes[2].opposite() );
    volume -= General_Spherical_Cone( s, p.opposite(), cell.planes[2].opposite(), cell.planes[3].opposite() );
    volume -= General_Spherical_Cone( s, p.opposite(), cell.planes[3].opposite(), cell.planes[0].opposite() );
    volume -= General_Spherical_Cone( s, p.opposite(), cell.planes[4].opposite(), cell.planes[0].opposite() );
    volume -= General_Spherical_Cone( s, p.opposite(), cell.planes[4].opposite(), cell.planes[1].opposite() );
    volume -= General_Spherical_Cone( s, p.opposite(), cell.planes[4].opposite(), cell.planes[2].opposite() );
    volume -= General_Spherical_Cone( s, p.opposite(), cell.planes[4].opposite(), cell.planes[3].opposite() );
    volume -= General_Spherical_Cone( s, p.opposite(), cell.planes[5].opposite(), cell.planes[0].opposite() );
    volume -= General_Spherical_Cone( s, p.opposite(), cell.planes[5].opposite(), cell.planes[1].opposite() );
    volume -= General_Spherical_Cone( s, p.opposite(), cell.planes[5].opposite(), cell.planes[2].opposite() );
    volume -= General_Spherical_Cone( s, p.opposite(), cell.planes[5].opposite(), cell.planes[3].opposite() );
    
    volume += Sphere_Four_Plane_Intersection_Volume( s, p.opposite(), cell.planes[0].opposite(), cell.planes[1].opposite(), cell.planes[4].opposite() );
    volume += Sphere_Four_Plane_Intersection_Volume( s, p.opposite(), cell.planes[0].opposite(), cell.planes[1].opposite(), cell.planes[5].opposite() );
    volume += Sphere_Four_Plane_Intersection_Volume( s, p.opposite(), cell.planes[1].opposite(), cell.planes[2].opposite(), cell.planes[4].opposite() );
    volume += Sphere_Four_Plane_Intersection_Volume( s, p.opposite(), cell.planes[1].opposite(), cell.planes[2].opposite(), cell.planes[5].opposite() );
    volume += Sphere_Four_Plane_Intersection_Volume( s, p.opposite(), cell.planes[2].opposite(), cell.planes[3].opposite(), cell.planes[4].opposite() );
    volume += Sphere_Four_Plane_Intersection_Volume( s, p.opposite(), cell.planes[2].opposite(), cell.planes[3].opposite(), cell.planes[5].opposite() );
    volume += Sphere_Four_Plane_Intersection_Volume( s, p.opposite(), cell.planes[3].opposite(), cell.planes[0].opposite(), cell.planes[4].opposite() );
    volume += Sphere_Four_Plane_Intersection_Volume( s, p.opposite(), cell.planes[3].opposite(), cell.planes[0].opposite(), cell.planes[5].opposite() );
    
    return volume;
}
