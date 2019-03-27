#pragma once

#include <opencv2/highgui/highgui.hpp>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;
using namespace cv;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;

void Cloud_CGAL_To_Cloud_CV ( vector<P2>const& cloud_cgal, vector<Point2d>& cloud_cv )
{
    for (auto c : cloud_cgal)
    {
        cloud_cv.push_back( Point2d( c.x(), c.y() ) );
    }
}

void Cloud_CV_To_Cloud_CGAL ( vector<Point2d>const& cloud_cv, vector<P2>& cloud_cgal )
{
    for (auto c : cloud_cv)
    {
        cloud_cgal.push_back( P2( c.x, c.y ) );
    }
}
