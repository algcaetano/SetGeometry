#include "polygon.h"
#include<iostream>
#include "AuxFunctions.h"

Polygon::Polygon()
{

}

Polygon::Polygon(std::vector<Point2d>& vert)
{
    if (vert.size()<3)
    {
        std::cerr<<"Not enougth points."<<std::endl;
    }
    else
    {
        this->external = createLines(vert);
        findLimits(vert);
    }
}
std::vector<Line2d> Polygon::createLines(std::vector<Point2d>& vert)
{
    if (vert.size()<3){
        std::cerr<<"not enougth points"<<std::endl;
        return std::vector<Line2d>{};
    }
    else
    {
        std::vector<Line2d> output;
        for (unsigned int i = 0; i < (vert.size()-1); i++)
        {
            output.push_back({vert[i], vert[i+1]-vert[i]});
        }
        output.push_back({vert.back(), vert.front()-vert.back()});
        return output;
    }
}

void Polygon::findLimits(std::vector<Point2d>& vert)
{
    double minX = vert[0].x;
    double maxX = minX;
    double minY = vert[0].y;
    double maxY = minY;
    for (unsigned int i = 0; i < vert.size(); i++)
    {
        minX = (vert[i].x<minX)?vert[i].x:minX;
        minY = (vert[i].y<minY)?vert[i].y:minY;
        maxX = (vert[i].x>maxX)?vert[i].x:maxX;
        maxY = (vert[i].y>maxY)?vert[i].y:maxY;
    }
    this->maxP.x = maxX;
    this->maxP.y = maxY;
    this->minP.x = minX;
    this->minP.y = minY;
}

bool Polygon::isInside(Point2d p, bool& isOn)
{
    if (p<minP||p>maxP) //out of limits
    {
        isOn = false;
        return false;
    }
    else
    {
        Line2d line(p,Point2d(this->maxP.x+1,p.y));
        double a = 2;
        double b = 2;
        int i = 0;
        int count = 0;
        int numVert = this->external.size();
        bool parallel =false;
        bool inter = false;
        while((i<numVert)&&a!=0)
        {
            inter = line.isOnSegment(this->external[i], a, b, parallel);
            if(inter && !parallel)
            {
                i+=1;
                count+=1;
            }
            else
            {
                i+=1;
            }
        }
        if(a==0)
        {
            isOn = true;
            return true;
        }
        else if((count%2)==0)
        {
            isOn = false;
            return false;
        }
        else
        {
            isOn = false;
            return true;
        }

    }
}

void Polygon::addHole(std::vector<Point2d> vert)
{
    //checks if all points lie inside external
    //this->internals.push_back(vert);
}

Polygon::~Polygon()
{

}
