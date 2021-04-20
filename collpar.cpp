#include "collpar.h"
#include"AuxFunctions.h"
#include<iostream>
#include </usr/lib/gcc/x86_64-linux-gnu/9/include/omp.h>

CollPar::CollPar()
{

}

CollPar::CollPar(DomainPoints domain, Polygon poly)
{
    std::vector<double> finalFractions; //to strore the final fractions
    std::vector<double> initialFractions(domain.propWithCollDir.size(), 1.0); //first fractions are all ones/to store intermediary fractions
    std::vector<Point2d> wallPoints; //to store the intermediary wall points
    std::vector<Point2d> finalWallPoints; //to store the final wall points
    std::vector<std::vector<int>> finalPath; //to store the final path
    std::vector<std::vector<int>> initialPath; //to store intermediary paths
    firstColl(domain, poly, initialPath, finalPath, initialFractions, finalFractions, wallPoints, finalWallPoints);
    newColl(domain, poly, initialPath, finalPath, initialFractions, finalFractions, wallPoints, finalWallPoints);
    //firstColl(domain, poly, initialPath, finalPath, initialFractions, finalFractions, wallPoints, finalWallPoints);
    std::cout<<"Ate aqui esta indo legal, eu acho"<<std::endl;
}

void CollPar::firstColl(DomainPoints domain, Polygon poly, std::vector<std::vector<int>>& initialPath, std::vector<std::vector<int>>& finalPath, std::vector<double>& initialFractions,
                                                 std::vector<double>& finalFractions, std::vector<Point2d>& wallPoints, std::vector<Point2d>& finalWallPoints)
{
    //std::vector<std::vector<int>> result; //acho que não precisa também
    //fractions.clear(); //preciso mesmo disso?
    //wallPoints.clear(); //acho que não preciso disso tambem
    #pragma omp parallel
    {
        std::vector<double> threadFractions; //fraction left after a intermediary collision => use to find point of collision
        std::vector<double> threadFinalFractions; //fractions left after a final collision => use to find the final point
        std::vector<std::vector<int>> threadInitialPath; //intermediary path traveled
        std::vector<std::vector<int>> threadFinalPath; //final path traveled
        std::vector<Point2d> threadWallPts; //intermediary wall hited point
        std::vector<Point2d> threadFinalWallPts; //final wall hited point
        Point2d pInt; //current point of intersection
        double fraction; //current fraction after collision
        bool isOver; //use to check if the colision is over (no collision)
        Point2d p0; //initial point
        int dir;
        #pragma omp for firstprivate(domain, poly)
        for(int i = 0; i < domain.propWithCollDir.size(); i++)
        {
            std::vector<int> collisionParameters; //vector with parameters of interest
            collisionParameters.push_back(domain.propWithCollDir[i][0]); //inital point id
            collisionParameters.push_back(domain.propWithCollDir[i][1]); //initial direction id

            //===================== change this section to handle with inter paths ==============================================
            p0 = domain.domainPoints[domain.propWithCollDir[i][0]]; //initial point => this will change in the next collisions
            dir = domain.propWithCollDir[i][1]; //current direction id => this will change in the next collisions
            //===================================================================================================================

            fraction = initialFractions[i]; //initial fraction
            std::vector<int> tempOutDirPar; //vector to store all collision parameters
            std::vector<int> tempOutDir; //vector used to store only the output directions
            tempOutDirPar = dirOut(p0, domain.lattice, dir, fraction, poly, isOver, pInt); //colisions parameters
            tempOutDir.insert(tempOutDir.begin(),tempOutDirPar.begin()+2,tempOutDirPar.end()); //output directions
            collisionParameters.push_back(tempOutDirPar[0]); //wall point id
            collisionParameters.push_back(tempOutDirPar[1]); //number of out directions => this will be comom to all out directions
            for(unsigned int j = 0; j < tempOutDir.size();j++)
            {
                if(isOver) //copy the results into the final vectors (do not change anymore)
                {
                    threadFinalFractions.push_back(fraction); //last fraction (fraction does not change if there is no hit)
                    threadFinalWallPts.push_back(p0); //last wall point hited is p0
                    std::vector<int> pathChoosen = collisionParameters; //inital point id, initial dir id, wall id, number of out directions
                    pathChoosen.push_back(tempOutDir[j]); //direction chosen
                    pathChoosen.insert(pathChoosen.end(),tempOutDir.begin(),tempOutDir.end()); //all possible directions
                    threadFinalPath.push_back(pathChoosen); //format => [p0_id dir_id wall_id number_out_dir dir_choosen_id all_dir_out ... dir_id wall_id number_out_dir dir_choosen_id all_dir_out]
                }
                else //copy the results into intermediary vectors (can change in other iterations)
                {
                    threadFractions.push_back(fraction);
                    threadWallPts.push_back(pInt);
                    std::vector<int> pathChoosen = collisionParameters; //inital point id, initial dir id, wall id, number of out directions
                    pathChoosen.push_back(tempOutDir[j]); //direction chosen
                    pathChoosen.insert(pathChoosen.end(),tempOutDir.begin(),tempOutDir.end()); //all possible directions
                    threadInitialPath.push_back(pathChoosen);
                }
            }
        }
        #pragma omp barrier
        {
            #pragma omp single
            {
                initialFractions.clear(); //clear used fractions to receive new ones
                wallPoints.clear(); //clear used wall points to receive new ones
            }
        }
        #pragma omp critical
        {
            initialPath.insert(initialPath.end(),threadInitialPath.begin(),threadInitialPath.end()); //intermediary path
            initialFractions.insert(initialFractions.end(),threadFractions.begin(),threadFractions.end()); //intermediary fractions
            wallPoints.insert(wallPoints.end(),threadWallPts.begin(),threadWallPts.end()); //intermediary wall points

            finalPath.insert(finalPath.end(),threadFinalPath.begin(),threadFinalPath.end()); //final path
            finalFractions.insert(finalFractions.end(),threadFinalFractions.begin(),threadFinalFractions.end()); //final fraction (maybe unecessary)
            finalWallPoints.insert(finalWallPoints.end(),threadFinalWallPts.begin(),threadFinalWallPts.end()); //final colision point
        }
    }
}

void CollPar::newColl(DomainPoints domain, Polygon poly, std::vector<std::vector<int>>& initialPath, std::vector<std::vector<int>>& finalPath, std::vector<double>& initialFractions,
                                                 std::vector<double>& finalFractions, std::vector<Point2d>& wallPoints, std::vector<Point2d>& finalWallPoints)
{
    #pragma omp parallel
    {
        std::vector<double> threadFractions; //fraction left after a intermediary collision => use to find point of collision
        std::vector<double> threadFinalFractions; //fractions left after a final collision => use to find the final point
        std::vector<std::vector<int>> threadInitialPath; //intermediary path traveled
        std::vector<std::vector<int>> threadFinalPath; //final path traveled
        std::vector<Point2d> threadWallPts; //intermediary wall hited point
        std::vector<Point2d> threadFinalWallPts; //final wall hited point
        Point2d pInt; //current point of intersection
        double fraction; //current fraction after collision
        bool isOver; //use to check if the colision is over (no collision)
        Point2d p0; //initial point
        int dir;
        #pragma omp for firstprivate(domain, poly)
        for(int i = 0; i < initialPath.size(); i++)
        {
            std::vector<int> collisionParameters; //vector with parameters of interest
            collisionParameters.push_back(domain.propWithCollDir[i][0]); //inital point id
            collisionParameters.push_back(domain.propWithCollDir[i][1]); //initial direction id
            //===================== change this section to handle with inter paths ==============================================
            p0 = wallPoints[i];
            dir = lastDirChoosen(initialPath[i]); //current direction id => this will change in the next collisions
            //===================================================================================================================
            fraction = initialFractions[i]; //initial fraction
            std::vector<int> tempOutDirPar; //vector to store all collision parameters
            std::vector<int> tempOutDir; //vector used to store only the output directions
            tempOutDirPar = dirOut(p0, domain.lattice, dir, fraction, poly, isOver, pInt); //colisions parameters
            tempOutDir.insert(tempOutDir.begin(),tempOutDirPar.begin()+2,tempOutDirPar.end()); //output directions
            collisionParameters.push_back(tempOutDirPar[0]); //wall point id
            collisionParameters.push_back(tempOutDirPar[1]); //number of out directions => this will be comom to all out directions
            for(unsigned int j = 0; j < tempOutDir.size();j++)
            {
                if(isOver) //copy the results into the final vectors (do not change anymore)
                {
                    threadFinalFractions.push_back(fraction); //last fraction (fraction does not change if there is no hit)
                    threadFinalWallPts.push_back(p0); //last wall point hited is p0
                    std::vector<int> pathChoosen = collisionParameters; //inital point id, initial dir id, wall id, number of out directions
                    pathChoosen.push_back(tempOutDir[j]); //direction chosen
                    pathChoosen.insert(pathChoosen.end(),tempOutDir.begin(),tempOutDir.end()); //all possible directions
                    threadFinalPath.push_back(pathChoosen); //format => [p0_id dir_id wall_id number_out_dir dir_choosen_id all_dir_out ... dir_id wall_id number_out_dir dir_choosen_id all_dir_out]
                }
                else //copy the results into intermediary vectors (can change in other iterations)
                {
                    threadFractions.push_back(fraction);
                    threadWallPts.push_back(pInt);
                    std::vector<int> pathChoosen = collisionParameters; //inital point id, initial dir id, wall id, number of out directions
                    pathChoosen.push_back(tempOutDir[j]); //direction chosen
                    pathChoosen.insert(pathChoosen.end(),tempOutDir.begin(),tempOutDir.end()); //all possible directions
                    threadInitialPath.push_back(pathChoosen);
                }
            }
        }
        #pragma omp barrier
        {
            #pragma omp single
            {
                initialFractions.clear(); //clear used fractions to receive new ones
                wallPoints.clear(); //clear used wall points to receive new ones
            }
        }
        #pragma omp critical
        {
            initialPath.insert(initialPath.end(),threadInitialPath.begin(),threadInitialPath.end()); //intermediary path
            initialFractions.insert(initialFractions.end(),threadFractions.begin(),threadFractions.end()); //intermediary fractions
            wallPoints.insert(wallPoints.end(),threadWallPts.begin(),threadWallPts.end()); //intermediary wall points

            finalPath.insert(finalPath.end(),threadFinalPath.begin(),threadFinalPath.end()); //final path
            finalFractions.insert(finalFractions.end(),threadFinalFractions.begin(),threadFinalFractions.end()); //final fraction (maybe unecessary)
            finalWallPoints.insert(finalWallPoints.end(),threadFinalWallPts.begin(),threadFinalWallPts.end()); //final colision point
        }
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

std::vector<int> CollPar::dirOut(Point2d& p0, Lattice lattice, int dir, double& fraction, Polygon poly, bool& isOver, Point2d& wallPt)
{
    Point2d pInt; //possile point of intersection
    int id1, id2; //possible ids of wall collisions (id1 is the higher priority by the default)
    bool isUnique, isOn, pointIn; //dummy variables
    Line2d lineInt; //line from point of intersection to the possible out direction
    Line2d lineTest(p0, Point2d(fraction*lattice.ex[dir], fraction*lattice.ey[dir])); //line from p0 to the end of direction dir
    std::vector<int> result, outDirections;
    int count = 0; //number of possible out directions
    if(isPossibleDirOut(lineTest)) // can be a propagation direction (ends in a domain point)
    {
        if(poly.isHited(lineTest, pInt, id1, id2, isUnique, pointIn)) //propagates with collision
        {
            result.push_back(id1); // line hited id (id with higher priority)
            wallPt = pInt; //point hitted in the wall
            p0 = pInt; //new p0;
            fraction *= 1-(pInt.distance(lineTest.r0)/(lineTest.r0+lineTest.v).distance(lineTest.r0)); //new overall fraction after collision
            lineInt.r0.x = pInt.x; //new initial (collision) point
            lineInt.r0.y = pInt.y; //new initial (collision) point
            for (unsigned int i = 1; i < lattice.ex.size(); i++)
            {
                lineInt.v.x = fraction*lattice.ex[i]; //new final point
                lineInt.v.y = fraction*lattice.ey[i]; //new final point
                if(isPossibleDirOut(lineInt)&&(poly.isHited(lineInt,pInt,id1,id2,isUnique,pointIn))) //new line segment can be an out direction and hits a wall
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
        else if(pointIn) //propagates with no collision and ends inside polygon
        {
            result.push_back(dir); //
            isOver = true; //propagation is over
            return result;
        }
        else //propagates to outside of the polygon or is tangent to one of the sides of te poligon
        {
            std::cerr<<"not a propagation direction"<<std::endl;
            isOver = true;
            return result;
        }
    }
    else //can not be a propagation direction (not ends at a domain point)
    {
        std::cerr<<"Is not a possible out direction"<<std::endl;
        isOver = true;
        return result;
    }
}

int CollPar::lastDirChoosen(std::vector<int> collPar)
{
    int gap = collPar[2]; //collPar[0] = x0; collPar[1] = dir0; collPar[2] = numDirOut
    int nextPos = 3+gap;
    while (nextPos<collPar.size())
    {
        gap = collPar[nextPos];
        nextPos += (1+gap);
    }
    return collPar[nextPos];
}

CollPar::~CollPar()
{

}
