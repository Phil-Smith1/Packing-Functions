#pragma once

#include <fstream>

#include "First_Order_Total_Area.h"
#include "Second_Order_Total_Area.h"
#include "Third_Order_Total_Area.h"
#include "Fourth_Order_Total_Area.h"
#include "Areas.h"

void Extract_Data_Pts ( string const& directory, Cell& cell, int sample_rate, double max_radius );
