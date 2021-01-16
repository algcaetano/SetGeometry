#ifndef POLYGON_H
#define POLYGON_H

#include<vector>
#include"point2d.h"

class Polygon
{
public:
    //constructors
    Polygon();
    Polygon(std::vector<Point2d>& vert); //creates an external polygon
    ~Polygon();
    //members
    std::vector<std::vector<Point2d>> external; //only one external polygon made of lines segments
    std::vector<std::vector<std::vector<Point2d>>> internals; //can have multiple holes each one defined by one polygon made of line segments
    //functions
    void addHole(std::vector<Point2d> vert);
private:
    //functions
    std::vector<std::vector<Point2d>> createLines(std::vector<Point2d>& vert);
};

#endif // POLYGON_H
