#ifndef DOMAINPOINTS_H
#define DOMAINPOINTS_H

#include "polygon.h"
#include "point2d.h"
#include <vector>
#include "lattice.h"

class DomainPoints
{
public:
    DomainPoints();
    DomainPoints(Polygon vert, Lattice lattice);
    ~DomainPoints();

    std::vector<Point2d> domainPoints;
    std::vector<int> boundaryPoints;
    std::vector<int> fluidPoints;
    std::vector<std::vector<int>> propWithNoCollDir;
    std::vector<std::vector<int>> propWithCollDir;
    Polygon walls;
    Lattice lattice;

private:
    void setBoundaryID(std::vector<int>& bound, std::vector<int>& fluid, std::vector<std::vector<int> > &propNoCol, std::vector<std::vector<int> > &propCol, Polygon poly,
                       std::vector<Point2d> pointList, Lattice lattice);
    //setBoundaryID => separates the domain into boundary (at least one collision direction) and fluid (no collision directions) points
    //@param std::vector<int>& bound => vector wich receives the colision points
    //@param std::vector<int>& fluid => vector wich receives the fluid points
    //@param Polygon poly => polygon that will be used to check the fluid or boundary point
    //@param std::vector<Point2d> pointList => list of points inside the polygon
    //@param Lattice lattice => fluid and boundary points depends on the lattice
    std::vector<Point2d> setDomainPoints(Polygon vert);
    //setDomainPoints => create a mesh of points inside a polygon
    //@param Polygon vert => polygon that will be used to create the mesh
};

#endif // DOMAINPOINTS_H
