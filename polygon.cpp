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

bool Polygon::isHited(Line2d line, Point2d& pInt, int& id, int& id2, bool& unique, bool& pointIn)
{
    double b, tempA; //tempA is the value that (pInt = r0 + tempA*v) of the line. b is the same for the side of the polygon
    double a = 2; //crossing point will result in a < 1
    bool isParallel; //dummy variable necessary for some methods
    bool tempIsCrossing = false; //initial status
    bool isCrossing = false; //return result
    Point2d pTest; //test point to check if is pointing inside
    bool isOn; //dummy variable to check if the collision point is over one of the sides
    bool tempPointIn; //pointInside status
    for (unsigned int i = 0; i < this->external.size(); i++) //check every side of the polygon
    {
        tempIsCrossing = line.isOnSegment(this->external[i], tempA, b, isParallel); //check if line is crossing the current side
        if(tempIsCrossing&&isParallel) //crosses and is parallel one with each other
        {
            pTest.x = (line.r0 + (line.v)*0.001).x; //ponto final deslocado no sentido da linha testada
            pTest.y = (line.r0 + (line.v)*0.001).y; //ponto final deslocado no sentido da linha testada
            tempPointIn = this->isInside(pTest,isOn); //verificar onde o ponto deslocado cai. Dentro do polígono, fora, ou sobre uma das linhas
            if(isOn) //cai sobre uma das linhas => a reta testada é tangente
            {
                pointIn = false; //do not pointing into domain
                return false; //do not hit and do not point into the domain
            }
        }
        if(tempIsCrossing&&(!compareDouble(tempA,0))) //se o segmento se cruza e o ponto de intersecção não é zero => TempA = 0 not considered (colision is on the line segment)
        {
            pTest.x = (line.r0 + (line.v)*(tempA/100)).x; //ponto deslocado no sentido do ponto de colisão
            pTest.y = (line.r0 + (line.v)*(tempA/100)).y; //ponto deslocado no sentido do ponto de colisão
            tempPointIn = this->isInside(pTest,isOn); //checa se ponto deslocado no sentido do ponto de colisão está dentro do polígono
            if(tempPointIn) //check if is pointing to the inside
            {
                if(compareDouble(tempA,a)) //two equal intersection points
                {
                    id2 = i; //new id
                    unique = false; //is not unique
                }
                else if(tempA<a) //new closest collision point
                {
                    a = tempA;
                    id = i;
                    pInt.x = (line.r0 + (line.v)*tempA).x;
                    pInt.y = (line.r0 + (line.v)*tempA).y;
                    isCrossing = true;
                    unique = true;
                    pointIn = true;
                }
            }
        }
    }
    if(!unique) //hitted a corner and there are two collision points. Order according the priority
    {
        int tempId = id;
        id = (this->externalPriority[id]>this->externalPriority[id2])?id:id2; //id is the one with higher priority
        id2 = (this->externalPriority[tempId]>this->externalPriority[id2])?id2:tempId; //id2 is the one with lower priority
    }
    if(!isCrossing) //chegou até aqui sem cruzar nenhum lado e não é paralelo a nenhum dos lados => segment pointing into the domain
    {
        pointIn = true;
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
