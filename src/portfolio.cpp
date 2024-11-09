#include <string>
#include <portfolio.h>

int Portfolio::GetStockCount(const std::string& symbol) const
{
    if (holdings_.contains(symbol))
        return holdings_.at(symbol);
    return 0;
}

int Portfolio::GetOwnerId() const
{
    return owner_id_;
}

void Portfolio::Buy(const int quantity, const std::string& symbol)
{
    if (holdings_.contains(symbol))
    {
        holdings_[symbol] += quantity;
    }
    else
    {
        holdings_[symbol] = quantity;
    }
}
