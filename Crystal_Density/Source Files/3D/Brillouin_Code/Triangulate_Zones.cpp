#include "B_Poly.h"

#include <CGAL/Triangulation_3.h>

using namespace std;

typedef Tetrahedron_3<Exact_Kernel> Tetrahedron;
typedef Triangulation_3<Exact_Kernel> Triangulation;

typedef Exact_Kernel::Point_3 P3_E;

typedef Polyhedron::Vertex_iterator vertex_iterator;

typedef Triangulation::Finite_cells_iterator cells_iterator;

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
