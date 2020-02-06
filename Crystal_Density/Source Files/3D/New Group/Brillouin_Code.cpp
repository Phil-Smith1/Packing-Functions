#include "Triangle_Area3D.h"
#include "B_Poly.h"
#include "Extract_Tetra_Cells.h"
#include "Triangulate_Zones.h"
#include "Divide_Polyhedron.h"

#include <thread>

typedef Exact_Kernel::Vector_3 V3_E;

void Produce_Cube ( double cube_size, P3_E const& centre, Polyhedron& cube )
{
    V3_E v = centre - ORIGIN;
    
    vector<P3_E> vertices;
    vertices.reserve( 8 );
    
    vertices.push_back( P3_E( cube_size, cube_size, cube_size ) + v );
    vertices.push_back( P3_E( cube_size, cube_size, -cube_size ) + v );
    vertices.push_back( P3_E( cube_size, -cube_size, cube_size ) + v );
    vertices.push_back( P3_E( -cube_size, cube_size, cube_size ) + v );
    vertices.push_back( P3_E( cube_size, -cube_size, -cube_size ) + v );
    vertices.push_back( P3_E( -cube_size, cube_size, -cube_size ) + v );
    vertices.push_back( P3_E( -cube_size, -cube_size, cube_size ) + v );
    vertices.push_back( P3_E( -cube_size, -cube_size, -cube_size ) + v );
    
    convex_hull_3( vertices.begin(), vertices.end(), cube );
}

void Initialise_Cubes ( double cube_size, int num_cubes, P3_E const& centre, vector<Polyhedron>& cubes )
{
    cubes.reserve( num_cubes * num_cubes * num_cubes );
    
    P3_E vertex = P3_E( centre.x() - cube_size, centre.y() - cube_size, centre.z() - cube_size );
    
    cube_size = cube_size / (double)num_cubes;
    
    for (int counter_1 = 0; counter_1 < num_cubes; ++counter_1)
    {
        for (int counter_2 = 0; counter_2 < num_cubes; ++counter_2)
        {
            for (int counter_3 = 0; counter_3 < num_cubes; ++counter_3)
            {
                Polyhedron cube;
                
                P3_E new_vertex = vertex + V3_E( 2 * counter_1 * cube_size, 2 * counter_2 * cube_size, 2 * counter_3 * cube_size );
                
                P3_E new_centre = new_vertex + V3_E( cube_size, cube_size, cube_size );
                
                Produce_Cube( cube_size, new_centre, cube );
                
                cubes.push_back( cube );
            }
        }
    }
}

bool Polyhedron_Inside_Cube ( Polyhedron const& cube, Polyhedron const& poly );

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

void Dividing_Space ( P3_E const& centre, multimap<double, P3_E>const& pts, vector<B_Poly>& final_polys, int zone_limit )
{
    vector<B_Poly> polys;
    polys.reserve( 3000 );
    
    Polyhedron cube;
    
    double cube_size = sqrt( pts.rbegin()->first ) * 0.5;
    
    Produce_Cube( cube_size, centre, cube );
    
    double cube_distance = Max_Distance_To_Polyhedron( centre, cube );
    
    polys.push_back( B_Poly( cube, cube_distance, 1 ) );
    
    vector<Polyhedron> cubes;
    
    int num_cubes = 2;
    
    Initialise_Cubes( cube_size, num_cubes, centre, cubes );
    
    vector<vector<B_Poly>> polygons;
    polygons.reserve( (int)cubes.size() );
    
    for (int counter = 0; counter < cubes.size(); ++counter)
    {
        vector<B_Poly> vec = { B_Poly( cubes[counter], Max_Distance_To_Polyhedron( centre, cubes[counter] ), 1 ) };
        
        polygons.push_back( vec );
    }
    
    double max_radius = 1e10;
    
    double plane_distance = 0;
    
    vector<Pl3_E> planes;
    planes.reserve( (int)pts.size() );
    
    int index = 0;
    
    /*for (auto iter = pts.begin(); iter != pts.end(); ++iter)
    {
        ++index;
        
        if (index == 30)
        {
            vector<B_Poly> copy = polygons[0];
            
            polygons.clear();
            cubes.clear();
            
            for (int counter = 0; counter < copy.size(); ++counter)
            {
                vector<B_Poly> vec = { copy[counter] };
                
                polygons.push_back( vec );
                
                cubes.push_back( copy[counter].poly );
            }
        }
        
        Pl3_E plane = bisector( centre, (*iter).second );
        
        plane_distance = sqrt( to_double( squared_distance( centre, plane ) ) );
        
        if (max_radius < plane_distance + 1e-10) break;
        
        for (int counter = 0; counter < cubes.size(); ++counter)
        {
            Removing_Polyhedrons( centre, planes, plane_distance, polygons[counter], final_polys, zone_limit );
        }
        
        //Removing_Distant_Polyhedrons( centre, planes, plane_distance, polys, final_polys, zone_limit );
        
        cout << polygons[0].size() << " " << final_polys.size() << endl;
        
        if (plane.oriented_side( centre ) == ON_NEGATIVE_SIDE) plane = plane.opposite();
        
        planes.push_back( plane );
        
        for (int counter_3 = 0; counter_3 < polygons.size(); ++counter_3)
        {
            if ((int)polygons[counter_3].size() == 0) continue;
            
            int intersect = Plane_Intersect_Cube( cubes[counter_3], plane );
            
            if (intersect == -1)
            {
                for (int counter_2 = 0; counter_2 < polygons[counter_3].size(); ++counter_2)
                {
                    polygons[counter_3][counter_2].zone += 1;
                }
                
                continue;
            }
            
            else if (intersect == 1) continue;
            
            else
            {
                vector<B_Poly> new_polys;
                new_polys.reserve( (int)polys.size() );
                
                for (int counter_1 = 0; counter_1 < polygons[counter_3].size(); ++counter_1)
                {
                    vector<P3_E> pos_pts;
                    vector<P3_E> neg_pts;
                    vector<P3_E> bdry_pts;
                    
                    for (vertex_iterator v = polygons[counter_3][counter_1].poly.vertices_begin(); v != polygons[counter_3][counter_1].poly.vertices_end(); ++v)
                    {
                        P3_E p = v->point();
                        
                        if (squared_distance( p, plane ) < 1e-10) bdry_pts.push_back( p );
                        
                        else if (plane.oriented_side( p ) == ON_POSITIVE_SIDE) pos_pts.push_back( p );
                        
                        else neg_pts.push_back( p );
                    }
                    
                    if ((int)neg_pts.size() == 0 || (int)pos_pts.size() == 0)
                    {
                        if ((int)pos_pts.size() == 0) ++polygons[counter_3][counter_1].zone;
                        continue;
                    }
                    
                    else
                    {
                        vector<S3_E> segs;
                        
                        for (halfedge_iterator h = polygons[counter_3][counter_1].poly.halfedges_begin(); h != polygons[counter_3][counter_1].poly.halfedges_end(); ++h)
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
                        
                        double dist_pos_poly = Max_Distance_To_Polyhedron( centre, pos_poly );
                        double dist_neg_poly = Max_Distance_To_Polyhedron( centre, neg_poly );
                        
                        polygons[counter_3][counter_1].poly = pos_poly;
                        polygons[counter_3][counter_1].dist = dist_pos_poly;
                        
                        if (polygons[counter_3][counter_1].zone + 1 <= zone_limit) new_polys.push_back( B_Poly( neg_poly, dist_neg_poly, polygons[counter_3][counter_1].zone + 1 ) );
                    }
                }
                
                polygons[counter_3].insert( polygons[counter_3].end(), new_polys.begin(), new_polys.end() );
            }
        }
        
        max_radius = 0;
        
        for (int counter = 0; counter < cubes.size(); ++counter)
        {
            double max_r = Max_Radius_Of_Space( centre, polygons[counter] );
            
            if (max_r > max_radius) max_radius = max_r;
        }
        
        vector<B_Poly> new_polys;
        new_polys.reserve( (int)polys.size() );
        
        for (int counter_1 = 0; counter_1 < polys.size(); ++counter_1)
        {
            vector<P3_E> pos_pts;
            vector<P3_E> neg_pts;
            vector<P3_E> bdry_pts;
            
            for (vertex_iterator v = polys[counter_1].poly.vertices_begin(); v != polys[counter_1].poly.vertices_end(); ++v)
            {
                P3_E p = v->point();
                
                if (squared_distance( p, plane ) < 1e-10) bdry_pts.push_back( p );
                
                else if (plane.oriented_side( p ) == ON_POSITIVE_SIDE) pos_pts.push_back( p );
                
                else neg_pts.push_back( p );
            }
            
            if ((int)neg_pts.size() == 0 || (int)pos_pts.size() == 0)
            {
                if ((int)pos_pts.size() == 0) ++polys[counter_1].zone;
                continue;
            }
            
            else
            {
                vector<S3_E> segs;
                
                for (halfedge_iterator h = polys[counter_1].poly.halfedges_begin(); h != polys[counter_1].poly.halfedges_end(); ++h)
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
                
                double dist_pos_poly = Max_Distance_To_Polyhedron( centre, pos_poly );
                double dist_neg_poly = Max_Distance_To_Polyhedron( centre, neg_poly );
                
                polys[counter_1].poly = pos_poly;
                polys[counter_1].dist = dist_pos_poly;
                
                if (polys[counter_1].zone + 1 <= zone_limit) new_polys.push_back( B_Poly( neg_poly, dist_neg_poly, polys[counter_1].zone + 1 ) );
            }
        }
        
        polys.insert( polys.end(), new_polys.begin(), new_polys.end() );
        
        max_radius = Max_Radius_Of_Space( centre, polys );
    }
    
    for (int counter = 0; counter < cubes.size(); ++counter)
    {
        Removing_Distant_Polyhedrons( centre, planes, plane_distance, polygons[counter], final_polys, zone_limit );
    }
    
    for (int counter = 0; counter < cubes.size(); ++counter)
    {
        final_polys.insert( final_polys.end(), polygons[counter].begin(), polygons[counter].end() );
    }
    
    Removing_Distant_Polyhedrons( centre, planes, plane_distance, polys, final_polys, zone_limit );
    
    final_polys.insert( final_polys.end(), polys.begin(), polys.end() );*/
    
    vector<vector<B_Poly>> fin_polys( (int)cubes.size() );
    vector<thread> thr;
    
    for (int counter = 0; counter < cubes.size(); ++counter)
    {
        fin_polys[counter].reserve( 1000 );
    }
    
    for (int counter = 0; counter < cubes.size(); ++counter)
    {
        vector<B_Poly> fin_poly = fin_polys[counter];
        
        //cout << "Thread " << counter + 1 << " about to start." << endl;
        this_thread::sleep_for( chrono::milliseconds( 2 ) );
        thr.push_back( thread( Divide_Polyhedron, centre, pts, cubes[counter], ref( fin_polys[counter] ), zone_limit ) );
    }
    
    for (int counter = 0; counter < cubes.size(); ++counter)
    {
        thr[counter].join();
    }
    
    for (int counter_1 = 0; counter_1 < cubes.size(); ++counter_1)
    {
        for (int counter_2 = 0; counter_2 < fin_polys[counter_1].size(); ++counter_2)
        {
            final_polys.push_back( fin_polys[counter_1][counter_2] );
            //final_polys.push_back( polys[0] );
        }
    }
}

void Compute_Brillouin_Zones ( multimap<double, P3_E> const& pts, int zone_limit, P3_E const& centre, vector<vector<Tetrahedron>>& zones_of_tetras )
{
    vector<B_Poly> polys;
    
    Dividing_Space( centre, pts, polys, zone_limit );
    
    cout << polys.size() << endl;
    
    Triangulate_Zones( polys, zone_limit, zones_of_tetras );
}
