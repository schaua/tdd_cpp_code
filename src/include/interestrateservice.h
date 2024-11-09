#ifndef INTERESTRATESERVICE_H
#define INTERESTRATESERVICE_H
#include <rateservice.h>

// This is a double for a future component of the
// application that has not yet been implemented
class InterestRateService : public RateService
{
    public:
    double GetCurrentRate(const std::string& accountType) const override {return rates.at(accountType); }

    InterestRateService(std::string bankURL): bankURL_(bankURL){}

    ~InterestRateService() = default;

    private:
    std::string bankURL_;
    std::map<const std::string, double> rates = {
        {"CD", 0.05},
        {"Savings", 0.03},
        {"Checking", 0.01}
    };
};

#endif