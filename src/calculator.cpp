#include "include/calculator.h"
#include <cmath>
#include <iostream>
int Calculator::Add(int a, int b) 
{
    return a+b;
}

double Calculator::CalculateInterest(const double principal, const std::string& type, const int term) const
{
    double rate = rates.at(type);
    return principal * rate * term / 365;
}

double Calculator::CalculateInterest(const double principal, const std::string& type, const int term, const int compounded) const
{
    int times = term / compounded;
    double years = term / 365.0;
    double rate = rates.at(type);

    double amount = principal * std::pow((1 + rate/times),(times*years));
    return amount - principal;
    
}
