#pragma once

#include <fstream>

#include "Input3D.h"
#include "Circumradius.h"
#include "First_Order_Total_Volume.h"
#include "Second_Order_Total_Volume.h"
#include "Third_Order_Total_Volume.h"
#include "Volumes3D.h"

void Extract_Data_Pts3D ( string const& directory, Input3D const& input, Cell3D const& cell, int index );
