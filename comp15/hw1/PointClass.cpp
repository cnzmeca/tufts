// PointClass.cpp
//
// A more realistic Point class 
//
// Mark A. Sheldon, UMass Lowell
// Fall 2011

#include <iostream>
#include <string>

#include "PointClass.h"
  
using namespace std;

Point::Point(int x_coord, int y_coord)
{
     x = x_coord;
     y = y_coord;
}

void Point::print()
{
     cout << "(" << x << ", " << y << ")";
}

int Point::get_x()
{
     return x;
}

int Point::get_y()
{
     return y;
}

Point Point::add(Point other)
{
     Point result(get_x() + other.get_x(),
		  get_y() + other.get_y());

     return result;
}
