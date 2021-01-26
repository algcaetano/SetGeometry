#include "polygon.h"
#include<iostream>

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
    this->minP = this->maxP = vert[0];
    for (unsigned int i = 0; i < vert.size(); i++)
    {
        if(vert[i]<this->minP)
        {
            this->minP = vert[i];
        }
        if (vert[i]>this->maxP)
        {
            this->maxP = vert[i];
        }
    }
}
bool Polygon::isInside(Point2d p)
{
    if (p<minP||p>maxP) //out of limits
    {
        return false;
    }
    else
    {
        return true;
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
