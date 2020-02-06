#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>

using namespace CGAL;

typedef Exact_predicates_exact_constructions_kernel Exact_Kernel;
typedef Polyhedron_3<Exact_Kernel> Polyhedron;

typedef Exact_Kernel::Point_3 P3_E;

typedef Polyhedron::Vertex_iterator vertex_iterator;

double Max_Distance_To_Polyhedron ( P3_E const& centre, Polyhedron& poly )
{
    double max_radius = 0;
    
    for (vertex_iterator v = poly.vertices_begin(); v != poly.vertices_end(); ++v)
    {
        P3_E p = v->point();
        
        double dist = sqrt( to_double( squared_distance( p, centre ) ) );
        
        if (dist > max_radius) max_radius = dist;
    }
    
    return max_radius;
}
