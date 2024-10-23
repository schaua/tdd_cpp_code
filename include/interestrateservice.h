#ifndef INTERESTRATESERVICE_H
#define INTERESTRATESERVICE_H
#include "rateservice.h"

class InterestRateService : public RateService
{
    public:
    double GetCurrentRate(const std::string& accountType) const override {
        auto iter = rates.find(accountType);
        if (iter != rates.end())
            return iter->second;
        return 0;
    };
    
    InterestRateService(std::string bankURL) : bankURL_(bankURL) {}

    ~InterestRateService() = default;
    
    private:
    std::string bankURL_;
    std::map<std::string, double> rates{{"Checking",2.0},{"Savings", 5.0}};
};
#endif