#include "include/calculator.h"
#include <cmath>
#include <iostream>
int Calculator::Add(int a, int b) 
{
    return a+b;
}

double Calculator::CalculateInterest(const double principal, const std::string& type, const int term) const
{
    return CalculateInterest(principal, type, term, term);
}

double Calculator::CalculateInterest(const double principal, const std::string& type, const int term, const int compounded) const
{
    if (term < 0) throw std::invalid_argument("Term cannot be a negative value!");
    int times = term / compounded;
    double years = term / 365.0;
    double rate = rateService->GetCurrentRate(type);

    double amount = principal * std::pow((1 + rate/times),(times*years));
    return amount - principal;
    
}


