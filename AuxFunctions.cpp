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

bool isOnRange(const double& init, const double& fin, const double& refer)
{
    double max = (fin>init)?fin:init;
    double min = (init<fin)?init:fin;
    if(compareDouble(min, refer) || compareDouble(max, refer))
    {
        return true;
    }
    else if(refer>min && refer<max)
    {
        return true;
    }
    else
    {
        return false;
    }
}
