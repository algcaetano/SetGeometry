#ifndef POLYGON_H
#define POLYGON_H

#include<vector>
#include"point2d.h"
#include"line2d.h"

class Polygon
{
public:
    //constructors
    Polygon();
    Polygon(std::vector<Point2d>& vert); //creates an external polygon
    ~Polygon();
    //members
    std::vector<Line2d> external; //only one external polygon made of lines segments
    std::vector<std::vector<std::vector<Point2d>>> internals; //can have multiple holes each one defined by one polygon made of line segments
    Point2d minP, maxP;
    //functions
    void addHole(std::vector<Point2d> vert);
    bool isInside(Point2d p);
private:
    //members
    Line2d limits;
    //functions
    std::vector<Line2d> createLines(std::vector<Point2d>& vert);
    void findLimits(std::vector<Point2d>& vert);
};

#endif // POLYGON_H
