#ifndef POINT2D_H
#define POINT2D_H


class Point2d
{
public:
    //constructors
    Point2d();
    Point2d(double x, double y);
    ~Point2d();
    //members
    double x;
    double y;
    //operators
    Point2d operator+(const Point2d& p);
    Point2d operator-(const Point2d& p);
    Point2d operator*(const double& d);
    Point2d operator/(const double& d);

    bool operator==(const Point2d& p);
    bool operator!=(const Point2d& p);
    bool operator<(const Point2d& p);
    bool operator>(const Point2d& p);

    //functions
    double distance(const Point2d& p);
private:
    //functions
};

#endif // POINT2D_H
