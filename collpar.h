#ifndef COLLPAR_H
#define COLLPAR_H

#include"domainpoints.h"

class CollPar
{
public:
    CollPar();
    CollPar(DomainPoints domain, Polygon poly);
    ~CollPar();
    std::vector<std::vector<int>> collPath;
private:
    bool isPossibleDirOut(Line2d line);
    //isPossibleDirOut => checks if the end point of line can be a domain point
    //@param bool => true if can be and false if can not be
    //@param Line2d line => the line to be tested
    std::vector<int> dirOut(Point2d& p0, Lattice lattice, int dir, double& fraction, Polygon poly, bool& isOver, Point2d& wallPt);
    //dirOut => vector with out directions of a propagation [wallId, numBerOfOut, OutIds] if there is a coll or [outId] is there is not
    //@param std::vector<int> => the out direction parameters
    //@param Point2d p0 => the starting point (and wall point if there is a hit)
    //@param Lattice lattice => the lattice considered
    //@param int dir => the direction of propagation
    //@param double& fraction => the fraction of lattice direction that is propagated (and fraction left after colision)
    //@param Polygon poly => the polygon inside which the propagation takes place
    //@ param bool& isOver => if there is other collision (false) or not (true)
    void firstColl(DomainPoints domain, Polygon poly, std::vector<std::vector<int>>& initialPath, std::vector<std::vector<int>>& finalPath, std::vector<double>& initialFractions,
                                            std::vector<double>& finalFractions, std::vector<Point2d>& initialWallPoints, std::vector<Point2d>& finalWallPoints);
    //firstColl => sets the parameters for the fisrt propagation
    //@param std::vector<std::vector<int>> => vector with parameters
    void newColl(DomainPoints domain, Polygon poly, std::vector<std::vector<int>>& initialPath, std::vector<std::vector<int>>& finalPath, std::vector<double>& initialFractions,
                                            std::vector<double>& finalFractions, std::vector<Point2d>& initialWallPoints, std::vector<Point2d>& finalWallPoints);
    //firstColl => sets the parameters for the fisrt propagation
    //@param std::vector<std::vector<int>> => vector with parameters
    int lastDirChoosen(std::vector<int> collPar);
};

#endif // COLLPAR_H
