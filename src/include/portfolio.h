#ifndef PORTFOLIO_H
#define PORTFOLIO_H
#include <map>

class Portfolio
{
public:
    Portfolio(int owner_id):owner_id_(owner_id) {}
    int GetStockCount(const std::string& symbol) const;
    int GetOwnerId() const;
    void Buy(const int quantity, const std::string& symbol);
private:
    int owner_id_;
    std::map<const std::string, int> holdings_;
};
#endif