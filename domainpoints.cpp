#include "domainpoints.h"
#include <cmath>
#include <algorithm>    // std::sort
#include <iostream>
#include </usr/lib/gcc/x86_64-linux-gnu/9/include/omp.h>
#include "AuxFunctions.h"

DomainPoints::DomainPoints()
{

}

DomainPoints::DomainPoints(Polygon vert, Lattice lattice)
{
    this->domainPoints = setDomainPoints(vert);
    this->walls = vert;
    this->lattice = lattice;
    setBoundaryID(this->boundaryPoints, this->fluidPoints, this->propWithNoCollDir, this->propWithCollDir, vert, this->domainPoints, lattice);
}

std::vector<Point2d> DomainPoints::setDomainPoints(Polygon vert)
{
    double xMin = vert.minP.x - 0.5;
    double xMax = vert.maxP.x + 0.5;
    int numX = round(xMax-xMin+1);
    double yMin = vert.minP.y - 0.5 ;
    double yMax = vert.maxP.y + 0.5;
    int numY = round(yMax-yMin+1);

    Point2d pTest;
    bool isOnEdge = false;
    std::vector<Point2d> result;

    for(int i = 0; i < numX; i++)
    {
        for(int j = 0; j < numY; j++)
        {
            pTest.x = xMin + i;
            pTest.y = yMin + j;
            if (vert.isInside(pTest, isOnEdge))
            {
                result.push_back(pTest);
            }
        }
    }
    std::sort (result.begin(), result.end());
    return result;
}

void DomainPoints::setBoundaryID(std::vector<int>& boundRes, std::vector<int>& fluidRes, std::vector<std::vector<int>>& propNoCol, std::vector<std::vector<int>>& propCol,
                                 Polygon poly, std::vector<Point2d> pointList, Lattice lattice)
{
    boundRes.clear();
    fluidRes.clear();
    propNoCol.clear();
    propCol.clear();
    #pragma omp parallel firstprivate(lattice, poly, pointList)
    {
        std::vector<int> bound, fluid;
        std::vector<std::vector<int>> col, noCol;
        #pragma omp for
        for (int i = 0; i < pointList.size(); i++)
        {
            double a, b; //dummy variables
            bool isParallel; //dummy variable
            Line2d line(pointList[i], Point2d(1,1)); //just inicial point r0 is necessary
            bool isCrossing = false; //initial status
            unsigned int numVert = 0; //initial side
            while (!isCrossing && numVert < poly.external.size()) //not crossing and not exceeding number of sides
            {
                unsigned int numDir = 1; //initial direction - [0 0] was not used
                while (!isCrossing && numDir < lattice.ex.size()) //not crossing and not exceeding number of directions
                {
                    line.v = Point2d(lattice.ex[numDir], lattice.ey[numDir]); //set the directions with the direction numDir
                    isCrossing = line.isOnSegment(poly.external[numVert], a, b, isParallel); //check if is crossing
                    numDir++; //new direction
                }
                numVert++; //new side
            }
            if (isCrossing)
            {
                bound.push_back(i);
                noCol.push_back({i, 0, i, 0});
                for (int j = 1; j < lattice.ex.size(); j++)
                {
                    line.v = Point2d(lattice.ex[j], lattice.ey[j]);
                    if(poly.isCrossing(line))
                    {
                        col.push_back({i, j});
                    }
                    else
                    {
                        noCol.push_back({i, j, fastFindPointId(pointList, (line.r0 + line.v)), j});
                    }
                }
            }
            else
            {
                fluid.push_back((int)i);
                noCol.push_back({i, 0, i, 0});
                for (int j = 1; j < lattice.ex.size(); j++)
                {
                    line.v = Point2d(lattice.ex[j], lattice.ey[j]);
                    noCol.push_back({i, j, fastFindPointId(pointList, (line.r0 + line.v)), j});
                }
            }
        }
        #pragma omp critical
        {
            boundRes.insert(std::end(boundRes), std::begin(bound), std::end(bound));
            fluidRes.insert(std::end(fluidRes), std::begin(fluid), std::end(fluid));
            propNoCol.insert(std::end(propNoCol), std::begin(noCol), std::end(noCol));
            propCol.insert(std::end(propCol), std::begin(col), std::end(col));
        }
    }
}

DomainPoints::~DomainPoints()
{

}
