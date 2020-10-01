// Definition for a simple immutable Point class.
//
// Mark A. Sheldon, UMass Lowell
// Fall 2011
//

#ifndef POINTCLASS_H
#define POINTCLASS_H

class Point
{
private:
     int x, y;

public:
     Point(int x_coord, int y_coord);

     int get_x();
     int get_y();
     Point add(Point other);
     void print();
};

#endif
