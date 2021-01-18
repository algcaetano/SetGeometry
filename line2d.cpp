#include "line2d.h"
#include<iostream>
#include"AuxFunctions.h"

Line2d::Line2d()
{
    this->r0 = Point2d(0,0);
    this->v = Point2d(0,0);
}

Line2d::Line2d(Point2d r0, Point2d v)
{
    if (compareDouble(v.distance(Point2d(0,0)),0))
    {
        std::cerr<<"Error: null direction vector"<<std::endl;
    }
    this->r0 = r0;
    this->v = v;
}

void Line2d::setId(int id) //set an identification number to this line segment
{
    this->id = id;
}

double Line2d::cross(const Line2d line) //cross product
{
    return (this->v.x*line.v.y - this->v.y*line.v.x);
}

double Line2d::dot(const Line2d line) //internal product
{
    return (this->v.x*line.v.x + this->v.y*line.v.y);
}

bool Line2d::isCrossing(Line2d& line, Point2d& crossPoint)
{
    if (this->r0==line.r0) //lines have the same reference point
    {
        crossPoint = this->r0;
        return true;
    }
    else //lines have distinct reference points
    {
        if(!compareDouble(cross(line),0)) //segments are not parallels
        {
            double scale = Line2d(Point2d(0,0), (line.r0-this->r0)).cross(line)/this->cross(line);
            if (compareDouble(scale,0) || compareDouble(scale,1)) //intersection point lies on one of the tips
            {
                crossPoint = this->r0 + this->v*scale;
                return true;
            }
            else if (scale > 0 && scale < 1) //intersection point lies on middle of the segment
            {
                crossPoint = this->r0 + this->v*scale;
                return true;
            }
            else //intersection point lies outside the segment
            {
                return false;
            }

        }
        else //segments are parallels
        {
            if (compareDouble(Line2d(Point2d(0,0), (line.r0-this->r0)).cross(*this), 0)) //segments are coincidents
            {
                double scale = Line2d(Point2d(0,0), (line.r0-this->r0)).dot(line)/this->dot(*this);
                double scale2 = Line2d(Point2d(0,0), ((line.r0-this->r0))+line.v).dot(line)/this->dot(*this);
                if (compareDouble(scale,0) || compareDouble(scale,1)) //reference point of second segment lies on the tips of first
                {
                    crossPoint = this->r0 + this->v*scale;
                    return true;
                }
                else if (scale > 0 && scale < 1) //reference point of second segment lies on middle of the first segment
                {
                    crossPoint = this->r0 + this->v*scale;
                    return true;
                }
                else if (compareDouble(scale2,0) || compareDouble(scale2,1)) //final point of the second segment lies on the tips of the first segment
                {
                    crossPoint = this->r0 + this->v*scale2;
                    return true;
                }
                else if (scale2 > 0 && scale2 < 1) //final point of the second segment lies on the middle of the first segment
                {
                    crossPoint = this->r0 + this->v*scale2;
                    return true;
                }
                else //segments do not overlap
                {
                    return false;
                }
            }
            else //segments are parallel but not coincidents
            {
                return false;
            }
        }
    }
}

Line2d::~Line2d()
{

}
