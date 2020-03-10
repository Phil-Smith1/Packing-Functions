#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_2.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/convex_hull_2.h>

#include <thread>

#include "B_Poly_2D.h"

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;
typedef K::Vector_2 V2;
typedef K::Triangle_2 Tri;
typedef K::Line_2 L2;
typedef K::Segment_2 S2;

typedef Triangulation_2<K> Triangulation_2D;
typedef Triangulation_2D::Vertex_circulator Vertex_circulator;
typedef Triangulation_2D::Finite_faces_iterator faces_iterator;

typedef Polygon::Vertex_iterator vertex_iterator_2D;

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

typedef K::Intersect_2 I2;

typedef Polygon::Edge_const_iterator edge_iterator;

void Generate_Cube_2D ( double cube_size, P2 const& centre, Polygon& square )
{
    V2 v = centre - ORIGIN;
    
    vector<P2> vertices;
    vertices.reserve( 4 );
    
    vertices.push_back( P2( cube_size, cube_size) + v );
    vertices.push_back( P2( cube_size, -cube_size ) + v );
    vertices.push_back( P2( -cube_size, +cube_size ) + v );
    vertices.push_back( P2( -cube_size, -cube_size ) + v );
    
    vector<P2> results;
    
    convex_hull_2( vertices.begin(), vertices.end(), back_inserter( results ) );
    
    square = Polygon( results.begin(), results.end() );
}

double Max_Distance_To_Polyhedron_2D ( P2 const& centre, Polygon& poly )
{
    double max_radius = 0;
    
    for (vertex_iterator_2D v = poly.vertices_begin(); v != poly.vertices_end(); ++v)
    {
        P2 p = P2( v->x(), v->y() );
        
        double dist = squared_distance( p, centre );
        
        if (dist > max_radius) max_radius = dist;
    }
    
    return sqrt( max_radius );
}

void Removing_Polyhedrons_2D ( P2 const& centre, vector<L2>const& planes, double plane_distance, vector<B_Poly_2D>& polys, vector<B_Poly_2D>& final_polys, int zone_limit )
{
    vector<B_Poly_2D> remaining_polys;
    remaining_polys.reserve( polys.size() );
    vector<B_Poly_2D> inside_polys;
    inside_polys.reserve( polys.size() );
    
    for (int counter = 0; counter < polys.size(); ++counter)
    {
        //cout << polys[counter].zone << endl;
        if (polys[counter].zone <= zone_limit)
        {
            if (polys[counter].dist < plane_distance + tiny_num) inside_polys.push_back( polys[counter] );
            
            else remaining_polys.push_back( polys[counter] );
        }
    }
    
    polys = remaining_polys;
    final_polys.insert( final_polys.end(), inside_polys.begin(), inside_polys.end() );
    
    //cout << polys.size() << endl;
    //cout << final_polys.size() << endl << endl;
}

int Plane_Intersect_Polyhedron_2D ( Polygon& cube, L2 const& plane )
{
    bool pos = false, neg = false;
    
    for (vertex_iterator_2D v = cube.vertices_begin(); v != cube.vertices_end(); ++v)
    {
        P2 p = P2( v->x(), v->y() );
        
        if (squared_distance( p, plane ) < 1e-10) continue;
        
        else if (plane.oriented_side( p ) == ON_POSITIVE_SIDE) pos = true;
        
        else neg = true;
        
        if (pos && neg) break;
    }
    
    if (!pos || !neg)
    {
        if (!pos) return -1;
        
        else return 1;
    }
    
    else return 0;
}

double Max_Radius_Of_Space_2D ( P2 const& centre, vector<B_Poly_2D>& polys )
{
    double max_radius = 0;
    
    for (int counter = 0; counter < polys.size(); ++counter)
    {
        if (polys[counter].dist > max_radius) max_radius = polys[counter].dist;
    }
    
    return max_radius;
}

void Divide_Polyhedron_2D ( P2 const centre, multimap<double, P2>const pts, Polygon poly, int starting_zone, vector<B_Poly_2D>& final_polys, int zone_limit )
{
    vector<B_Poly_2D> polys;
    polys.push_back( B_Poly_2D( poly, Max_Distance_To_Polyhedron_2D( centre, poly ), starting_zone ) );
    
    double max_radius = 1e10;
    double plane_distance = 0;
    
    vector<L2> planes;
    planes.reserve( (int)pts.size() );
    
    double precision = 1e12;
    
    bool remove_polys = false;
    
    for (auto iter = pts.begin(); iter != pts.end(); ++iter)
    {
        L2 plane = bisector( centre, (*iter).second );
        
        long double a = (long long int)(plane.a() * precision + 0.5);
        long double b = (long long int)(plane.b() * precision + 0.5);
        long double c = (long long int)(plane.c() * precision + 0.5);
        
        a = a / (long double)precision;
        b = b / (long double)precision;
        c = c / (long double)precision;
        
        plane = L2( a, b, c );
        
        double plane_distance = sqrt( to_double( squared_distance( centre, plane ) ) );
        
        if (max_radius < plane_distance + 1e-10) break;
        
        {
            mutex m1;
            
            lock_guard<mutex> lock_guard( m1 );
            
            if (remove_polys) Removing_Polyhedrons_2D( centre, planes, plane_distance, polys, final_polys, zone_limit );
        }
        
        if (plane.oriented_side( centre ) == ON_NEGATIVE_SIDE) plane = plane.opposite();
        
        planes.push_back( plane );
        
        if ((int)polys.size() == 0) break;
        
        int intersect = Plane_Intersect_Polyhedron_2D( poly, plane );
        
        if (intersect == -1)
        {
            for (int counter = 0; counter < polys.size(); ++counter)
            {
                polys[counter].zone += 1;
            }
            
            remove_polys = true;
            
            continue;
        }
        
        else if (intersect == 1)
        {
            remove_polys = false;
            continue;
        }
        
        else
        {
            remove_polys = true;
            
            vector<B_Poly_2D> new_polys;
            new_polys.reserve( (int)polys.size() );
            
            for (int counter_1 = 0; counter_1 < polys.size(); ++counter_1)
            {
                vector<P2> pos_pts;
                vector<P2> neg_pts;
                vector<P2> bdry_pts;
                
                for (vertex_iterator_2D v = polys[counter_1].poly.vertices_begin(); v != polys[counter_1].poly.vertices_end(); ++v)
                {
                    P2 p = P2( v->x(), v->y() );
                    
                    if (squared_distance( p, plane ) < tiny_num) bdry_pts.push_back( p );
                    
                    else if (plane.oriented_side( p ) == ON_POSITIVE_SIDE) pos_pts.push_back( p );
                    
                    else neg_pts.push_back( p );
                }
                
                if ((int)neg_pts.size() == 1 && squared_distance( neg_pts[0], plane ) < 1e-3) continue;
                
                else if ((int)pos_pts.size() == 1 && squared_distance( pos_pts[0], plane ) < 1e-3)
                {
                    ++polys[counter_1].zone;
                    continue;
                }
                
                else if ((int)neg_pts.size() == 0 || (int)pos_pts.size() == 0)
                {
                    if ((int)pos_pts.size() == 0) ++polys[counter_1].zone;
                    continue;
                }
                
                else
                {
                    vector<S2> segs;
                    
                    for (edge_iterator h = polys[counter_1].poly.edges_begin(); h != polys[counter_1].poly.edges_end(); ++h)
                    {
                        P2 p1 = h->source();
                        P2 p2 = h->target();
                        
                        long double x = (long long int)(p1.x() * precision + 0.5);
                        long double y = (long long int)(p1.y() * precision + 0.5);
                        
                        x = x / (long double)precision;
                        y = y / (long double)precision;
                        
                        p1 = P2( x, y );
                        
                        x = (long long int)(p2.x() * precision + 0.5);
                        y = (long long int)(p2.y() * precision + 0.5);
                        
                        x = x / (long double)precision;
                        y = y / (long double)precision;
                        
                        p2 = P2( x, y );
                        
                        segs.push_back( S2( p1, p2 ) );
                    }
                    
                    vector<P2> pts;
                    
                    for (int counter_2 = 0; counter_2 < segs.size(); ++counter_2)
                    {
                        if (CGAL::do_intersect( plane, segs[counter_2] ))
                        {
                            cpp11::result_of<I2(L2, L2)>::type result = intersection( plane, L2( segs[counter_2].source(), segs[counter_2].target() ) );
                            
                            if (result)
                            {
                                if (const P2 * p = boost::get<P2>( &*result ))
                                {
                                    if (squared_distance( *p, segs[counter_2].source() ) > tiny_num && squared_distance( *p, segs[counter_2].target() ) > tiny_num)
                                    {
                                        P2 pt = *p;
                                        
                                        long double x = (long long int)(pt.x() * precision + 0.5);
                                        long double y = (long long int)(pt.y() * precision + 0.5);
                                        
                                        x = x / (long double)precision;
                                        y = y / (long double)precision;
                                        
                                        pt = P2( x, y );
                                        
                                        pts.push_back( pt );
                                    }
                                }
                            }
                            
                            else cout << "Wrong!" << endl;
                        }
                    }
                    
                    /*if (polys[counter_1].zone == 1)
                    {
                        cout << endl;
                        cpp11::result_of<I2(L2, S2)>::type result1 = intersection( plane, segs[1] );
                        cpp11::result_of<I2(L2, S2)>::type result2 = intersection( plane, segs[3] );
                        cpp11::result_of<I2(L2, L2)>::type result3 = intersection( plane, L2( segs[1].source(), segs[1].target() ) );
                        cpp11::result_of<I2(L2, L2)>::type result4 = intersection( plane, L2( segs[3].source(), segs[3].target() ) );
                        if (result1) cout << "result1" << endl;
                        if (result2) cout << "result2" << endl;
                        if (result3) cout << "result3" << endl;
                        if (result4) cout << "result4" << endl;
                        cout << CGAL::do_intersect( plane, segs[1] ) << endl;
                        cout << CGAL::do_intersect( plane, segs[3] ) << endl;
                        cout << segs[1].source() << endl;
                        cout << segs[1].target() << endl;
                        cout << segs[3].source() << endl;
                        cout << segs[3].target() << endl;
                        cout << plane << endl;
                        cout << pos_pts.size() << endl;
                        cout << neg_pts.size() << endl;
                        cout << bdry_pts.size() << endl;
                        cout << pts.size() << endl;
                        cout << endl;
                    }*/
                    
                    pos_pts.insert( pos_pts.end(), pts.begin(), pts.end() );
                    pos_pts.insert( pos_pts.end(), bdry_pts.begin(), bdry_pts.end() );
                    neg_pts.insert( neg_pts.end(), pts.begin(), pts.end() );
                    neg_pts.insert( neg_pts.end(), bdry_pts.begin(), bdry_pts.end() );
                    
                    Polygon pos_poly, neg_poly;
                    
                    vector<P2> results;
                    
                    convex_hull_2( pos_pts.begin(), pos_pts.end(), back_inserter( results ) );
                    
                    pos_poly = Polygon( results.begin(), results.end() );
                    
                    results.clear();
                    
                    double dist_pos_poly = Max_Distance_To_Polyhedron_2D( centre, pos_poly );
                    
                    polys[counter_1].poly = pos_poly;
                    polys[counter_1].dist = dist_pos_poly;
                    
                    if (polys[counter_1].zone + 1 <= zone_limit)
                    {
                        convex_hull_2( neg_pts.begin(), neg_pts.end(), back_inserter( results ) );
                        
                        neg_poly = Polygon( results.begin(), results.end() );
                        
                        double dist_neg_poly = Max_Distance_To_Polyhedron_2D( centre, neg_poly );
                        
                        new_polys.push_back( B_Poly_2D( neg_poly, dist_neg_poly, polys[counter_1].zone + 1 ) );
                    }
                }
            }
            
            polys.insert( polys.end(), new_polys.begin(), new_polys.end() );
        }
        
        max_radius = Max_Radius_Of_Space_2D( centre, polys );
    }
    
    {
        mutex m1;
        
        lock_guard<mutex> lock_guard( m1 );
        
        Removing_Polyhedrons_2D( centre, planes, plane_distance, polys, final_polys, zone_limit );
        
        final_polys.insert( final_polys.end(), polys.begin(), polys.end() );
    }
}

void Compute_Brillouin_Zones_2D ( multimap<double, P2>const& pts, int zone_limit, P2 const& centre, vector<vector<Tri>>& zones_of_tris, vector<double>& max_radii, vector<double>& cell_volume )
{
    vector<B_Poly_2D> final_polys;
    final_polys.reserve( 3000 );
    
    Polygon cube;
    
    double cube_size = sqrt( pts.rbegin()->first ) * 0.5;
    
    Generate_Cube_2D( cube_size, centre, cube );
    
    multimap<double, P2> reduced_pts;
    multimap<double, P2> remaining_pts;
    
    for (auto iter = pts.begin(); iter != pts.end(); ++iter)
    {
        if ((int)reduced_pts.size() <= -1) reduced_pts.insert( pair<double, P2>( iter->first, iter->second ) );
        
        else remaining_pts.insert( pair<double, P2>( iter->first, iter->second ) );
    }
    
    vector<B_Poly_2D> starting_polys;
    
    Divide_Polyhedron_2D( centre, reduced_pts, cube, 1, starting_polys, zone_limit );
    
    vector<vector<B_Poly_2D>> fin_polys( (int)starting_polys.size() );
    vector<thread> thr;
    
    thr.reserve( starting_polys.size() );
    
    bool threads = false;
    
    for (int counter = 0; counter < fin_polys.size(); ++counter)
    {
        fin_polys[counter].reserve( 1000 );
    }
    
    if (threads)
    {
        for (int counter = 0; counter < starting_polys.size(); ++counter)
        {
            thr.push_back( thread( Divide_Polyhedron_2D, centre, remaining_pts, starting_polys[counter].poly, starting_polys[counter].zone, ref( fin_polys[counter] ), zone_limit ) );
        }
        
        for (int counter = 0; counter < starting_polys.size(); ++counter)
        {
            thr[counter].join();
        }
    }
    
    else
    {
        for (int counter = 0; counter < starting_polys.size(); ++counter)
        {
            Divide_Polyhedron_2D( centre, remaining_pts, starting_polys[counter].poly, starting_polys[counter].zone, fin_polys[counter], zone_limit );
        }
    }
    
    for (int counter_1 = 0; counter_1 < starting_polys.size(); ++counter_1)
    {
        final_polys.insert( final_polys.end(), fin_polys[counter_1].begin(), fin_polys[counter_1].end() );
    }
    
    vector<double> vec( zone_limit, 0 );
    max_radii = vec;
    
    for (int counter = 0; counter < final_polys.size(); ++counter)
    {
        double max_radius = final_polys[counter].dist;
        
        if (max_radii[final_polys[counter].zone - 1] < max_radius) max_radii[final_polys[counter].zone - 1] = max_radius;
    }
    
    zones_of_tris.resize( zone_limit );
    
    for (int counter = 0; counter < final_polys.size(); ++counter)
    {
        vector<P2> vertices;
        
        for (vertex_iterator_2D v = final_polys[counter].poly.vertices_begin(); v != final_polys[counter].poly.vertices_end(); ++v)
        {
            P2 p = P2( v->x(), v->y() );
            
            vertices.push_back( p );
        }
        
        Triangulation_2D T( vertices.begin(), vertices.end() );
        
        for (faces_iterator c = T.Triangulation_2D::finite_faces_begin(); c != T.Triangulation_2D::finite_faces_end(); ++c)
        {
            Tri tri = T.triangle( c );
            
            zones_of_tris[final_polys[counter].zone - 1].push_back( tri );
            
            cell_volume[final_polys[counter].zone - 1] += tri.area();
        }
    }
    
    /*for (int counter = 0; counter < volumes.size(); ++counter)
    {
        cout << volumes[counter] << endl;
    }*/
}
