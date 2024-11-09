#ifndef PORTFOLIO_H
#define PORTFOLIO_H
#include <map>
#include <memory>
#include <stockpriceservice.h>

class Portfolio
{
public:
    Portfolio(int owner_id):owner_id_(owner_id) {}
    Portfolio(int owner_id, std::shared_ptr<StockPriceService> sps):owner_id_(owner_id), stockPriceService(sps) {}
    int GetStockCount(const std::string& symbol) const;
    int GetOwnerId() const;
    void Buy(const int quantity, const std::string& symbol);
    double GetStockValue(const std::string& symbol) const;
private:
    int owner_id_;
    std::map<const std::string, int> holdings_;
    std::shared_ptr<StockPriceService> stockPriceService;
};
#endif