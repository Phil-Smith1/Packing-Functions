#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_exact_constructions_kernel Exact_Kernel;
typedef Polyhedron_3<Exact_Kernel> Polyhedron;

typedef Exact_Kernel::Point_3 P3_E;
typedef Exact_Kernel::Plane_3 Pl3_E;

typedef Polyhedron::Vertex_iterator vertex_iterator;

int Plane_Intersect_Polyhedron ( Polyhedron& cube, Pl3_E const& plane )
{
    vector<P3_E> pos_pts;
    vector<P3_E> neg_pts;
    vector<P3_E> bdry_pts;
    
    for (vertex_iterator v = cube.vertices_begin(); v != cube.vertices_end(); ++v)
    {
        P3_E p = v->point();
        
        if (squared_distance( p, plane ) < 1e-10) bdry_pts.push_back( p );
        
        else if (plane.oriented_side( p ) == ON_POSITIVE_SIDE) pos_pts.push_back( p );
        
        else neg_pts.push_back( p );
    }
    
    if ((int)neg_pts.size() == 0 || (int)pos_pts.size() == 0)
    {
        if ((int)pos_pts.size() == 0) return -1;
        
        else return 1;
    }
    
    else return 0;
}
