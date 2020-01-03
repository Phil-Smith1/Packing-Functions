#pragma once

#include <vector>

using namespace std;

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

void Volumes3D ( double first_order_total_volume, double second_order_total_volume, double third_order_total_volume, vector<double>& volumes_at_least, vector<double>& volumes_exact );
