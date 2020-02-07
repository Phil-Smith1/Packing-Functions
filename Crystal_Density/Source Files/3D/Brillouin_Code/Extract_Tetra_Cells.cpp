#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_exact_constructions_kernel Exact_Kernel;
typedef Exact_predicates_inexact_constructions_kernel K;

typedef Tetrahedron_3<Exact_Kernel> Tetrahedron;
typedef Exact_Kernel::Point_3 P3_E;

typedef K::Point_3 P3;
typedef K::Plane_3 Pl3;

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

void Extract_Tetra_Cells ( vector<vector<Tetrahedron>>const& zones_of_tetras, int zone_limit, vector<vector<vector<Pl3>>>& tetra_cells )
{
    for (int counter_1 = 0; counter_1 < zone_limit; ++counter_1)
    {
        vector<vector<Pl3>> single_zone_tetra_cells;
        single_zone_tetra_cells.reserve( (int)zones_of_tetras[counter_1].size() );
        
        for (int counter_2 = 0; counter_2 < zones_of_tetras[counter_1].size(); ++counter_2)
        {
            if (to_double( zones_of_tetras[counter_1][counter_2].volume() ) < tiny_num * 1e7) continue;
            
            vector<P3_E> exact_vertices;
            
            exact_vertices.push_back( zones_of_tetras[counter_1][counter_2].vertex( 0 ) );
            exact_vertices.push_back( zones_of_tetras[counter_1][counter_2].vertex( 1 ) );
            exact_vertices.push_back( zones_of_tetras[counter_1][counter_2].vertex( 2 ) );
            exact_vertices.push_back( zones_of_tetras[counter_1][counter_2].vertex( 3 ) );
            
            vector<P3> vertices;
            
            vertices.push_back( P3( to_double( exact_vertices[0].x() ), to_double( exact_vertices[0].y() ), to_double( exact_vertices[0].z() ) ) );
            vertices.push_back( P3( to_double( exact_vertices[1].x() ), to_double( exact_vertices[1].y() ), to_double( exact_vertices[1].z() ) ) );
            vertices.push_back( P3( to_double( exact_vertices[2].x() ), to_double( exact_vertices[2].y() ), to_double( exact_vertices[2].z() ) ) );
            vertices.push_back( P3( to_double( exact_vertices[3].x() ), to_double( exact_vertices[3].y() ), to_double( exact_vertices[3].z() ) ) );
            
            vector<Pl3> tetra_cell;
            
            tetra_cell.push_back( Pl3( vertices[0], vertices[1], vertices[2] ) );
            tetra_cell.push_back( Pl3( vertices[0], vertices[1], vertices[3] ) );
            tetra_cell.push_back( Pl3( vertices[0], vertices[2], vertices[3] ) );
            tetra_cell.push_back( Pl3( vertices[1], vertices[2], vertices[3] ) );
            
            if (tetra_cell[0].oriented_side( vertices[3] ) == ON_NEGATIVE_SIDE) tetra_cell[0] = tetra_cell[0].opposite();
            if (tetra_cell[1].oriented_side( vertices[2] ) == ON_NEGATIVE_SIDE) tetra_cell[1] = tetra_cell[1].opposite();
            if (tetra_cell[2].oriented_side( vertices[1] ) == ON_NEGATIVE_SIDE) tetra_cell[2] = tetra_cell[2].opposite();
            if (tetra_cell[3].oriented_side( vertices[0] ) == ON_NEGATIVE_SIDE) tetra_cell[3] = tetra_cell[3].opposite();
            
            single_zone_tetra_cells.push_back( tetra_cell );
        }
        
        tetra_cells.push_back( single_zone_tetra_cells );
    }
}
