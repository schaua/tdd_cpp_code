#ifndef STOCKPRICESERVICE_H
#define STOCKPRICESERVICE_H
#include <string>

class StockPriceService
{
public:
    virtual double GetStockPrice(const std::string& symbol) const = 0;
    virtual ~StockPriceService() = default;
};
#endif