#include "Max_Distance_To_Polyhedron.h"
#include "Removing_Polyhedrons.h"
#include "Max_Radius_Of_Space.h"
#include "Plane_Intersect_Polyhedron.h"

#include <mutex>

#include <CGAL/convex_hull_3.h>

typedef Exact_Kernel::Segment_3 S3_E;
typedef Exact_Kernel::Intersect_3 I3;

typedef K::Segment_3 S3;
typedef K::Intersect_3 I3_I;

typedef Polyhedron::Halfedge_iterator halfedge_iterator;

typedef Polyhedron_I::Halfedge_iterator halfedge_iterator_i;

void Divide_Polyhedron ( P3_E const centre, multimap<double, P3_E>const pts, Polyhedron poly, vector<B_Poly>& final_polys, int zone_limit )
{
    mutex m1;
    
    lock_guard<mutex> lock_guard( m1 );
    
    vector<B_Poly> polys;
    polys.push_back( B_Poly( poly, Max_Distance_To_Polyhedron( centre, poly ), 1 ) );
    
    double max_radius = 1e10;
    double plane_distance = 0;
    
    vector<Pl3_E> planes;
    planes.reserve( (int)pts.size() );
    
    for (auto iter = pts.begin(); iter != pts.end(); ++iter)
    {
        Pl3_E plane = bisector( centre, (*iter).second );
        
        plane_distance = sqrt( to_double( squared_distance( centre, plane ) ) );
        
        if (max_radius < plane_distance + tiny_num) break;
        
        Removing_Polyhedrons( centre, planes, plane_distance, polys, final_polys, zone_limit );
        
        if (plane.oriented_side( centre ) == ON_NEGATIVE_SIDE) plane = plane.opposite();
        
        planes.push_back( plane );
        
        if ((int)polys.size() == 0) break;
        
        int intersect = Plane_Intersect_Polyhedron( poly, plane );
        
        if (intersect == -1)
        {
            for (int counter = 0; counter < polys.size(); ++counter)
            {
                polys[counter].zone += 1;
            }
            
            continue;
        }
        
        else if (intersect == 1) continue;
        
        else
        {
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
        }
        
        max_radius = Max_Radius_Of_Space( centre, polys );
    }
    
    Removing_Polyhedrons( centre, planes, plane_distance, polys, final_polys, zone_limit );
    
    final_polys.insert( final_polys.end(), polys.begin(), polys.end() );
}

void Divide_Polyhedron_I ( P3 const centre, multimap<double, P3>const pts, Polyhedron_I poly, int starting_zone, vector<B_Poly_I>& final_polys, int zone_limit )
{
    vector<B_Poly_I> polys;
    polys.push_back( B_Poly_I( poly, Max_Distance_To_Polyhedron_I( centre, poly ), starting_zone ) );
    
    double max_radius = 1e10;
    double plane_distance = 0;
    
    vector<Pl3> planes;
    planes.reserve( (int)pts.size() );
    
    double precision = 1e12;
    
    bool remove_polys = false;
    
    for (auto iter = pts.begin(); iter != pts.end(); ++iter)
    {
        Pl3 plane = bisector( centre, (*iter).second );
        
        long double a = (long long int)(plane.a() * precision + 0.5);
        long double b = (long long int)(plane.b() * precision + 0.5);
        long double c = (long long int)(plane.c() * precision + 0.5);
        long double d = (long long int)(plane.d() * precision + 0.5);
        
        a = a / (long double)precision;
        b = b / (long double)precision;
        c = c / (long double)precision;
        d = d / (long double)precision;
        
        plane = Pl3( a, b, c, d );
        
        double plane_distance = sqrt( to_double( squared_distance( centre, plane ) ) );
        
        if (max_radius < plane_distance + 1e-10) break;
        
        {
            mutex m1;
            
            lock_guard<mutex> lock_guard( m1 );
            
            if (remove_polys) Removing_Polyhedrons_I( centre, planes, plane_distance, polys, final_polys, zone_limit );
        }
        
        if (plane.oriented_side( centre ) == ON_NEGATIVE_SIDE) plane = plane.opposite();
        
        planes.push_back( plane );
        
        if ((int)polys.size() == 0) break;
        
        int intersect = Plane_Intersect_Polyhedron_I( poly, plane );
        
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
            
            vector<B_Poly_I> new_polys;
            new_polys.reserve( (int)polys.size() );
            
            for (int counter_1 = 0; counter_1 < polys.size(); ++counter_1)
            {
                vector<P3> pos_pts;
                vector<P3> neg_pts;
                vector<P3> bdry_pts;
                
                for (vertex_iterator_i v = polys[counter_1].poly.vertices_begin(); v != polys[counter_1].poly.vertices_end(); ++v)
                {
                    P3 p = v->point();
                    
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
                    vector<S3> segs;
                    
                    for (halfedge_iterator_i h = polys[counter_1].poly.halfedges_begin(); h != polys[counter_1].poly.halfedges_end(); ++h)
                    {
                        P3 p1 = (h->vertex())->point();
                        P3 p2 = (h->prev()->vertex())->point();
                        
                        long double x = (long long int)(p1.x() * precision + 0.5);
                        long double y = (long long int)(p1.y() * precision + 0.5);
                        long double z = (long long int)(p1.z() * precision + 0.5);
                        
                        x = x / (long double)precision;
                        y = y / (long double)precision;
                        z = z / (long double)precision;
                        
                        p1 = P3( x, y, z );
                        
                        x = (long long int)(p2.x() * precision + 0.5);
                        y = (long long int)(p2.y() * precision + 0.5);
                        z = (long long int)(p2.z() * precision + 0.5);
                        
                        x = x / (long double)precision;
                        y = y / (long double)precision;
                        z = z / (long double)precision;
                        
                        p2 = P3( x, y, z );
                        
                        segs.push_back( S3( p1, p2 ) );
                        
                        ++h;
                    }
                    
                    vector<P3> pts;
                    
                    for (int counter_2 = 0; counter_2 < segs.size(); ++counter_2)
                    {
                        cpp11::result_of<I3_I(Pl3, S3)>::type result = intersection( plane, segs[counter_2] );
                        
                        if (result)
                        {
                            if (const P3 * p = boost::get<P3>( &*result ))
                            {
                                if (squared_distance( *p, segs[counter_2].source()) > tiny_num && squared_distance( *p, segs[counter_2].target()) > tiny_num)
                                {
                                    P3 pt = *p;
                                    
                                    long double x = (long long int)(pt.x() * precision + 0.5);
                                    long double y = (long long int)(pt.y() * precision + 0.5);
                                    long double z = (long long int)(pt.z() * precision + 0.5);
                                    
                                    x = x / (long double)precision;
                                    y = y / (long double)precision;
                                    z = z / (long double)precision;
                                    
                                    pt = P3( x, y, z );
                                    
                                    pts.push_back( pt );
                                }
                            }
                        }
                    }
                    
                    pos_pts.insert( pos_pts.end(), pts.begin(), pts.end() );
                    pos_pts.insert( pos_pts.end(), bdry_pts.begin(), bdry_pts.end() );
                    neg_pts.insert( neg_pts.end(), pts.begin(), pts.end() );
                    neg_pts.insert( neg_pts.end(), bdry_pts.begin(), bdry_pts.end() );
                    
                    Polyhedron_I pos_poly, neg_poly;
                    
                    convex_hull_3( pos_pts.begin(), pos_pts.end(), pos_poly );
                    
                    double dist_pos_poly = Max_Distance_To_Polyhedron_I( centre, pos_poly );
                    
                    polys[counter_1].poly = pos_poly;
                    polys[counter_1].dist = dist_pos_poly;
                    
                    if (polys[counter_1].zone + 1 <= zone_limit)
                    {
                        convex_hull_3( neg_pts.begin(), neg_pts.end(), neg_poly );
                        
                        double dist_neg_poly = Max_Distance_To_Polyhedron_I( centre, neg_poly );
                        
                        new_polys.push_back( B_Poly_I( neg_poly, dist_neg_poly, polys[counter_1].zone + 1 ) );
                    }
                }
            }
            
            polys.insert( polys.end(), new_polys.begin(), new_polys.end() );
        }
        
        max_radius = Max_Radius_Of_Space( centre, polys );
    }
    
    {
        mutex m1;
        
        lock_guard<mutex> lock_guard( m1 );
        
        Removing_Polyhedrons_I( centre, planes, plane_distance, polys, final_polys, zone_limit );
        
        final_polys.insert( final_polys.end(), polys.begin(), polys.end() );
    }
    
    //cout << final_polys.size() << endl;
}
