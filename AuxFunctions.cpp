#include "AuxFunctions.h"

double power(const double& base, int exp)
{
    double result = 1;
    for(int i = 0; i < exp; i++)
    {
        result*=base;
    }
    return result;
}

bool compareDouble(const double& d1, const double& d2)
{
    return (sqrt(power((d1-d2),2)) < 1e-14)? true:false;
}
