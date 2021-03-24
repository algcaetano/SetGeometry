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
    std::vector<int> externalID;
    std::vector<int> externalPriority;
    std::vector<std::vector<Line2d>> internals; //can have multiple holes each one defined by one polygon made of line segments
    Point2d minP, maxP; //bottom left and up right limits
    //functions
    void addHole(std::vector<Point2d> vert);
    bool isInside(Point2d p, bool& isOn);
    void setExternalID(const int line, const int id);
    //setExternalID => gives an id number to a external line segment
    //@param const int line => the line segment to be identified
    //@param const int id => the id number to be given to the line segment
    bool isCrossing(Line2d refLine);
    //isCrossing => checks if a line segment intersect at least one of the sides of de polygon
    //@param bool => true if crosses, false if do not
    //@param line2d refLine => the line segment to be checked
    bool isHited(Line2d line, Point2d& pInt, int& id, int& id2, bool& unique, bool& pointIn);
    //isHited => checks if a line segment hits a wall from the polygon. Obs: if starting point is on the wall this is not considered a intersection point
    //Obs 2: if the line segment points outward the poligon, the result is false
    //Obs 3: if there are more than one intersection, the resulting id will be the closest one
    //@param bool => the resulting condition of intersection or not
    //@param Line2d line => the line segment to be tested
    //@param Point2d& pInt => the intersection point
    //@param int& id => the id of the side intersected
    //@param bool& unique => checks if the line intersect only one side
    //@param bool& pointIn => checks if the line segment is pointing into the polygon
    void setExternalPrior(const int line, const int id);
    //setExternalPrior => gives an priority number to a external line segment. In case of a segment intersect a corner, the higher ID prevail
    //@param const int line => the line segment to be identified
    //@param const int id => the id number to be given to the line segment
private:
    //members
    Line2d limits;
    //functions
    std::vector<Line2d> createLines(std::vector<Point2d>& vert);
    void findLimits(std::vector<Point2d>& vert);
};

#endif // POLYGON_H
