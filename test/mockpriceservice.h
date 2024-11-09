#ifndef MOCKPRICESERVICE_H
#define MOCKPRICESERVICE_H
#include <gmock/gmock.h>
#include <stockpriceservice.h>

class MockPriceService : public StockPriceService
{
public:
    MOCK_METHOD(double, GetStockPrice, (const std::string& symbol), (const override));
};
#endif