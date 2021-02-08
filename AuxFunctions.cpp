#include "AuxFunctions.h"

int power(const int& base, int exp)
{
    int result = 1;
    for(int i = 0; i < exp; i++)
    {
        result*=base;
    }
    return result;
}

double power(const double& base, int exp)
{
    double result = 1;
    for(int i = 0; i < exp; i++)
    {
        result*=base;
    }
    return result;
}

std::vector<int> power(const std::vector<int>& base, int exp)
{
    std::vector<int> result(base.size());
    for (unsigned int i = 0; i < base.size(); i++)
    {
        result[i] = (power(base[i],exp));
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
