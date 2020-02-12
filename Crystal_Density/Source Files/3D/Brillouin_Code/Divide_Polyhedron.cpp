#include "Max_Distance_To_Polyhedron.h"
#include "Removing_Polyhedrons.h"
#include "Max_Radius_Of_Space.h"
#include "Plane_Intersect_Polyhedron.h"

#include <mutex>

#include <CGAL/convex_hull_3.h>

typedef Exact_Kernel::Segment_3 S3_E;
typedef Exact_Kernel::Intersect_3 I3;

typedef Polyhedron::Halfedge_iterator halfedge_iterator;

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
        
        if (max_radius < plane_distance + 1e-10) break;
        
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
