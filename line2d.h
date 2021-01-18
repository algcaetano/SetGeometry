#ifndef LINE2D_H
#define LINE2D_H

#include "point2d.h"

class Line2d
{
public:
    //constructors
    Line2d();
    Line2d(Point2d r0, Point2d v);//initial point and direction vector -> r0 = p1, r0+v = p2
    ~Line2d();
    //members
    Point2d r0, v;
    int id;
    //functions
    bool isCrossing(Line2d& line, Point2d& crossPoint);
    void setId(int id);
private:
    double cross(const Line2d line); //vectorial product
    double dot(const Line2d line); //internal product
};

#endif // LINE2D_H
