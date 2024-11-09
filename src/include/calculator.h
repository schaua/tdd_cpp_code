#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <string>
#include <map>
#include <memory>
#include <rateservice.h>

class Calculator
{
    public:
    Calculator() = default;
    Calculator(std::shared_ptr<RateService> rateservice):rateService(rateservice){}
    int Add(int a, int b);
    double CalculateInterest(const double principal, const std::string& type, const int term) const;
    double CalculateInterest(const double principal, const std::string& type, const int term, const int compounded) const;

    private:
    std::shared_ptr<RateService> rateService;
};
#endif