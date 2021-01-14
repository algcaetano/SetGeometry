#include "point2d.h"
#include "AuxFunctions.h"

Point2d::Point2d()
{
    this->x = 0;
    this->y = 0;
}

Point2d::Point2d(double x, double y)
{
    this->x = x;
    this->y = y;
}

Point2d Point2d::operator+(const Point2d& p)
{
    return Point2d(this->x + p.x, this->y + p.y);
}

Point2d Point2d::operator-(const Point2d& p)
{
    return Point2d(this->x - p.x, this->y - p.y);
}

Point2d Point2d::operator*(const double& d)
{
    return Point2d(d*this->x, d*this->y);
}

Point2d Point2d::operator/(const double& d)
{
    return Point2d(this->x/d, this->y/d);
}

bool Point2d::operator==(const Point2d &p)
{
    return (compareDouble(this->x, p.x) && compareDouble(this->y, p.y));
}

bool Point2d::operator!=(const Point2d &p)
{
    return !(compareDouble(this->x, p.x) && compareDouble(this->y, p.y));
}

bool Point2d::operator<(const Point2d &p)
{
    if (compareDouble(this->x,p.x))
    {
        if (compareDouble(this->y,p.y))
        {
            return false;
        }
        else
        {
            return (this->y<p.y)?true:false;
        }
    }
    else
    {
        return (this->x<p.x)?true:false;
    }
}

bool Point2d::operator>(const Point2d &p)
{
    if (compareDouble(this->x,p.x))
    {
        if (compareDouble(this->y,p.y))
        {
            return false;
        }
        else
        {
            return (this->y>p.y)?true:false;
        }
    }
    else
    {
        return (this->x>p.x)?true:false;
    }
}

//functions definitions
double Point2d::distance(const Point2d & p)
{
    return sqrt(pow((this->x-p.x), 2) + pow((this->y-p.y), 2));
}

Point2d::~Point2d()
{

}
