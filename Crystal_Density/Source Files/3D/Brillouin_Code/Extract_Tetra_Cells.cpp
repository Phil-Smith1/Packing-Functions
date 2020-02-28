#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_exact_constructions_kernel Exact_Kernel;
typedef Exact_predicates_inexact_constructions_kernel K;

typedef Tetrahedron_3<Exact_Kernel> Tetrahedron;
typedef Exact_Kernel::Point_3 P3_E;
typedef Exact_Kernel::Plane_3 Pl3_E;

typedef Tetrahedron_3<K> Tetrahedron_I;
typedef K::Point_3 P3;
typedef K::Line_3 L3;
typedef K::Plane_3 Pl3;

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

#include "Sphere_Tetrahedron_Intersection.h"

void Extract_Tetra_Cells ( vector<vector<Tetrahedron>>const& zones_of_tetras, int zone_limit, vector<vector<vector<Pl3>>>& tetra_cells )
{
    for (int counter_1 = 0; counter_1 < zone_limit; ++counter_1)
    {
        vector<vector<Pl3>> single_zone_tetra_cells;
        single_zone_tetra_cells.reserve( (int)zones_of_tetras[counter_1].size() );
        
        for (int counter_2 = 0; counter_2 < zones_of_tetras[counter_1].size(); ++counter_2)
        {
            if (to_double( zones_of_tetras[counter_1][counter_2].volume() ) < tiny_num) continue;
            
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
            
            for (int counter_3 = 0; counter_3 < 4; ++counter_3)
            {
                if (abs( tetra_cell[counter_3].a() ) < tiny_num) Pl3( 0, tetra_cell[counter_3].b(), tetra_cell[counter_3].c(), tetra_cell[counter_3].d() );
                if (abs( tetra_cell[counter_3].b() ) < tiny_num) Pl3( tetra_cell[counter_3].a(), 0, tetra_cell[counter_3].c(), tetra_cell[counter_3].d() );
                if (abs( tetra_cell[counter_3].c() ) < tiny_num) Pl3( tetra_cell[counter_3].a(), tetra_cell[counter_3].b(), 0, tetra_cell[counter_3].d() );
                if (abs( tetra_cell[counter_3].d() ) < tiny_num) Pl3( tetra_cell[counter_3].a(), tetra_cell[counter_3].b(), tetra_cell[counter_3].c(), 0 );
            }
            
            if (tetra_cell[0].oriented_side( vertices[3] ) == ON_NEGATIVE_SIDE) tetra_cell[0] = tetra_cell[0].opposite();
            if (tetra_cell[1].oriented_side( vertices[2] ) == ON_NEGATIVE_SIDE) tetra_cell[1] = tetra_cell[1].opposite();
            if (tetra_cell[2].oriented_side( vertices[1] ) == ON_NEGATIVE_SIDE) tetra_cell[2] = tetra_cell[2].opposite();
            if (tetra_cell[3].oriented_side( vertices[0] ) == ON_NEGATIVE_SIDE) tetra_cell[3] = tetra_cell[3].opposite();
            
            single_zone_tetra_cells.push_back( tetra_cell );
        }
        
        tetra_cells.push_back( single_zone_tetra_cells );
    }
}

void Extract_Tetra_Cells_I ( P3 const& centre, vector<vector<Tetrahedron_I>>const& zones_of_tetras, int zone_limit, vector<vector<vector<Pl3>>>& tetra_cells, vector<double>& cell_volume )
{
    vector<double> vec( zone_limit, 0 );
    cell_volume = vec;
    
    for (int counter_1 = 0; counter_1 < zone_limit; ++counter_1)
    {
        vector<vector<Pl3>> single_zone_tetra_cells;
        single_zone_tetra_cells.reserve( (int)zones_of_tetras[counter_1].size() );
        
        for (int counter_2 = 0; counter_2 < zones_of_tetras[counter_1].size(); ++counter_2)
        {
            double tetra_volume = to_double( zones_of_tetras[counter_1][counter_2].volume() );
            
            if (tetra_volume < tiny_num * 1e4) continue;
            
            vector<P3> vertices;
            
            vertices.push_back( zones_of_tetras[counter_1][counter_2].vertex( 0 ) );
            vertices.push_back( zones_of_tetras[counter_1][counter_2].vertex( 1 ) );
            vertices.push_back( zones_of_tetras[counter_1][counter_2].vertex( 2 ) );
            vertices.push_back( zones_of_tetras[counter_1][counter_2].vertex( 3 ) );
            
            double precision = 1e12;
            
            long double x = (long long int)(vertices[0].x() * precision + 0.5);
            long double y = (long long int)(vertices[0].y() * precision + 0.5);
            long double z = (long long int)(vertices[0].z() * precision + 0.5);
            
            x = x / (long double)precision;
            y = y / (long double)precision;
            z = z / (long double)precision;
            
            vertices[0] = P3( x, y, z );
            
            x = (long long int)(vertices[1].x() * precision + 0.5);
            y = (long long int)(vertices[1].y() * precision + 0.5);
            z = (long long int)(vertices[1].z() * precision + 0.5);
            
            x = x / (long double)precision;
            y = y / (long double)precision;
            z = z / (long double)precision;
            
            vertices[1] = P3( x, y, z );
            
            x = (long long int)(vertices[2].x() * precision + 0.5);
            y = (long long int)(vertices[2].y() * precision + 0.5);
            z = (long long int)(vertices[2].z() * precision + 0.5);
            
            x = x / (long double)precision;
            y = y / (long double)precision;
            z = z / (long double)precision;
            
            vertices[2] = P3( x, y, z );
            
            x = (long long int)(vertices[3].x() * precision + 0.5);
            y = (long long int)(vertices[3].y() * precision + 0.5);
            z = (long long int)(vertices[3].z() * precision + 0.5);
            
            x = x / (long double)precision;
            y = y / (long double)precision;
            z = z / (long double)precision;
            
            vertices[3] = P3( x, y, z );
            
            vector<Pl3> tetra_cell;
            
            tetra_cell.push_back( Pl3( vertices[0], vertices[1], vertices[2] ) );
            tetra_cell.push_back( Pl3( vertices[0], vertices[1], vertices[3] ) );
            tetra_cell.push_back( Pl3( vertices[0], vertices[2], vertices[3] ) );
            tetra_cell.push_back( Pl3( vertices[1], vertices[2], vertices[3] ) );
            
            long double a = (long long int)(tetra_cell[0].a() * precision + 0.5);
            long double b = (long long int)(tetra_cell[0].b() * precision + 0.5);
            long double c = (long long int)(tetra_cell[0].c() * precision + 0.5);
            long double d = (long long int)(tetra_cell[0].d() * precision + 0.5);
            
            a = a / (long double)precision;
            b = b / (long double)precision;
            c = c / (long double)precision;
            d = d / (long double)precision;
            
            tetra_cell[0] = Pl3( a, b, c, d );
            
            a = (long long int)(tetra_cell[1].a() * precision + 0.5);
            b = (long long int)(tetra_cell[1].b() * precision + 0.5);
            c = (long long int)(tetra_cell[1].c() * precision + 0.5);
            d = (long long int)(tetra_cell[1].d() * precision + 0.5);
            
            a = a / (long double)precision;
            b = b / (long double)precision;
            c = c / (long double)precision;
            d = d / (long double)precision;
            
            tetra_cell[1] = Pl3( a, b, c, d );
            
            a = (long long int)(tetra_cell[2].a() * precision + 0.5);
            b = (long long int)(tetra_cell[2].b() * precision + 0.5);
            c = (long long int)(tetra_cell[2].c() * precision + 0.5);
            d = (long long int)(tetra_cell[2].d() * precision + 0.5);
            
            a = a / (long double)precision;
            b = b / (long double)precision;
            c = c / (long double)precision;
            d = d / (long double)precision;
            
            tetra_cell[2] = Pl3( a, b, c, d );
            
            a = (long long int)(tetra_cell[3].a() * precision + 0.5);
            b = (long long int)(tetra_cell[3].b() * precision + 0.5);
            c = (long long int)(tetra_cell[3].c() * precision + 0.5);
            d = (long long int)(tetra_cell[3].d() * precision + 0.5);
            
            a = a / (long double)precision;
            b = b / (long double)precision;
            c = c / (long double)precision;
            d = d / (long double)precision;
            
            tetra_cell[3] = Pl3( a, b, c, d );
            
            if (tetra_cell[0].oriented_side( vertices[3] ) == ON_NEGATIVE_SIDE) tetra_cell[0] = tetra_cell[0].opposite();
            if (tetra_cell[1].oriented_side( vertices[2] ) == ON_NEGATIVE_SIDE) tetra_cell[1] = tetra_cell[1].opposite();
            if (tetra_cell[2].oriented_side( vertices[1] ) == ON_NEGATIVE_SIDE) tetra_cell[2] = tetra_cell[2].opposite();
            if (tetra_cell[3].oriented_side( vertices[0] ) == ON_NEGATIVE_SIDE) tetra_cell[3] = tetra_cell[3].opposite();
            
            Sphere s = Sphere( centre, 20 );
            double vol = Sphere_Tetrahedron_Intersection( s, tetra_cell );
            
            if (vol < tiny_num) continue;
            if (vol > tetra_volume + 0.0001) continue;
            
            cell_volume[counter_1] += vol;
            
            single_zone_tetra_cells.push_back( tetra_cell );
        }
        
        //cout << cell_volume[counter_1] << endl;
        
        tetra_cells.push_back( single_zone_tetra_cells );
    }
}
