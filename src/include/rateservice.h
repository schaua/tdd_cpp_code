#ifndef RATESERVICE_H
#define RATESERVICE_H
#include <string>

class RateService
{
    public:
    virtual double GetCurrentRate(const std::string& accountType) const = 0;
    virtual ~RateService() = default;
};
#endif