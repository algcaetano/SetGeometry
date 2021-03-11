#include "domainpoints.h"
#include <cmath>
#include <algorithm>    // std::sort

DomainPoints::DomainPoints()
{

}

DomainPoints::DomainPoints(Polygon vert, Lattice lattice)
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
    this->domainPoints = result;

    #pragma omp parallel
    {
        std::vector<unsigned long int> bound, fluid;
        #pragma omp for
        for (int i = 0; i < result.size(); i++)
        {
            double a, b; //dummy variables
            bool isParallel; //dummy variable
            Line2d line(result[i], Point2d(1,1)); //just inicial point r0 is necessary
            bool isCrossing = false; //initial status
            unsigned int numVert = 0; //initial side
            while (!isCrossing && numVert < vert.external.size()) //not crossing and not exceeding number of sides
            {
                unsigned int numDir = 1; //initial direction - [0 0] was not used
                while (!isCrossing && numDir < lattice.ex.size()) //not crossing and not exceeding number of directions
                {
                    line.v = Point2d(lattice.ex[numDir], lattice.ey[numDir]); //set the directions with the direction numDir
                    isCrossing = line.isOnSegment(vert.external[numVert], a, b, isParallel); //check if is crossing
                    numDir++; //new direction
                }
                numVert++; //new side
            }
            if (isCrossing)
            {
                bound.push_back(i);
            }
            else
            {
                fluid.push_back(i);
            }
        }
        #pragma omp critical
        {
            this->boundaryPoints.insert(std::end(this->boundaryPoints), std::begin(bound), std::end(bound));
            this->fluidPoints.insert(std::end(this->fluidPoints), std::begin(fluid), std::end(fluid));
        }
    }
}

DomainPoints::~DomainPoints()
{

}
