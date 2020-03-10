#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangle_2.h>

#include <thread>
#include <fstream>

#include "Input3D.h"

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;
typedef K::Vector_2 V2;
typedef K::Triangle_2 Tri;
typedef K::Line_2 L2;
typedef K::Segment_2 S2;

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

typedef K::Intersect_2 I2;

#include "Irregular_Sector_Area.h"
#include "Edge_Circle_Intersections.h"

double Sec_Area ( Circle const& c, P2 const& vertex, Edge const& e1, Edge const& e2, int intersection_1, int intersection_2 )
{
    if (abs( Norm( vertex, c.c ) - c.r ) < tiny_num)
    {
        double vol1 = 0, vol2 = 0;
        
        if (intersection_1 == 1 || intersection_1 == 0)
        {
            if (e1.line.oriented_side( c.c ) == ON_POSITIVE_SIDE)
            {
                if (intersection_2 == 1 || intersection_2 == 0)
                {
                    if (e2.line.oriented_side( c.c ) == ON_POSITIVE_SIDE) return c.area;
                    
                    else return 0;
                }
                
                else
                {
                    vol2 = Segment_Area( c, e2.i1, e2.i2 );
                    
                    if (e2.line.oriented_side( c.c ) == ON_POSITIVE_SIDE) return c.area - vol2;
                    
                    else return vol2;
                }
            }
            
            else return 0;
        }
        
        else
        {
            vol1 = Segment_Area( c, e1.i1, e1.i2 );
            
            if (e1.line.oriented_side( c.c ) == ON_POSITIVE_SIDE) vol1 = c.area - vol1;
            
            if (intersection_2 == 1 || intersection_2 == 0)
            {
                if (e2.line.oriented_side( c.c ) == ON_POSITIVE_SIDE) return vol1;
                
                else return 0;
            }
            
            else
            {
                vol2 = Segment_Area( c, e2.i1, e2.i2 );
                
                if (e2.line.oriented_side( c.c ) == ON_POSITIVE_SIDE) vol2 = c.area - vol2;
                
                if (((e1.line.oriented_side( e2.i1 ) == ON_NEGATIVE_SIDE && Norm( e2.i1, vertex ) > 1e-8) || (e1.line.oriented_side( e2.i2 ) == ON_NEGATIVE_SIDE && Norm( e2.i2, vertex ) > 1e-8)) && ((e2.line.oriented_side( e1.i1 ) == ON_NEGATIVE_SIDE && Norm( e1.i1, vertex ) > 1e-8) || (e2.line.oriented_side( e1.i2 ) == ON_NEGATIVE_SIDE && Norm( e1.i2, vertex ) > 1e-8))) return 0;
                
                else if (((e1.line.oriented_side( e2.i1 ) == ON_NEGATIVE_SIDE && Norm( e2.i1, vertex ) > 1e-8) || (e1.line.oriented_side( e2.i2 ) == ON_NEGATIVE_SIDE && Norm( e2.i2, vertex ) > 1e-8)) || ((e2.line.oriented_side( e1.i1 ) == ON_NEGATIVE_SIDE && Norm( e1.i1, vertex ) > 1e-8) || (e2.line.oriented_side( e1.i2 ) == ON_NEGATIVE_SIDE && Norm( e1.i2, vertex ) > 1e-8)))
                {
                    if ((e1.line.oriented_side( e2.i1 ) == ON_NEGATIVE_SIDE && Norm( e2.i1, vertex ) > 1e-8) || (e1.line.oriented_side( e2.i2 ) == ON_NEGATIVE_SIDE && Norm( e2.i2, vertex ) > 1e-8)) return vol1;
                    
                    else return vol2;
                }
                
                else return vol1 + vol2 - c.area;
            }
        }
    }
    
    else if (Norm( vertex, c.c ) > c.r)
    {
        double vol1 = 0, vol2 = 0;
        
        if (intersection_1 == 1 || intersection_1 == 0)
        {
            if (e1.line.oriented_side( c.c ) == ON_POSITIVE_SIDE)
            {
                if (intersection_2 == 1 || intersection_2 == 0)
                {
                    if (e2.line.oriented_side( c.c ) == ON_POSITIVE_SIDE) return c.area;
                    
                    else return 0;
                }
                
                else
                {
                    vol2 = Segment_Area( c, e2.i1, e2.i2 );
                    
                    if (e2.line.oriented_side( c.c ) == ON_POSITIVE_SIDE) return c.area - vol2;
                    
                    else return vol2;
                }
            }
            
            else return 0;
        }
        
        else
        {
            vol1 = Segment_Area( c, e1.i1, e1.i2 );
            
            if (e1.line.oriented_side( c.c ) == ON_POSITIVE_SIDE) vol1 = c.area - vol1;
            
            if (intersection_2 == 1 || intersection_2 == 0)
            {
                if (e2.line.oriented_side( c.c ) == ON_POSITIVE_SIDE) return vol1;
                
                else return 0;
            }
            
            else
            {
                vol2 = Segment_Area( c, e2.i1, e2.i2 );
                
                if (e2.line.oriented_side( c.c ) == ON_POSITIVE_SIDE) vol2 = c.area - vol2;
                
                if (e1.line.oriented_side( e2.i1 ) == ON_NEGATIVE_SIDE && e2.line.oriented_side( e1.i1 ) == ON_NEGATIVE_SIDE) return 0;
                
                else if (e1.line.oriented_side( e2.i1 ) == ON_NEGATIVE_SIDE || e2.line.oriented_side( e1.i1 ) == ON_NEGATIVE_SIDE)
                {
                    if (e1.line.oriented_side( e2.i1 ) == ON_NEGATIVE_SIDE) return vol1;
                    
                    else return vol2;
                }
                
                else return vol1 + vol2 - c.area;
            }
        }
    }
    
    else
    {
        P2 intersection1 = e1.i1;
        
        if (e2.line.oriented_side( intersection1 ) == ON_NEGATIVE_SIDE) intersection1 = e1.i2;
        
        P2 intersection2 = e2.i1;
        
        if (e1.line.oriented_side( intersection2 ) == ON_NEGATIVE_SIDE) intersection2 = e2.i2;
        
        double triangle_area = Triangle_Area( vertex, intersection1, intersection2 );
        double segment_area = Segment_Area( c, intersection1, intersection2 );
        
        L2 l( intersection1, intersection2 );
        
        if (l.oriented_side( c.c ) == l.oriented_side( vertex )) return triangle_area + segment_area;
        
        else return triangle_area + c.area - segment_area;
    }
}

double Intersect_Area ( Circle const& c, vector<Edge>& edges, vector<P2> const& vertices )
{
    double volume1 = 0, volume2 = 0, volume3 = 0, volume4 = 0, volume5 = 0, volume6 = 0;
    
    int intersection_1 = Line_Circle_Intersections( c, edges[0] );
    int intersection_2 = Line_Circle_Intersections( c, edges[1] );
    int intersection_3 = Line_Circle_Intersections( c, edges[2] );
    
    if (intersection_1 == 1 || intersection_1 == 0)
    {
        if (edges[0].line.oriented_side( c.c ) == ON_NEGATIVE_SIDE) volume1 = c.area;
        
        else volume1 = 0;
    }
    
    if (intersection_2 == 1 || intersection_2 == 0)
    {
        if (edges[1].line.oriented_side( c.c ) == ON_NEGATIVE_SIDE) volume2 = c.area;
        
        else volume2 = 0;
    }
    
    if (intersection_3 == 1 || intersection_3 == 0)
    {
        if (edges[2].line.oriented_side( c.c ) == ON_NEGATIVE_SIDE) volume3 = c.area;
        
        else volume3 = 0;
    }
    
    if (intersection_1 == 2)
    {
        volume1 = Segment_Area( c, edges[0].i1, edges[0].i2 );
        
        if (edges[0].line.oriented_side( c.c ) == ON_NEGATIVE_SIDE) volume1 = c.area - volume1;
    }
    
    if (intersection_2 == 2)
    {
        volume2 = Segment_Area( c, edges[1].i1, edges[1].i2 );
        
        if (edges[1].line.oriented_side( c.c ) == ON_NEGATIVE_SIDE) volume2 = c.area - volume2;
    }
    
    if (intersection_3 == 2)
    {
        volume3 = Segment_Area( c, edges[2].i1, edges[2].i2 );
        
        if (edges[2].line.oriented_side( c.c ) == ON_NEGATIVE_SIDE) volume3 = c.area - volume3;
    }
    
    edges[0].line = edges[0].line.opposite();
    edges[1].line = edges[1].line.opposite();
    edges[2].line = edges[2].line.opposite();
    
    volume4 = Sec_Area( c, vertices[0], edges[0], edges[2], intersection_1, intersection_3);
    
    volume5 = Sec_Area( c, vertices[1], edges[0], edges[1], intersection_1, intersection_2 );
    
    volume6 = Sec_Area( c, vertices[2], edges[1], edges[2], intersection_2, intersection_3 );
    
    edges[0].line = edges[0].line.opposite();
    edges[1].line = edges[1].line.opposite();
    edges[2].line = edges[2].line.opposite();
    
    /*cout << volume1 << endl;
    cout << volume2 << endl;
    cout << volume3 << endl;
    cout << volume4 << endl;
    cout << volume5 << endl;
    cout << volume6 << endl;*/
    
    return c.area - volume1 - volume2 - volume3 + volume4 + volume5 + volume6;
}

double Disk_Triangle_Intersection ( Circle const& c, Tri const& t )
{
    double tri_area = t.area();
    
    if (tri_area < tiny_num * 1e4) return 0;
    
    vector<P2> vertices;
    
    vertices.push_back( t.vertex( 0 ) );
    vertices.push_back( t.vertex( 1 ) );
    vertices.push_back( t.vertex( 2 ) );
    
    double precision = 1e12;
    
    long double x = (long long int)(vertices[0].x() * precision + 0.5);
    long double y = (long long int)(vertices[0].y() * precision + 0.5);
    
    x = x / (long double)precision;
    y = y / (long double)precision;
    
    vertices[0] = P2( x, y );
    
    x = (long long int)(vertices[1].x() * precision + 0.5);
    y = (long long int)(vertices[1].y() * precision + 0.5);
    
    x = x / (long double)precision;
    y = y / (long double)precision;
    
    vertices[1] = P2( x, y );
    
    x = (long long int)(vertices[2].x() * precision + 0.5);
    y = (long long int)(vertices[2].y() * precision + 0.5);
    
    x = x / (long double)precision;
    y = y / (long double)precision;
    
    vertices[2] = P2( x, y );
    
    vector<Edge> edges;
    
    edges.push_back( Edge( L2( vertices[0], vertices[1] ), vertices[0], vertices[1], 0 ) );
    edges.push_back( Edge( L2( vertices[1], vertices[2] ), vertices[1], vertices[2], 0 ) );
    edges.push_back( Edge( L2( vertices[2], vertices[0] ), vertices[2], vertices[0], 0 ) );
    
    if (edges[0].line.oriented_side( vertices[2] ) == ON_NEGATIVE_SIDE)
    {
        edges[0].line = edges[0].line.opposite();
        edges[0].startpt = vertices[1];
        edges[0].endpt = vertices[0];
    }
    
    if (edges[1].line.oriented_side( vertices[0] ) == ON_NEGATIVE_SIDE)
    {
        edges[1].line = edges[1].line.opposite();
        edges[1].startpt = vertices[2];
        edges[1].endpt = vertices[1];
    }
    
    if (edges[2].line.oriented_side( vertices[1] ) == ON_NEGATIVE_SIDE)
    {
        edges[2].line = edges[2].line.opposite();
        edges[2].startpt = vertices[0];
        edges[2].endpt = vertices[2];
    }
    
    Circle c2( c.c, 8 );
    
    double area1 = Intersect_Area( c2, edges, vertices );
    
    Circle c3( c.c, c.r + 0.01 );
    
    double area2 = Intersect_Area( c3, edges, vertices );
    double area3 = Intersect_Area( c, edges, vertices );
    
    /*if (abs( area2 - area3) > 0.01)
    {
        cout << c.r << endl;
        cout << tri_area << endl;
        cout << area3 << endl;
        cout << area2 << endl;
    }*/
    
    //cout << area1 << endl;
    //cout << area2 << endl;
    //cout << area3 << endl;
    
    if (area1 < tiny_num) return 0;
    if (area1 > tri_area + 0.0001) return 0;
    
    if (area3 < -tiny_num || area3 > tri_area + 0.0001)
    {
        cout << area3 << endl;
        cout << tri_area << endl;
        cout << c.c << endl;
        cout << c.r << endl;
        cout << vertices[0] << endl;
        cout << vertices[1] << endl;
        cout << vertices[2] << endl << endl;
    }
    
    return area3;
}
