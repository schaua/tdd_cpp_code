#include <string>
#include <portfolio.h>
#include <stdexcept>
#include <numeric>

int Portfolio::GetStockCount(const std::string &symbol) const
{
    int total_quantity{0};

    if (holdings_.contains(symbol))
        total_quantity =  holdings_.at(symbol);

    if (symbol == "*")
        total_quantity = std::accumulate(holdings_.begin(), holdings_.end(), 0,
            [](const int prev_sum, const std::pair<std::string, int> &entry)
            {
                return prev_sum + entry.second;
            });

    return total_quantity;
}

int Portfolio::GetOwnerId() const
{
    return owner_id_;
}

void Portfolio::Buy(const int quantity, const std::string &symbol)
{
    if (quantity < 0)
        throw std::invalid_argument("quantity cannot be negative");

    if (holdings_.contains(symbol))
    {
        holdings_[symbol] += quantity;
    }
    else
    {
        holdings_[symbol] = quantity;
    }
}
