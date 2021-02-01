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
    bool isCrossing(Line2d& line, double& a, double& b, bool& isParallel);
    //isCrossing => checks if line 1 crosses line 2
    //@return bool => returns true if lines cross and false if dont
    //@param Line2d& line => line to be checked
    //@param double2d& a => factor such that pInt = r + v*a is the intersection point
    //@param bool& isParallel => flag to check if lines are parallel (true) or not (false)
    bool isOnSegment(Line2d& line, double& a, double& b, bool& isParallel);
    //isOnSegment => checks if the segments (r1+v1) and (r2+v2) of the CROSSING LINES intersect
    //@return bool => true if segments intersect
    //@param Line2d& line => line segment to be compared
    void setId(int id);
    //setID => relate an ID to this line segment
    //@param int id = the ID number
    double calculateA(Point2d& p);

private:
    double cross(const Line2d line);
    //cross => calculates the vectorial product v1 x v2. v1 is taken from this object
    //@return double => z component of v1 x v2
    //@param const Line2d line => Line2d class where v2 is taken from

    double dot(const Line2d line); //internal product
};

#endif // LINE2D_H
