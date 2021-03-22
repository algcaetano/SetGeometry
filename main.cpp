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
#include"collpar.h"

using namespace std;


//enable double*Point2d operations => overload should be global
Point2d operator*(const double& d, const Point2d& p){
    return Point2d(d*p.x, d*p.y);
}

int main()
{
    vector<Point2d> vert = {Point2d(0, 0),
                            Point2d(0, 20),
                            Point2d(20, 20),
                            Point2d(20, 0)};
    Polygon poly(vert);
    Lattice lattice(4);
    DomainPoints domainPoints(poly, lattice);

    poly.setExternalID(3, 1);

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
