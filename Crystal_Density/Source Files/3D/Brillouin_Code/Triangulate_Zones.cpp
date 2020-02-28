#include "B_Poly.h"
#include "B_Poly_I.h"

#include <CGAL/Triangulation_3.h>

using namespace std;

typedef Tetrahedron_3<Exact_Kernel> Tetrahedron;
typedef Triangulation_3<Exact_Kernel> Triangulation;

typedef Tetrahedron_3<K> Tetrahedron_I;
typedef Triangulation_3<K> Triangulation_I;

typedef Exact_Kernel::Point_3 P3_E;
typedef K::Point_3 P3;

typedef Polyhedron::Vertex_iterator vertex_iterator;
typedef Polyhedron_I::Vertex_iterator vertex_iterator_i;

typedef Triangulation::Finite_cells_iterator cells_iterator;
typedef Triangulation_I::Finite_cells_iterator cells_iterator_i;

void Triangulate_Zones ( vector<B_Poly>& polys, int zone_limit, vector<vector<Tetrahedron>>& zones_of_tetras )
{
    zones_of_tetras.resize( zone_limit );
    
    for (int counter = 0; counter < polys.size(); ++counter)
    {
        vector<P3_E> vertices;
        
        for (vertex_iterator v = polys[counter].poly.vertices_begin(); v != polys[counter].poly.vertices_end(); ++v)
        {
            P3_E p = v->point();
            
            vertices.push_back( p );
        }
        
        Triangulation T( vertices.begin(), vertices.end() );
        
        for (cells_iterator c = T.Triangulation::finite_cells_begin(); c != T.Triangulation::finite_cells_end(); ++c)
        {
            Tetrahedron tetra = T.Triangulation::tetrahedron( c );
            
            zones_of_tetras[polys[counter].zone - 1].push_back( tetra );
        }
    }
}

void Triangulate_Zones_I ( vector<B_Poly_I>& polys, int zone_limit, vector<vector<Tetrahedron_I>>& zones_of_tetras )
{
    zones_of_tetras.resize( zone_limit );
    
    for (int counter = 0; counter < polys.size(); ++counter)
    {
        vector<P3> vertices;
        
        for (vertex_iterator_i v = polys[counter].poly.vertices_begin(); v != polys[counter].poly.vertices_end(); ++v)
        {
            P3 p = v->point();
            
            vertices.push_back( p );
        }
        
        Triangulation_I T( vertices.begin(), vertices.end() );
        
        for (cells_iterator_i c = T.Triangulation_I::finite_cells_begin(); c != T.Triangulation_I::finite_cells_end(); ++c)
        {
            Tetrahedron_I tetra = T.Triangulation_I::tetrahedron( c );
            
            zones_of_tetras[polys[counter].zone - 1].push_back( tetra );
        }
    }
}
