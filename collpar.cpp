#include "collpar.h"
#include"AuxFunctions.h"
#include<iostream>

CollPar::CollPar()
{

}

CollPar::CollPar(DomainPoints domain, Polygon poly)
{
    for(int i = 0; i < domain.propWithCollDir.size(); i++)
    {
        Point2d p0 = domain.domainPoints[domain.propWithCollDir[i][0]];
        int dir = domain.propWithCollDir[i][1];
        double fraction = 1.0;
        bool isOver;
        std::vector<int> tempOutDir;
        this->collPath.push_back(dirOut(p0, domain.lattice, dir, fraction, poly, isOver));
    }
}

bool CollPar::isPossibleDirOut(Line2d line)
{
    double x, y, fractpartX, intpartX, fractpartY, intpartY;
    x = (line.r0 + line.v).x;
    y = (line.r0 + line.v).y;
    fractpartX = abs(modf(x, &intpartX));
    fractpartY = abs(modf(y, &intpartY));
    return (compareDouble(fractpartX,0.5)&&compareDouble(fractpartY,0.5))?true:false;
}

std::vector<int> CollPar::dirOut(Point2d& p0, Lattice lattice, int dir, double& fraction, Polygon poly, bool& isOver)
{
    Point2d pInt; //possile point of intersection
    int id1, id2; //possible ids of wall collisions
    bool isUnique, isOn; //dummy variables
    Line2d lineInt; //line from point of intersection through the possible out direction
    Line2d lineTest(p0, Point2d(fraction*lattice.ex[dir], fraction*lattice.ey[dir])); //line from p0 to end of direction dir
    std::vector<int> result, outDirections;
    int count = 0;
    if(isPossibleDirOut(lineTest)) // can be a propagation direction
    {
        if(poly.isHited(lineTest, pInt, id1, id2, isUnique)) //propagates with collision
        {
            result.push_back(id1); // line hited id (id with higher priority)
            p0 = pInt; //new p0;
            fraction *= 1-(pInt.distance(lineTest.r0)/(lineTest.r0+lineTest.v).distance(lineTest.r0)); //new overall fraction after collision
            lineInt.r0.x = pInt.x; //new initial (collision) point
            lineInt.r0.y = pInt.y; //new initial (collision) point
            for (int i = 1; i < lattice.ex.size(); i++)
            {
                lineInt.v.x = fraction*lattice.ex[i]; //new final point
                lineInt.v.y = fraction*lattice.ey[i]; //new final point
                if(isPossibleDirOut(lineInt)&&(poly.isHited(lineInt,pInt,id1,id2,isUnique))) //new line segment can be an out direction? if yes, hits any wall?
                {
                    count++;
                    outDirections.push_back(i);
                }
                else if(isPossibleDirOut(lineInt)&&poly.isInside(lineInt.r0 + lineInt.v, isOn)) //can be a out segment and can ends inside the polygon
                {
                    if(!isOn) //if is not on the line
                    {
                        count++;
                        outDirections.push_back(i);
                    }
                }
            }
            result.push_back(count); //number of out directions
            result.insert(end(result), begin(outDirections), end(outDirections)); //out directions
            isOver = false;
            return result;
        }
        else if(poly.isInside(lineTest.r0 + lineTest.v, isOn)) //propagates with no collision and ends inside polygon
        {
            if(!isOn)
            {
                result.push_back(dir); //
                isOver = true; //propagation is over
                return result;
            }
            else
            {
                std::cerr<<"not a propagation direction"<<std::endl;
                isOver = true;
                return result;
            }
        }
        else //propagates to outside of the polygon or tangent
        {
            std::cerr<<"not a propagation direction"<<std::endl;
            isOver = true;
            return result;
        }
    }
    else //can not be a propagation direction
    {
        std::cerr<<"Is not a possible out direction"<<std::endl;
        isOver = true;
        return result;
    }
}

CollPar::~CollPar()
{

}
