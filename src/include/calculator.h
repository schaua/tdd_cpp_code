#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <string>
#include <map>
class Calculator
{
    public:
    int Add(int a, int b);
    double CalculateInterest(const double principal, const std::string& type, const int term) const;
    double CalculateInterest(const double principal, const std::string& type, const int term, const int compounded) const;
    private:
    std::map<const std::string, double> rates = {
        {"CD", 0.05},
        {"Savings", 0.03},
        {"Checking", 0.01}
    };
};
#endif