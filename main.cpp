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
#include"domainpoints.h"

using namespace std;


//enable double*Point2d operations => overload should be global
Point2d operator*(const double& d, const Point2d& p){
    return Point2d(d*p.x, d*p.y);
}

int main()
{
    vector<Point2d> vert = {Point2d(0, 0),
                            Point2d(0, 100),
                            Point2d(150, 100),
                            Point2d(150, 85),
                            Point2d(15, 85),
                            Point2d(15, 20),
                            Point2d(85, 20),
                            Point2d(85, 35),
                            Point2d(50, 35),
                            Point2d(50, 70),
                            Point2d(100, 70),
                            Point2d(100, 0)};
    Polygon poly(vert);
    Lattice lattice(4);
    DomainPoints domainPoints(poly, lattice);


     //separar em boundary and fluid points
//    std::vector<int> boundaryPoints;
//    std::vector<int> fluidPoints;
//    for (unsigned int i = 0; i < domainPoints.domainPoints.size(); i++) //all points should be checked
//    {
//        double a, b; //dummy variables
//        bool isParallel; //dummy variable
//        Line2d line(domainPoints.domainPoints[i], Point2d(1,1)); //just inicial point r0 is necessary
//        bool isCrossing = false; //initial status
//        unsigned int numVert = 0; //initial side
//        while (!isCrossing && numVert < poly.external.size()) //not crossing and not exceeding number of sides
//        {
//            unsigned int numDir = 1; //initial direction - [0 0] was not used
//            while (!isCrossing && numDir < lattice.ex.size()) //not crossing and not exceeding number of directions
//            {
//                line.v = Point2d(lattice.ex[numDir], lattice.ey[numDir]); //set the directions with the direction numDir
//                isCrossing = line.isOnSegment(poly.external[numVert], a, b, isParallel); //check if is crossing
//                numDir++; //new direction
//            }
//            numVert++; //new side
//        }
//        if (isCrossing)
//        {
//            boundaryPoints.push_back(i);
//        }
//        else
//        {
//            fluidPoints.push_back(i);
//        }
//    }


    ofstream myfile;
    myfile.open ("domainPoints.csv");
    for (unsigned int i = 0; i < domainPoints.domainPoints.size(); i++)
    {
        myfile <<domainPoints.domainPoints[i].x<<";"<<domainPoints.domainPoints[i].y<<std::endl;
    }
    myfile.close();

    ofstream myfile2;
    myfile2.open ("fluidPoints.csv");
    for (unsigned int i = 0; i < domainPoints.fluidPoints.size(); i++)
    {
        myfile2 <<domainPoints.domainPoints[domainPoints.fluidPoints[i]].x<<";"<<domainPoints.domainPoints[domainPoints.fluidPoints[i]].y<<std::endl;
    }
    myfile2.close();

    ofstream myfile3;
    myfile3.open ("boundaryPoints.csv");
    for (unsigned int i = 0; i < domainPoints.boundaryPoints.size(); i++)
    {
        myfile3 <<domainPoints.domainPoints[domainPoints.boundaryPoints[i]].x<<";"<<domainPoints.domainPoints[domainPoints.boundaryPoints[i]].y<<std::endl;
    }
    myfile3.close();

    ofstream myfile4;
    myfile4.open("boundary.csv");
    for (unsigned int i = 0; i < vert.size(); i++)
    {
        myfile4<<vert[i].x<<";"<<vert[i].y<<std::endl;
    }
    myfile4.close();

    return 0;
}
