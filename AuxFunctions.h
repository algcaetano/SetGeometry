#ifndef AUXFUNCTIONS_H
#define AUXFUNCTIONS_H

#include<math.h>


//functions declarations
bool compareDouble(const double& d1, const double& d2);
double power(const double& base, int exp);

//functions definitions
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

#endif // AUXFUNCTIONS_H
