#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_exact_constructions_kernel Exact_Kernel;
typedef Exact_predicates_inexact_constructions_kernel K;
typedef Polyhedron_3<Exact_Kernel> Polyhedron;
typedef Polyhedron_3<K> Polyhedron_I;

typedef Exact_Kernel::Point_3 P3_E;
typedef Exact_Kernel::Plane_3 Pl3_E;

typedef K::Point_3 P3;
typedef K::Plane_3 Pl3;

typedef Polyhedron::Vertex_iterator vertex_iterator;
typedef Polyhedron_I::Vertex_iterator vertex_iterator_i;

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

int Plane_Intersect_Polyhedron_I ( Polyhedron_I& cube, Pl3 const& plane )
{
    bool pos = false, neg = false;
    
    for (vertex_iterator_i v = cube.vertices_begin(); v != cube.vertices_end(); ++v)
    {
        P3 p = v->point();
        
        if (squared_distance( p, plane ) < 1e-10) continue;
        
        else if (plane.oriented_side( p ) == ON_POSITIVE_SIDE) pos = true;
        
        else neg = true;
        
        if (pos && neg) break;
    }
    
    if (!pos || !neg)
    {
        if (!pos) return -1;
        
        else return 1;
    }
    
    else return 0;
}
