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
        this->externalID = std::vector<int>(this->external.size(),0);
        this->externalPriority = std::vector<int>(this->external.size(),0);
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
        Line2d line(p,Point2d(this->maxP.x+1,p.y)); //line segment from p to outside the polygon
        double a = 2;
        double b = 2;
        int i = 0;
        int count = 0;
        int numVert = this->external.size();
        bool parallel =false;
        bool inter = false;
        while((i<numVert)&&!compareDouble(a,0)) //run over all verts or skip if p is over one of the segments
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
        if(compareDouble(a,0)) //is over one of the sides
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

void Polygon::setExternalID(const int line, const int id)
{
    this->externalID[line] = id;
}

void Polygon::setExternalPrior(const int line, const int id)
{
    this->externalPriority[line] = id;
}

bool Polygon::isCrossing(Line2d refLine)
{
    double a, b; //dummy variables
    bool isParallel; //dummy variable
    bool isCrossing = false; //initial status
    unsigned int numVert = 0; //initial side
    while (!isCrossing && numVert < this->external.size()) //not crossing and not exceeding number of sides
    {
        isCrossing = refLine.isOnSegment(this->external[numVert], a, b, isParallel); //check if is crossing
        isCrossing = compareDouble(a,0)?false:isCrossing; //check if the intersection is the initial point
        numVert++; //new side
    }
    return isCrossing?true:false;
}

bool Polygon::isHited(Line2d line, Point2d& pInt, int& id, int& id2, bool& unique)
{
    double b, tempA;
    double a = 2; //crossing point will result in a < 1
    bool isParallel; //dummy variable
    bool tempIsCrossing = false; //initial status
    bool isCrossing = false; //return result
    Point2d pTest; //test point to check if is pointing inside
    bool isOn; //dummy variable
    bool pointIn; //pointInside status
    for (int i = 0; i < this->external.size(); i++)
    {
        tempIsCrossing = line.isOnSegment(this->external[i], tempA, b, isParallel); //check if is crossing
        if(tempIsCrossing&&isParallel) //segmento paralelo e se cruza
        {
            pTest.x = (line.r0 + (line.v)*0.001).x; //ponto final deslocado no sentido da linha testada
            pTest.y = (line.r0 + (line.v)*0.001).y; //ponto final deslocado no sentido da linha testada
            pointIn = this->isInside(pTest,isOn); //verificar onde o ponto deslocado cai
            if(isOn) //this direction is tangent to one of the sides and can not be considered
            {
                return false;
            }
        }
        else if(tempIsCrossing&&(!compareDouble(tempA,0))) //TempA = 0 not considered (colision is on the line segment)
        {
            pTest.x = (line.r0 + (line.v)*(tempA/10)).x;
            pTest.y = (line.r0 + (line.v)*(tempA/10)).y;
            pointIn = this->isInside(pTest,isOn);
            if(pointIn) //check if is pointing to the inside
            {
                if(compareDouble(tempA,a)) //two equal intersection points
                {
                    id2 = i;
                    unique = false;
                }
                else if(tempA<a) //new closest collision point
                {
                    a = tempA;
                    id = i;
                    pInt.x = (line.r0 + (line.v)*tempA).x;
                    pInt.y = (line.r0 + (line.v)*tempA).y;
                    isCrossing = true;
                    unique = true;
                }
            }
        }
    }
    if(!unique) //hitted a corner
    {
        int tempId = id;
        id = (this->externalPriority[id]>this->externalPriority[id2])?id:id2; //id is the one with higher priority
        id2 = (this->externalPriority[tempId]>this->externalPriority[id2])?id2:tempId;
    }
    return isCrossing;
}

void Polygon::addHole(std::vector<Point2d> vert)
{
    //future method to insert a hole into de domain
}

Polygon::~Polygon()
{

}
