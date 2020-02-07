#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_exact_constructions_kernel Exact_Kernel;
typedef Polyhedron_3<Exact_Kernel> Polyhedron;

typedef Exact_Kernel::Point_3 P3_E;
typedef Exact_Kernel::Vector_3 V3_E;
typedef Exact_Kernel::Segment_3 S3_E;
typedef Exact_Kernel::Plane_3 Pl3_E;
typedef Exact_Kernel::Intersect_3 I3;

typedef Polyhedron::Vertex_iterator vertex_iterator;

int Compute_Zone( P3_E const& centre, vector<Pl3_E>const& planes, Polyhedron& poly )
{
    vector<P3_E> vertices;
    
    for (vertex_iterator v = poly.vertices_begin(); v != poly.vertices_end(); ++v)
    {
        P3_E p = v->point();
        
        vertices.push_back( p );
    }
    
    P3_E mean = ORIGIN;
    
    for (int counter = 0; counter < vertices.size(); ++counter)
    {
        V3_E v = vertices[counter] - ORIGIN;
        
        mean += v;
    }
    
    int num_vertices = (int)vertices.size();
    
    mean = P3_E( mean.x() / (double)num_vertices, mean.y() / (double)num_vertices, mean.z() / (double)num_vertices );
    
    S3_E seg = S3_E( centre, mean );
    
    int zone = 1;
    
    for (int counter = 0; counter < planes.size(); ++counter)
    {
        cpp11::result_of<I3(Pl3_E, S3_E)>::type result = intersection( planes[counter], seg );
        
        if (result) ++zone;
    }
    
    return zone;
}
