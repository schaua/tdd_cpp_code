#include "../include/calculator.h"

int Calculator::Add(int a,int b)
{
    return a+b;
}

double Calculator::CalculateInterest(double principal, double rate, int time)
{
    return principal * rate / 100 * time;
}
