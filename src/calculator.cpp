#include "include/calculator.h"
int Calculator::Add(int a, int b) 
{
    return a+b;
}

double Calculator::CalculateInterest(const double principal, const std::string& type, const int term) const
{
    double rate = rates.at(type);
    return principal * rate * term / 365;
}
