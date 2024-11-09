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
    Calculator(std::unique_ptr<RateService> rateservice):rateService(std::move(rateservice)){}
    int Add(int a, int b);
    double CalculateInterest(const double principal, const std::string& type, const int term) const;
    double CalculateInterest(const double principal, const std::string& type, const int term, const int compounded) const;

    private:
    std::unique_ptr<RateService> rateService;
    // std::map<const std::string, double> rates = {
    //     {"CD", 0.05},
    //     {"Savings", 0.03},
    //     {"Checking", 0.01}
    // };
};
#endif