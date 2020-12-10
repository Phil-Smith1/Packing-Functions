#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Cell.h"

using namespace cv;

#ifndef big_number
#define big_number
const double big_num = 1e10;
#endif

void Bounding_Box ( vector<P2>const& vertices, pair<Point2d, Point2d>& cell_box )
{
    cell_box.first = Point2d( big_num, big_num );
    cell_box.second = Point2d( -big_num, -big_num );
    
    for (auto v : vertices)
    {
        if (cell_box.first.x > v.x()) cell_box.first.x = v.x();
        if (cell_box.first.y > v.y()) cell_box.first.y = v.y();
        if (cell_box.second.x < v.x()) cell_box.second.x = v.x();
        if (cell_box.second.y < v.y()) cell_box.second.y = v.y();
    }
}

void Scaling_Parameters ( vector<P2>const& vertices, Point image_sizes, double& scale, Point2d& shift )
{
    pair<Point2d, Point2d> box;
    
    Bounding_Box( vertices, box );
    
    Point2d cell_sizes( box.second.x - box.first.x, box.second.y - box.first.y );
    Point2d cell_centre( box.second.x + box.first.x, box.second.y + box.first.y );
    cell_centre *= 0.5;
    
    Point2d image_centre( image_sizes.x * 0.5, image_sizes.y * 0.5 );
    
    scale = std::min( image_sizes.x / (double)cell_sizes.x, image_sizes.y / (double)cell_sizes.y );
    scale *= 0.9;
    shift = image_centre - scale * cell_centre;
}

void Bounding_Box ( vector<Cell>const& cells, pair<Point2d, Point2d>& cell_box )
{
    cell_box.first = Point2d( big_num, big_num );
    cell_box.second = Point2d( -big_num, -big_num );
    
    for (auto c : cells)
    {
        for (auto v : c.vertices)
        {
            if (cell_box.first.x > v.x()) cell_box.first.x = v.x();
            if (cell_box.first.y > -v.y()) cell_box.first.y = -v.y();
            if (cell_box.second.x < v.x()) cell_box.second.x = v.x();
            if (cell_box.second.y < -v.y()) cell_box.second.y = -v.y();
        }
    }
}

void Scaling_Parameters ( vector<Cell>const& cells, Point image_sizes, double& scale )
{
    pair<Point2d, Point2d> box;
    
    Bounding_Box( cells, box );
    
    Point2d cell_sizes( box.second.x - box.first.x, box.second.y - box.first.y );
    Point2d cell_centre( box.second.x + box.first.x, box.second.y + box.first.y );
    cell_centre *= 0.5;
    
    Point2d image_centre( image_sizes.x * 0.5, image_sizes.y * 0.5 );
    
    scale = std::min( image_sizes.x / (double)cell_sizes.x, image_sizes.y / (double)cell_sizes.y );
    scale *= 0.9;
}

void Draw_Cells ( vector<Cell> const& cells )
{
    const Point image_sizes( 450, 350 );
    
    double scale;
    
    Scaling_Parameters( cells, image_sizes, scale );
    
    int counter_1 = 0;
    
    for (auto cell : cells)
    {
        Point2d shift;
        
        Scaling_Parameters( cell.vertices, image_sizes, scale, shift );
        
        Mat image( image_sizes, CV_8UC3, CV_RGB( 255, 255, 255 ) );
        
        for (int counter_2 = 0; counter_2 < cell.num_pts; ++counter_2)
        {
            Point2d p = scale * Point2d( cell.pts[counter_2].x(), -cell.pts[counter_2].y() ) + shift;
            
            circle( image, p, 4, CV_RGB( 0, 0, 0 ), -1 );
        }
        
        for (int counter_2 = 0; counter_2 < cell.edges.size(); ++counter_2)
        {
            Point2d p1 = scale * Point2d( cell.edges[counter_2].startpt.x(), -cell.edges[counter_2].startpt.y() ) + shift;
            Point2d p2 = scale * Point2d( cell.edges[counter_2].endpt.x(), -cell.edges[counter_2].endpt.y() ) + shift;
            
            line( image, p1, p2, CV_RGB( 0, 0, 0 ), 1 );
        }
        
        imwrite( "/Users/philsmith/Documents/Xcode Projects/Crystal_Density/Graphs/Cells/Cell_" + to_string( counter_1 ) + ".png", image );
        
        ++counter_1;
    }
}

void Draw_Unit_Cell ( P2 const& p1, P2 const& p2, vector<P2> const& int_pts )
{
    const Point image_sizes( 450, 350 );
    
    vector<P2> vertices;
    
    vertices.push_back( P2( 0, 0 ) );
    vertices.push_back( p1 );
    vertices.push_back( p2 );
    vertices.push_back( P2( p1.x() + p2.x(), p1.y() + p2.y() ) );
    
    double scale = 0;
    Point2d shift;
    
    Scaling_Parameters( vertices, image_sizes, scale, shift );
    
    Mat image( image_sizes, CV_8UC3, CV_RGB( 255, 255, 255 ) );
    
    Point2d pt1 = scale * Point2d( vertices[0].x(), vertices[0].y() ) + shift;
    Point2d pt2 = scale * Point2d( vertices[1].x(), vertices[1].y() ) + shift;
    
    line( image, pt1, pt2, CV_RGB( 0, 0, 0 ), 1 );
    
    pt1 = scale * Point2d( vertices[1].x(), vertices[1].y() ) + shift;
    pt2 = scale * Point2d( vertices[3].x(), vertices[3].y() ) + shift;
    
    line( image, pt1, pt2, CV_RGB( 0, 0, 0 ), 1 );
    
    pt1 = scale * Point2d( vertices[3].x(), vertices[3].y() ) + shift;
    pt2 = scale * Point2d( vertices[2].x(), vertices[2].y() ) + shift;
    
    line( image, pt1, pt2, CV_RGB( 0, 0, 0 ), 1 );
    
    pt1 = scale * Point2d( vertices[2].x(), vertices[2].y() ) + shift;
    pt2 = scale * Point2d( vertices[0].x(), vertices[0].y() ) + shift;
    
    line( image, pt1, pt2, CV_RGB( 0, 0, 0 ), 1 );
    
    for (int counter = 0; counter < int_pts.size(); ++counter)
    {
        Point2d p = scale * Point2d( int_pts[counter].x(), int_pts[counter].y() ) + shift;
        
        circle( image, p, 4, CV_RGB( 0, 0, 0 ), -1 );
    }
    
    vector<P2> extra_pts;
    
    extra_pts.push_back( P2( -0.025, 0.05 ) );
    extra_pts.push_back( P2( 0.275, -0.05 ) );
    extra_pts.push_back( P2( 1 - 0.025, 0.05 ) );
    
    extra_pts.push_back( P2( -0.025, 1.05 ) );
    extra_pts.push_back( P2( 0.275, 1 - 0.05 ) );
    extra_pts.push_back( P2( 1 - 0.025, 1.05 ) );
    
    for (int counter = 0; counter < extra_pts.size(); ++counter)
    {
        Point2d p = scale * Point2d( extra_pts[counter].x(), extra_pts[counter].y() ) + shift;
        
        circle( image, p, 4, CV_RGB( 255, 0, 0 ), -1 );
    }
    
    imwrite( "/Users/philsmith/Documents/Work/Xcode Projects/Crystal_Density/3D/Graphs/Unit_Cell.png", image );
}
