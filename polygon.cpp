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
        for (unsigned int i = 0; i < (vert.size()-1); i++)
        {
            this->external.push_back({vert[i], vert[i+1]});
        }
        this->external.push_back({vert.back(), vert.front()});
    }
}
std::vector<std::vector<Point2d>> Polygon::createLines(std::vector<Point2d>& vert)
{
    if (vert.size()<3){
        std::cerr<<"not enougth points"<<std::endl;
        return std::vector<std::vector<Point2d>>{};
    }
    else
    {
        std::vector<std::vector<Point2d>> output;
        for (unsigned int i = 0; i < (vert.size()-1); i++)
        {
            output.push_back({vert[i], vert[i+1]});
        }
        output.push_back({vert.back(), vert.front()});
        return output;
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
