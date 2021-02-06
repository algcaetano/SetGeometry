#include <iostream>
#include"polygon.h"
#include"point2d.h"
#include"line2d.h"
#include<vector>
#include <algorithm>    // std::sort
#include <math.h>

using namespace std;


//enable double*Point2d operations => overload should be global
Point2d operator*(const double& d, const Point2d& p){
    return Point2d(d*p.x, d*p.y);
}

int main()
{
    vector<Point2d> vert = {Point2d(0, 10),
                            Point2d(15, 10),
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


    return 0;
}
