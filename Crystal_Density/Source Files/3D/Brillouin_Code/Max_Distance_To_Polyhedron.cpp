#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>

using namespace CGAL;

typedef Exact_predicates_exact_constructions_kernel Exact_Kernel;
typedef Exact_predicates_inexact_constructions_kernel K;
typedef Polyhedron_3<Exact_Kernel> Polyhedron;

typedef Polyhedron_3<K> Polyhedron_I;

typedef Exact_Kernel::Point_3 P3_E;
typedef K::Point_3 P3;

typedef Polyhedron::Vertex_iterator vertex_iterator;
typedef Polyhedron_I::Vertex_iterator vertex_iterator_i;

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

double Max_Distance_To_Polyhedron_I ( P3 const& centre, Polyhedron_I& poly )
{
    double max_radius = 0;
    
    for (vertex_iterator_i v = poly.vertices_begin(); v != poly.vertices_end(); ++v)
    {
        P3 p = v->point();
        
        double dist = squared_distance( p, centre );
        
        if (dist > max_radius) max_radius = dist;
    }
    
    return sqrt( max_radius );
}

double Min_Distance_To_Polyhedron_I ( P3 const& centre, Polyhedron_I& poly )
{
    double min_radius = 1e10;
    
    for (vertex_iterator_i v = poly.vertices_begin(); v != poly.vertices_end(); ++v)
    {
        P3 p = v->point();
        
        double dist = squared_distance( p, centre );
        
        if (dist < min_radius) min_radius = dist;
    }
    
    return sqrt( min_radius );
}
