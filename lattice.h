#ifndef LATTICE_H
#define LATTICE_H

#include <vector>

class Lattice
{
public:
    Lattice();
    Lattice(int order);
    ~Lattice();
    //members
    int numDir;
    int maxDisp;
    std::vector<int> ex;
    std::vector<int> ey;
    std::vector<int> ex2;
    std::vector<int> ey2;
    std::vector<double> e_dot_e;
    std::vector<double> ws;
    double as;
    double as2;
private:
    void setLattice(int& order);
};

#endif // LATTICE_H
