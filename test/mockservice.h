#ifndef MOCKRATESERVICE_H
#define MOCKRATESERVICE_H
#include <gmock/gmock.h>
#include <rateservice.h>

class MockRateService : public RateService
{
        public:
    MOCK_METHOD(double, GetCurrentRate, (const std::string& accountType),(const override));

    MockRateService(std::string bankURL){}
    ~MockRateService() = default;
};
#endif