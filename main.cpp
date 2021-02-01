#include <iostream>
#include"polygon.h"
#include"point2d.h"
#include"line2d.h"
#include<vector>
#include <algorithm>    // std::sort

using namespace std;


//enable double*Point2d operations => overload should be global
Point2d operator*(const double& d, const Point2d& p){
    return Point2d(d*p.x, d*p.y);
}

int main()
{
    vector<Point2d> vert = {Point2d(0.0, 1.0),
                            Point2d(1.0, 1.0),
                            Point2d(1.0, 1.5),
                            Point2d(1.5, 1.5),
                            Point2d(1.5, 0.25),
                            Point2d(1.0, 0.25),
                            Point2d(1.0, 0.5),
                            Point2d(0.5, 0.5),
                            Point2d(0.5, 0.0),
                            Point2d(0.0, 0.0)};
    Polygon poly(vert);

    double a, b;
    bool isParalell;
    bool isOnSegment = poly.external[0].isOnSegment(poly.external[2], a, b, isParalell);

    return 0;
}
