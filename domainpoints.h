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

private:
    void getBoundaryID(std::vector<int>& bound, std::vector<int>& fluid, Line2d& lTest, Line2d& lRef);
};

#endif // DOMAINPOINTS_H
