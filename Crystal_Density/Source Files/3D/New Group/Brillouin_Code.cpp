#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/convex_hull_3.h>
#include <CGAL/Triangulation_3.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 P3;
typedef K::Plane_3 Pl3;

typedef Exact_predicates_exact_constructions_kernel Exact_Kernel;
typedef Polyhedron_3<Exact_Kernel> Polyhedron;
typedef Tetrahedron_3<Exact_Kernel> Tetrahedron;
typedef Triangulation_3<Exact_Kernel> Triangulation;

typedef Exact_Kernel::Point_3 P3_E;
typedef Exact_Kernel::Vector_3 V3_E;
typedef Exact_Kernel::Segment_3 S3_E;
typedef Exact_Kernel::Plane_3 Pl3_E;
typedef Exact_Kernel::Intersect_3 I3;

typedef Polyhedron::Halfedge_iterator halfedge_iterator;
typedef Polyhedron::Vertex_iterator vertex_iterator;

typedef Triangulation::Finite_cells_iterator cells_iterator;

void Produce_Large_Cube ( double cube_size, Polyhedron& cube )
{
    vector<P3_E> vertices;
    vertices.reserve( 8 );
    
    vertices.push_back( P3_E( cube_size, cube_size, cube_size ) );
    vertices.push_back( P3_E( cube_size, cube_size, -cube_size ) );
    vertices.push_back( P3_E( cube_size, -cube_size, cube_size ) );
    vertices.push_back( P3_E( -cube_size, cube_size, cube_size ) );
    vertices.push_back( P3_E( cube_size, -cube_size, -cube_size ) );
    vertices.push_back( P3_E( -cube_size, cube_size, -cube_size ) );
    vertices.push_back( P3_E( -cube_size, -cube_size, cube_size ) );
    vertices.push_back( P3_E( -cube_size, -cube_size, -cube_size ) );
    
    convex_hull_3( vertices.begin(), vertices.end(), cube );
}

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

double Max_Distance_To_Polygon ( P3_E const& centre, Polyhedron& poly )
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

void Removing_Distant_Polygons ( P3_E const& centre, vector<Pl3_E>const& planes, double plane_distance, vector<Polyhedron>& polys, vector<Polyhedron>& final_polys, int zone_limit, bool remove_inside_zones )
{
    vector<vector<Polyhedron>> remaining_polys;
    remaining_polys.resize( zone_limit );
    
    vector<double> distances( zone_limit, -1 );
    
    for (int counter = 0; counter < polys.size(); ++counter)
    {
        int zone = Compute_Zone( centre, planes, polys[counter] );
        
        if (zone <= zone_limit)
        {
            if (remove_inside_zones)
            {
                double dist = Max_Distance_To_Polygon( centre, polys[counter] );
                
                if (dist > distances[zone - 1]) distances[zone - 1] = dist;
            }
            
            remaining_polys[zone - 1].push_back( polys[counter] );
        }
    }
    
    int remove_zones = -1;
    
    for (int counter = 0; counter < zone_limit; ++counter)
    {
        if (plane_distance + 1e-10 > distances[counter] && distances[counter] > 0) remove_zones = counter;
    }
    
    vector<Polyhedron> combine_polys;
    
    for (int counter = 0; counter < zone_limit; ++counter)
    {
        if (counter <= remove_zones) final_polys.insert( final_polys.end(), remaining_polys[counter].begin(), remaining_polys[counter].end() );
        
        else combine_polys.insert( combine_polys.end(), remaining_polys[counter].begin(), remaining_polys[counter].end() );
    }
    
    polys = combine_polys;
}

double Max_Radius_Of_Space ( P3_E const& centre, vector<Polyhedron>& polys )
{
    double max_radius = 0;
    
    for (int counter = 0; counter < polys.size(); ++counter)
    {
        double dist = Max_Distance_To_Polygon( centre, polys[counter] );
        
        if (dist > max_radius) max_radius = dist;
    }
    
    return max_radius;
}

void Dividing_Space ( P3_E const& centre, multimap<double, P3_E>const& pts, vector<Pl3_E>& planes, vector<Polyhedron>& final_polys, int cube_size, int zone_limit )
{
    Polyhedron cube;
    
    Produce_Large_Cube( cube_size, cube );
    
    vector<Polyhedron> polys;
    polys.reserve( 3000 );
    
    polys.push_back( cube );
    
    double max_radius = 10;
    
    double plane_distance = 0;
    
    int last_polys_size = 0;
    
    planes.reserve( (int)pts.size() );
    
    int index = 0;
    
    for (auto iter = pts.begin(); iter != pts.end(); ++iter)
    {
        Pl3_E plane = bisector( centre, (*iter).second );
        
        if (plane.oriented_side( centre ) == ON_NEGATIVE_SIDE) plane = plane.opposite();
        
        plane_distance = sqrt( to_double( squared_distance( centre, plane ) ) );
        
        if (max_radius < plane_distance + 1e-10) break;
        
        planes.push_back( plane );
        
        vector<Polyhedron> new_polys;
        new_polys.reserve( (int)polys.size() );
        
        for (int counter_1 = 0; counter_1 < polys.size(); ++counter_1)
        {
            vector<P3_E> pos_pts;
            vector<P3_E> neg_pts;
            vector<P3_E> bdry_pts;
            
            for (vertex_iterator v = polys[counter_1].vertices_begin(); v != polys[counter_1].vertices_end(); ++v)
            {
                P3_E p = v->point();
                
                if (squared_distance( p, plane ) < 1e-10) bdry_pts.push_back( p );
                
                else if (plane.oriented_side( p ) == ON_POSITIVE_SIDE) pos_pts.push_back( p );
                
                else neg_pts.push_back( p );
            }
            
            if ((int)neg_pts.size() == 0 || (int)pos_pts.size() == 0) continue;
            
            else
            {
                vector<S3_E> segs;
                
                for (halfedge_iterator h = polys[counter_1].halfedges_begin(); h != polys[counter_1].halfedges_end(); ++h)
                {
                    P3_E p1 = (h->vertex())->point();
                    P3_E p2 = (h->prev()->vertex())->point();
                    
                    segs.push_back( S3_E( p1, p2 ) );
                    
                    ++h;
                }
                
                vector<P3_E> pts;
                
                for (int counter_2 = 0; counter_2 < segs.size(); ++counter_2)
                {
                    cpp11::result_of<I3(Pl3_E, S3_E)>::type result = intersection( plane, segs[counter_2] );
                    
                    if (result)
                    {
                        if (const P3_E * p = boost::get<P3_E>( &*result )) pts.push_back( *p );
                        
                        else
                        {
                            pts.push_back( segs[counter_2].source() );
                            pts.push_back( segs[counter_2].target() );
                        }
                    }
                }
                
                pos_pts.insert( pos_pts.end(), pts.begin(), pts.end() );
                pos_pts.insert( pos_pts.end(), bdry_pts.begin(), bdry_pts.end() );
                neg_pts.insert( neg_pts.end(), pts.begin(), pts.end() );
                neg_pts.insert( neg_pts.end(), bdry_pts.begin(), bdry_pts.end() );
                
                Polyhedron pos_poly, neg_poly;
                
                convex_hull_3( pos_pts.begin(), pos_pts.end(), pos_poly );
                convex_hull_3( neg_pts.begin(), neg_pts.end(), neg_poly );
                
                polys[counter_1] = pos_poly;
                
                int zone = Compute_Zone( centre, planes, neg_poly );
                
                if (zone <= zone_limit) new_polys.push_back( neg_poly );
            }
        }
        
        polys.insert( polys.end(), new_polys.begin(), new_polys.end() );
        
        if ((int)polys.size() > last_polys_size + 250)
        {
            ++index;
            
            bool remove_inside_zones = false;
            
            if (index % 4 == 0) remove_inside_zones = true;
            
            Removing_Distant_Polygons( centre, planes, plane_distance, polys, final_polys, zone_limit, remove_inside_zones );
            
            last_polys_size = (int)polys.size();
        }
        
        if ((int)planes.size() % 10 == 0) max_radius = Max_Radius_Of_Space( centre, polys );
    }
    
    Removing_Distant_Polygons( centre, planes, plane_distance, polys, final_polys, zone_limit, false );
    
    final_polys.insert( final_polys.end(), polys.begin(), polys.end() );
}

void Compute_Brillouin_Zones ( int perim, int zone_limit, double cube_size, P3_E const& centre, vector<vector<Tetrahedron>>& zones_of_tetras )
{
    multimap<double, P3_E> pts;
    
    for (int counter_1 = -perim; counter_1 < perim + 1; ++counter_1)
    {
        for (int counter_2 = -perim; counter_2 < perim + 1; ++counter_2)
        {
            for (int counter_3 = -perim; counter_3 < perim + 1; ++counter_3)
            {
                if (counter_1 == 0 && counter_2 == 0 && counter_3 == 0) continue;
                
                P3_E p = P3_E( counter_1, counter_2, counter_3 );
                
                double dist = to_double( squared_distance( centre, p ) );
                
                pts.insert( pair<double, P3_E>( dist, p ) );
            }
        }
    }
    
    vector<Pl3_E> bisectors;
    vector<Polyhedron> polys;
    
    Dividing_Space( centre, pts, bisectors, polys, cube_size, zone_limit );
    
    cout << polys.size() << endl;
    
    vector<vector<Polyhedron>> zones_of_polys( zone_limit );
    
    for (int counter = 0; counter < polys.size(); ++counter)
    {
        int zone = Compute_Zone( centre, bisectors, polys[counter] );
        
        zones_of_polys[zone - 1].push_back( polys[counter] );
    }
    
    zones_of_tetras.resize( zone_limit );
    
    for (int counter_1 = 0; counter_1 < zone_limit; ++counter_1)
    {
        for (int counter_2 = 0; counter_2 < zones_of_polys[counter_1].size(); ++counter_2)
        {
            zones_of_tetras[counter_1].reserve( (int)zones_of_polys[counter_1].size() );
            
            Polyhedron poly = zones_of_polys[counter_1][counter_2];
            vector<P3_E> vertices;
            
            for (vertex_iterator v = poly.vertices_begin(); v != poly.vertices_end(); ++v)
            {
                P3_E p = v->point();
                
                vertices.push_back( p );
            }
            
            Triangulation T( vertices.begin(), vertices.end() );
            
            for (cells_iterator c = T.Triangulation::finite_cells_begin(); c != T.Triangulation::finite_cells_end(); ++c)
            {
                Tetrahedron tetra = T.Triangulation::tetrahedron( c );
                
                zones_of_tetras[counter_1].push_back( tetra );
            }
        }
    }
}

void Extract_Tetra_Cells ( vector<vector<Tetrahedron>>const& zones_of_tetras, int zone_limit, vector<vector<vector<Pl3>>>& tetra_cells )
{
    for (int counter_1 = 0; counter_1 < zone_limit; ++counter_1)
    {
        vector<vector<Pl3>> single_zone_tetra_cells;
        single_zone_tetra_cells.reserve( (int)zones_of_tetras[counter_1].size() );
        
        for (int counter_2 = 0; counter_2 < zones_of_tetras[counter_1].size(); ++counter_2)
        {
            vector<Pl3> tetra_cell;
            
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
