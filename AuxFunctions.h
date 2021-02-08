#pragma once

#ifndef AUXFUNCTIONS_H
#define AUXFUNCTIONS_H

#include<math.h>
#include<vector>

//functions declarations
bool compareDouble(const double& d1, const double& d2);
int power(const int& base, int exp);
double power(const double& base, int exp);
std::vector<int> power(const std::vector<int>& base, int exp);
bool isOnRange(const double& init, const double& fin, const double& refer);

#endif // AUXFUNCTIONS_H
