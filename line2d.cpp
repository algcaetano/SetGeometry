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

bool Line2d::isCrossing(Line2d& line, double& a, double& b, bool& isParallel)
{
    double v1VetV2 = this->cross(line);
    double drVetV2 = Line2d(Point2d(0,0), (line.r0-this->r0)).cross(line);
    if(compareDouble(v1VetV2,0))
    {
        if(compareDouble(drVetV2,0))
        {
            a = 2;
            b = 2;
            isParallel = true;
            return true;
        }
        else
        {
            a = 2;
            b = 2;
            isParallel = true;
            return false;
        }
    }
    else
    {
        a = drVetV2/v1VetV2;
        Point2d pInt = this->r0+this->v*a;
        b = line.calculateA(pInt);
        isParallel = false;
        return true;
    }
}

bool Line2d::isOnSegment(Line2d& line, double& a, double& b, bool& isParallel)
{
    if (isCrossing(line, a, b, isParallel))
    {
        if (isParallel)
        {
            double dist1 = calculateA(line.r0); //"a" para chegar no ponto inicial
            Point2d pf = line.r0+line.v;
            double dist2 = calculateA(pf); //"a" para chegar no ponto final
            double maxDist = (dist1>dist2)?dist1:dist2;
            double minDist = (dist1<dist2)?dist1:dist2;
            if (isOnRange(0,1,dist1)) //o ponto final está dentro do segmento
            {
                if (isOnRange(0,1,dist2)) //o ponto inicial está dentro do segmento
                {
                    a = (dist1<dist2)?dist1:dist2; //os dois pontos estão dentro do segmento, "a" é referente ao mais próximo
                    return true;
                }
                else //somente o ponto incial está dentro do segmento => tem que checar para onde aponta
                {
                    if (isOnRange(minDist,maxDist,0)) //the starting point of this line is between the initial and final points of the line tested
                    {
                        a = 0;
                        return true;
                    }
                    else
                    {
                        a = dist1;
                        return true;
                    }
                }
            }
            else //ponto inicial não faz parte do segmento
            {
                if (isOnRange(0,1,dist2)) //somente o ponto final faz parte do segmento
                {
                    if (isOnRange(minDist,maxDist,0)) //the starting point of this line is between the initial and final points of the line tested
                    {
                        a = 0;
                        return true;
                    }
                    else
                    {
                        a = dist2;
                        return true;
                    }
                }
                else //nem o ponto inicial nem o final do segmento testado está dentro deste segmento
                {
                    if (isOnRange(0,1,line.calculateA(this->r0)))
                    {
                        a = 0;
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }
        else
        {
            return (isOnRange(0,1,a)&&isOnRange(0,1,b))?true:false;
        }
    }
    else
    {
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
