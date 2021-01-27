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

void Line2d::setId(int id)
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

bool Line2d::isCrossing(Line2d& line, double& a, bool& isParallel)
{
    double v1VetV2 = this->cross(line);
    double drVetV2 = Line2d(Point2d(0,0), (line.r0-this->r0)).cross(line);
    if(compareDouble(v1VetV2,0))
    {
        if(compareDouble(drVetV2,0))
        {
            a = 0;
            isParallel = true;
            return true;
        }
        else
        {
            a = 2;
            isParallel = true;
            return false;
        }
    }
    else
    {
        a = drVetV2/v1VetV2;
        isParallel = false;
        return true;
    }
}

bool Line2d::isOnSegment(Line2d& line, double& a, bool& isParallel)
{
    if (isCrossing(line, a, isParallel))
    {
        if (isParallel)
        {
            double dist1 = calculateA(line.r0);
            Point2d pf = line.r0+line.v;
            double dist2 = calculateA(pf);
            if(isOnRange(0,1,dist1)||isOnRange(0,1,dist2))
            {
                if (isOnRange(0,1,dist1)&&isOnRange(0,1,dist2))
                {
                    a = (dist1<dist2)?dist1:dist2;
                }
                else
                {
                    a = isOnRange(0,1,dist1)?dist1:dist2;
                }
                return true;
            }
            else
            {
                if(isOnRange(0,1,line.calculateA(this->r0)))
                {
                    a = 0;
                    return true;
                }
                else
                {
                    a = 2;
                    return false;
                }
            }
        }
        else
        {
            return isOnRange(0,1,a)?true:false;
        }
    }
    else
    {
        a = 2;
        return false;
    }
}

double Line2d::calculateA(Point2d& p)
{
    if(!compareDouble(this->v.x,0))
    {
        return (p-this->r0).x/this->v.x;
    }
    else
    {
        return (p-this->r0).y/this->v.y;
    }
}

Line2d::~Line2d()
{

}
