#include <iostream>
#include"polygon.h"
#include"point2d.h"
#include"line2d.h"
#include"lattice.h"
#include<vector>
#include <algorithm>    // std::sort
#include <math.h>
#include <iostream>
#include <fstream>

using namespace std;


//enable double*Point2d operations => overload should be global
Point2d operator*(const double& d, const Point2d& p){
    return Point2d(d*p.x, d*p.y);
}

int main()
{
    vector<Point2d> vert = {Point2d(0, 15),
                            Point2d(15, 35),
                            Point2d(15, 8),
                            Point2d(2, 8),
                            Point2d(2, 1),
                            Point2d(8, 1),
                            Point2d(8, 4),
                            Point2d(6, 4),
                            Point2d(6, 2),
                            Point2d(4, 2),
                            Point2d(4, 6),
                            Point2d(10, 6),
                            Point2d(10, 0),
                            Point2d(0, 0)};
    Polygon poly(vert);

    double param, fractpart, intpart;
    int numX, numY;

      param = 3.14159265;
      fractpart = modf (param , &intpart);

    std::vector<Point2d> domainPoints;
    fractpart  = modf(poly.minP.x-1, &intpart);
    double x0 = intpart+0.5;
    fractpart  = modf(poly.minP.y-1, &intpart);
    double y0 = intpart+0.5;
    fractpart  = modf(poly.maxP.x+1, &intpart);
    double xf = intpart+0.5;
    fractpart  = modf(poly.maxP.y+1, &intpart);
    double yf = intpart+0.5;
    fractpart  = modf(xf-x0+1, &intpart);
    numX = round(intpart);
    fractpart  = modf(yf-y0+1, &intpart);
    numY = round(intpart);

    Point2d pTest;
    bool isOnLine = false;

    for (int i = 0; i < numY; i++)
    {
        for (int j = 0; j < numX; j++)
        {
            pTest.x = x0+j;
            pTest.y = y0+i;
            if(poly.isInside(pTest, isOnLine))
            {
                domainPoints.push_back(pTest);
            }
        }
    }

    std::sort (domainPoints.begin(), domainPoints.end());
    Lattice lattice(4);

     //separar em boundary and fluid points
    std::vector<int> boundaryPoints;
    std::vector<int> fluidPoints;
    for (unsigned int i = 0; i < domainPoints.size(); i++) //all points should be checked
    {
        double a, b; //dummy variables
        bool isParallel; //dummy variable
        Line2d line(domainPoints[i], Point2d(1,1)); //just inicial point r0 is necessary
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
            boundaryPoints.push_back(i);
        }
        else
        {
            fluidPoints.push_back(i);
        }
    }


    ofstream myfile;
    myfile.open ("domainPoints.csv");
    for (unsigned int i = 0; i < domainPoints.size(); i++)
    {
        myfile <<domainPoints[i].x<<";"<<domainPoints[i].y<<std::endl;
    }
    myfile.close();

    ofstream myfile2;
    myfile2.open ("fluidPoints.csv");
    for (unsigned int i = 0; i < fluidPoints.size(); i++)
    {
        myfile2 <<domainPoints[fluidPoints[i]].x<<";"<<domainPoints[fluidPoints[i]].y<<std::endl;
    }
    myfile2.close();

    ofstream myfile3;
    myfile3.open ("boundaryPoints.csv");
    for (unsigned int i = 0; i < boundaryPoints.size(); i++)
    {
        myfile3 <<domainPoints[boundaryPoints[i]].x<<";"<<domainPoints[boundaryPoints[i]].y<<std::endl;
    }
    myfile3.close();

    return 0;
}
