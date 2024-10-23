#include <stdexcept>
#include "../include/calculator.h"

int Calculator::Add(int a,int b)
{
    return a+b;
}

double Calculator::CalculateInterest(double principal, double rate, int time)
{
    // Negative time is nonsense
    if (time < 0)
        throw std::invalid_argument(
            "Time cannot be a negative value"
        );
    return principal * rate / 100 * time;
}
