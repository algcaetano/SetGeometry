#ifndef LINE2D_H
#define LINE2D_H

#include "point2d.h"

class Line2d
{
public:
    //constructors
    Line2d();
    Line2d(Point2d r0, Point2d v);//initial point and direction vector => r0 = p1, r0+v = p2
    ~Line2d();

    //members
    Point2d r0, v;
    //Point2d r0 => reference point
    //Point2d v => vector parallel to the line

    int id;
    //int id => identification number of the line

    //functions
    bool isCrossing(Line2d& line, Point2d& crossPoint);
    //isCrossing => checks if line 1 crosses line 2
    //@return bool => returns true if lines cross and false if dont
    //@param Line2d& line => line to be checked
    //@param Point2d& crossPoint => point where lines intersect

    void setId(int id);
    //setID => relate an ID to this line segment
    //@param int id = the ID number

private:
    double cross(const Line2d line);
    //cross => calculates the vectorial product v1 x v2. v1 is taken from this object
    //@return double => z component of v1 x v2
    //@param const Line2d line => Line2d class where v2 is taken from

    double dot(const Line2d line); //internal product
};

#endif // LINE2D_H
