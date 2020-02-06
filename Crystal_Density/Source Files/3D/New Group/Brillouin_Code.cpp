#include "Triangle_Area3D.h"
#include "B_Poly.h"

#include <thread>
#include <mutex>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_3.h>
#include <CGAL/Triangulation_3.h>

using namespace std;

typedef K::Plane_3 Pl3;

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

void Removing_Distant_Polygons ( P3_E const& centre, vector<Pl3_E>const& planes, double plane_distance, vector<B_Poly>& polys, vector<B_Poly>& final_polys, int zone_limit )
{
    vector<B_Poly> remaining_polys;
    remaining_polys.reserve( polys.size() );
    vector<B_Poly> inside_polys;
    inside_polys.reserve( polys.size() );
    
    for (int counter = 0; counter < polys.size(); ++counter)
    {
        if (polys[counter].zone <= zone_limit)
        {
            if (polys[counter].dist < plane_distance + tiny_num) inside_polys.push_back( polys[counter] );
            
            else remaining_polys.push_back( polys[counter] );
        }
    }
    
    polys = remaining_polys;
    final_polys.insert( final_polys.end(), inside_polys.begin(), inside_polys.end() );
}

double Max_Radius_Of_Space ( P3_E const& centre, vector<B_Poly>& polys )
{
    double max_radius = 0;
    
    for (int counter = 0; counter < polys.size(); ++counter)
    {
        if (polys[counter].dist > max_radius) max_radius = polys[counter].dist;
    }
    
    return max_radius;
}

int Plane_Intersect_Cube ( Polyhedron& cube, Pl3_E const& plane )
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

void Divide_Polygon ( P3_E const centre, multimap<double, P3_E>const pts, Polyhedron cube, vector<B_Poly>& final_polys, int zone_limit )
{
    mutex m1;
    
    m1.lock();
    
    vector<B_Poly> polygons;
    polygons.push_back( B_Poly( cube, Max_Distance_To_Polygon( centre, cube ), 1 ) );
    
    double max_radius = 1e10;
    
    double plane_distance = 0;
    
    vector<Pl3_E> planes;
    planes.reserve( (int)pts.size() );
    
    for (auto iter = pts.begin(); iter != pts.end(); ++iter)
    {
        Pl3_E plane = bisector( centre, (*iter).second );
        
        plane_distance = sqrt( to_double( squared_distance( centre, plane ) ) );
        
        if (max_radius < plane_distance + 1e-10) break;
        
        Removing_Distant_Polygons( centre, planes, plane_distance, polygons, final_polys, zone_limit );
        
        if (plane.oriented_side( centre ) == ON_NEGATIVE_SIDE) plane = plane.opposite();
        
        planes.push_back( plane );
        
        if ((int)polygons.size() == 0) continue;
        
        int intersect = Plane_Intersect_Cube( cube, plane );
        
        if (intersect == -1)
        {
            for (int counter_2 = 0; counter_2 < polygons.size(); ++counter_2)
            {
                polygons[counter_2].zone += 1;
            }
            
            continue;
        }
        
        else if (intersect == 1) continue;
        
        else
        {
            vector<B_Poly> new_polys;
            new_polys.reserve( (int)polygons.size() );
            
            for (int counter_1 = 0; counter_1 < polygons.size(); ++counter_1)
            {
                vector<P3_E> pos_pts;
                vector<P3_E> neg_pts;
                vector<P3_E> bdry_pts;
                
                for (vertex_iterator v = polygons[counter_1].poly.vertices_begin(); v != polygons[counter_1].poly.vertices_end(); ++v)
                {
                    P3_E p = v->point();
                    
                    if (squared_distance( p, plane ) < 1e-10) bdry_pts.push_back( p );
                    
                    else if (plane.oriented_side( p ) == ON_POSITIVE_SIDE) pos_pts.push_back( p );
                    
                    else neg_pts.push_back( p );
                }
                
                if ((int)neg_pts.size() == 0 || (int)pos_pts.size() == 0)
                {
                    if ((int)pos_pts.size() == 0) ++polygons[counter_1].zone;
                    continue;
                }
                
                else
                {
                    vector<S3_E> segs;
                    
                    for (halfedge_iterator h = polygons[counter_1].poly.halfedges_begin(); h != polygons[counter_1].poly.halfedges_end(); ++h)
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
                    
                    double dist_pos_poly = Max_Distance_To_Polygon( centre, pos_poly );
                    double dist_neg_poly = Max_Distance_To_Polygon( centre, neg_poly );
                    
                    polygons[counter_1].poly = pos_poly;
                    polygons[counter_1].dist = dist_pos_poly;
                    
                    if (polygons[counter_1].zone + 1 <= zone_limit) new_polys.push_back( B_Poly( neg_poly, dist_neg_poly, polygons[counter_1].zone + 1 ) );
                }
            }
            
            polygons.insert( polygons.end(), new_polys.begin(), new_polys.end() );
        }
        
        max_radius = Max_Radius_Of_Space( centre, polygons );
    }
    
    Removing_Distant_Polygons( centre, planes, plane_distance, polygons, final_polys, zone_limit );
    
    final_polys.insert( final_polys.end(), polygons.begin(), polygons.end() );
    
    cout << final_polys.size() << endl;
    
    m1.unlock();
}

void Dividing_Space ( P3_E const& centre, multimap<double, P3_E>const& pts, vector<B_Poly>& final_polys, int zone_limit )
{
    vector<B_Poly> polys;
    polys.reserve( 3000 );
    
    Polyhedron cube;
    
    double cube_size = sqrt( pts.rbegin()->first ) * 0.5;
    
    Produce_Cube( cube_size, centre, cube );
    
    double cube_distance = Max_Distance_To_Polygon( centre, cube );
    
    polys.push_back( B_Poly( cube, cube_distance, 1 ) );
    
    vector<Polyhedron> cubes;
    
    int num_cubes = 2;
    
    Initialise_Cubes( cube_size, num_cubes, centre, cubes );
    
    vector<vector<B_Poly>> polygons;
    polygons.reserve( (int)cubes.size() );
    
    for (int counter = 0; counter < cubes.size(); ++counter)
    {
        vector<B_Poly> vec = { B_Poly( cubes[counter], Max_Distance_To_Polygon( centre, cubes[counter] ), 1 ) };
        
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
            Removing_Distant_Polygons( centre, planes, plane_distance, polygons[counter], final_polys, zone_limit );
        }
        
        //Removing_Distant_Polygons( centre, planes, plane_distance, polys, final_polys, zone_limit );
        
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
                        
                        double dist_pos_poly = Max_Distance_To_Polygon( centre, pos_poly );
                        double dist_neg_poly = Max_Distance_To_Polygon( centre, neg_poly );
                        
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
                
                double dist_pos_poly = Max_Distance_To_Polygon( centre, pos_poly );
                double dist_neg_poly = Max_Distance_To_Polygon( centre, neg_poly );
                
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
        Removing_Distant_Polygons( centre, planes, plane_distance, polygons[counter], final_polys, zone_limit );
    }
    
    for (int counter = 0; counter < cubes.size(); ++counter)
    {
        final_polys.insert( final_polys.end(), polygons[counter].begin(), polygons[counter].end() );
    }
    
    Removing_Distant_Polygons( centre, planes, plane_distance, polys, final_polys, zone_limit );
    
    final_polys.insert( final_polys.end(), polys.begin(), polys.end() );*/
    
    vector<vector<B_Poly>> fin_polys( (int)cubes.size() );
    vector<thread> thr;
    
    for (int counter = 0; counter < cubes.size(); ++counter)
    {
        fin_polys[counter].reserve( 1000 );
        //fin_polys[counter].clear();
    }
    
    vector<B_Poly> fin_poly_1;
    vector<B_Poly> fin_poly_2;
    vector<B_Poly> fin_poly_3;
    vector<B_Poly> fin_poly_4;
    vector<B_Poly> fin_poly_5;
    vector<B_Poly> fin_poly_6;
    vector<B_Poly> fin_poly_7;
    vector<B_Poly> fin_poly_8;
    
    P3_E centre1 = centre;
    P3_E centre2 = centre;
    P3_E centre3 = centre;
    P3_E centre4 = centre;
    P3_E centre5 = centre;
    P3_E centre6 = centre;
    P3_E centre7 = centre;
    P3_E centre8 = centre;
    
    multimap<double, P3_E> pts1 = pts;
    multimap<double, P3_E> pts2 = pts;
    multimap<double, P3_E> pts3 = pts;
    multimap<double, P3_E> pts4 = pts;
    multimap<double, P3_E> pts5 = pts;
    multimap<double, P3_E> pts6 = pts;
    multimap<double, P3_E> pts7 = pts;
    multimap<double, P3_E> pts8 = pts;
    
    int z1 = zone_limit;
    int z2 = zone_limit;
    int z3 = zone_limit;
    int z4 = zone_limit;
    int z5 = zone_limit;
    int z6 = zone_limit;
    int z7 = zone_limit;
    int z8 = zone_limit;
    
    Polyhedron cube1 = cubes[0];
    Polyhedron cube2 = cubes[1];
    Polyhedron cube3 = cubes[2];
    Polyhedron cube4 = cubes[3];
    Polyhedron cube5 = cubes[4];
    Polyhedron cube6 = cubes[5];
    Polyhedron cube7 = cubes[6];
    Polyhedron cube8 = cubes[7];
    
    /*thread thread_1( Divide_Polygon, centre, pts, cube1, ref( fin_poly_1 ), zone_limit );
    thread thread_2( Divide_Polygon, centre, pts, cube2, ref( fin_poly_2 ), zone_limit );
    thread thread_3( Divide_Polygon, centre, pts, cube3, ref( fin_poly_3 ), zone_limit );
    thread thread_4( Divide_Polygon, centre, pts, cube4, ref( fin_poly_4 ), zone_limit );
    thread thread_5( Divide_Polygon, centre, pts, cube5, ref( fin_poly_5 ), zone_limit );
    thread thread_6( Divide_Polygon, centre, pts, cube6, ref( fin_poly_6 ), zone_limit );
    thread thread_7( Divide_Polygon, centre, pts, cube7, ref( fin_poly_7 ), zone_limit );
    thread thread_8( Divide_Polygon, centre, pts, cube8, ref( fin_poly_8 ), zone_limit );
    
    thread_1.join();
    thread_2.join();
    thread_3.join();
    thread_4.join();
    thread_5.join();
    thread_6.join();
    thread_7.join();
    thread_8.join();*/
    
    for (int counter = 0; counter < cubes.size(); ++counter)
    {
        vector<B_Poly> fin_poly = fin_polys[counter];
        
        //cout << "Thread " << counter + 1 << " about to start." << endl;
        this_thread::sleep_for( chrono::milliseconds( 2 ) );
        thr.push_back( thread( Divide_Polygon, centre, pts, cubes[counter], ref( fin_polys[counter] ), zone_limit ) );
    }
    
    for (int counter = 0; counter < cubes.size(); ++counter)
    {
        thr[counter].join();
    }
    
    for (int counter_1 = 0; counter_1 < cubes.size(); ++counter_1)
    {
        for (int counter_2 = 0; counter_2 < fin_polys[counter_1].size(); ++counter_2)
        {
            //final_polys.push_back( fin_polys[counter_1][counter_2] );
            final_polys.push_back( polys[0] );
        }
    }
}

void Compute_Brillouin_Zones ( int perim, int zone_limit, P3_E const& centre, vector<vector<Tetrahedron>>& zones_of_tetras )
{
    V3_E v1 = V3_E( 5 / (double)6, -1 / (double)6, -1 / (double)6 );
    V3_E v2 = V3_E( -1 / (double)6, 5 / (double)6, -1 / (double)6 );
    V3_E v3 = V3_E( -1 / (double)6, -1 / (double)6, 5 / (double)6 );
    
    multimap<double, P3_E> pts;
    
    for (int counter_1 = -perim; counter_1 < perim + 1; ++counter_1)
    {
        for (int counter_2 = -perim; counter_2 < perim + 1; ++counter_2)
        {
            for (int counter_3 = -perim; counter_3 < perim + 1; ++counter_3)
            {
                if (counter_1 == 0 && counter_2 == 0 && counter_3 == 0) continue;
                
                V3_E v = counter_1 * v1 + counter_2 * v2 + counter_3 * v3;
                
                P3_E p = P3_E( v.x(), v.y(), v.z() );
                
                double dist = to_double( squared_distance( centre, p ) );
                
                pts.insert( pair<double, P3_E>( dist, p ) );
            }
        }
    }
    
    vector<B_Poly> polys;
    
    Dividing_Space( centre, pts, polys, zone_limit );
    
    cout << polys.size() << endl;
    
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

void Extract_Tetra_Cells ( vector<vector<Tetrahedron>>const& zones_of_tetras, int zone_limit, vector<vector<vector<Pl3>>>& tetra_cells )
{
    for (int counter_1 = 0; counter_1 < zone_limit; ++counter_1)
    {
        vector<vector<Pl3>> single_zone_tetra_cells;
        single_zone_tetra_cells.reserve( (int)zones_of_tetras[counter_1].size() );
        
        for (int counter_2 = 0; counter_2 < zones_of_tetras[counter_1].size(); ++counter_2)
        {
            if (to_double( zones_of_tetras[counter_1][counter_2].volume() ) < tiny_num) continue;
            
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
