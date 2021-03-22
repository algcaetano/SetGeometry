#include "collpar.h"
#include"AuxFunctions.h"
#include<iostream>

CollPar::CollPar()
{

}

CollPar::CollPar(DomainPoints domain)
{
    for(int i = 0; i < domain.propWithCollDir.size(); i++)
    {

    }
}

bool CollPar::isPossibleDirOut(Line2d line)
{
    double x, y, fractpartX, intpartX, fractpartY, intpartY;
    x = (line.r0 + line.v).x;
    y = (line.r0 + line.v).y;
    fractpartX = modf(x, &intpartX);
    fractpartY = modf(y, &intpartY);
    return (compareDouble(fractpartX,0.5)&&compareDouble(fractpartY,0.5))?true:false;
}

std::vector<int> CollPar::dirOut(Point2d& p0, Lattice lattice, int dir, double& fraction, Polygon poly, bool& isOver)
{
    Point2d pInt; //possile point of intersection
    int id1, id2; //possible ids of collisions
    bool isUnique, isOn; //dummy variables
    Line2d lineInt; //line from point of intersection through the possible out direction
    Line2d lineTest(p0, Point2d(fraction*lattice.ex[dir], fraction*lattice.ey[dir])); //line from p0 into direction dir
    std::vector<int> result, outDirections;
    int count = 0;
    if(isPossibleDirOut(lineTest)) // can be a dir out
    {
        if(poly.isHited(lineTest, pInt, id1, id2, isUnique)) //propagates with collision
        {
            result.push_back((id1<id2)?id1:id2); // line hited id (for now, use the minnor id if there are two ids)
            p0 = pInt; //new p0;
            fraction *= 1-(pInt.distance(lineTest.r0)/lineTest.v.distance(lineTest.r0)); //new overall fraction after collision
            lineInt.r0.x = pInt.x; //new initial (collision) point
            lineInt.r0.y = pInt.y; //new initial (collision) point
            for (int i = 1; i < lattice.ex.size(); i++)
            {
                lineInt.v.x = fraction*lattice.ex[i]; //new final point
                lineInt.v.y = fraction*lattice.ey[i]; //new final point
                if(isPossibleDirOut(lineTest)&&(poly.isHited(lineInt,pInt,id1,id2,isUnique)||poly.isInside(lineInt.r0 + lineInt.v, isOn))) //new line segment can be an out direction? if yes, hit or end inside the polygon?
                {
                    count++;
                    outDirections.push_back(i);
                }
            }
            result.push_back(count); //number of out directions
            result.insert(end(result), begin(outDirections), end(outDirections)); //out directions
            isOver = false;
            return result;
        }
        else if(poly.isInside(lineTest.r0 + lineTest.v, isOn)) //propagates with no collision and ends inside polygon
        {
            result.push_back(dir);
            isOver = true;
            return result;
        }
        else
        {
            std::cerr<<"not a domain point"<<std::endl;
            isOver = true;
            return result;
        }
    }
    else
    {
        std::cerr<<"Is not a possible out direction"<<std::endl;
        isOver = true;
        return result;
    }
}

CollPar::~CollPar()
{

}
