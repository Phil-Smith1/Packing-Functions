#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Cell.h"

using namespace cv;

#ifndef big_number
#define big_number
const double big_num = 1e10;
#endif

void Bounding_Box ( vector<P2>const& vertices, pair<Point2d, Point2d>& cell_box );

void Scaling_Parameters ( vector<P2>const& vertices, Point image_sizes, double scale, Point2d& shift );

void Bounding_Box ( vector<Cell>const& cells, pair<Point2d, Point2d>& cell_box );

void Scaling_Parameters ( vector<Cell>const& cells, Point image_sizes, double& scale );

void Draw_Cells ( vector<Cell> const& cells );
