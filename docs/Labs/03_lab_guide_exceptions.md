# Lab 03

## Scenario

It is time to consider additional tests.  Looking at the requirements another possible test would be to confirm that the `Buy` function will not allow a negative quantity.  Logically this would be selling stocks using a function defined for aquiring stocks.  Consider what would be an appropriate response to such as situation.  It might be appropriate just to ignore the bad data, or it might be critical enough to the business domain that this type of behavior raise a red flag.  Discussion with the project owner leads to the decision that a negative stock puchase should raise an exception in the program.  

Add a test that will check that an exception is raised if the stock quantity is less than zero.  Also confirm that the stock quantity values are isolated based upon the stock symbol.

### Step-by-Step

1. Add a new test for Buy to confirm that a negative quantity is not allowed.

```cpp
TEST_F(PortfolioTest, BuyNegativeQuantityFails)
{
    EXPECT_THROW(portfolio->Buy(-1, "IBM"), std::invalid_argument);
}
```

9. Looking at the `Buy` method, this looks pretty complicated. Perhaps if we refactor it can be made simpler. STOP! Refactoring is only allowed when we have come back to Green. We should not refactor in order to write a new test. We like the idea behind this test, but in order to refactor while Green we need to disable it temporarily. That could be done by commenting it out, or we can take advantage of the `DISABLED_` prefix to ask Google Test to skip over this one.

```cpp
TEST_F(PortfolioTest, Given_a_portfolio_the_purchase_of_negative_quantity_throws_an_exception)
{
    // Arrange
    // Act
    // Assert 
    EXPECT_THROW(portfolio.Buy(-1, "IBM"), std::invalid_argument);
}
```

10. This causes a failing test since no exception is thrown.  Update the definition of `Buy` to check the quantity is not less than zero.  If it is, throw a `std::invalid_argument` exception, with an appropriate message.

```cpp
void Portfolio::Buy(const int quantity, const std::string& symbol)
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
```

11. This causes a minor error until we add the header file for `stdexcept`.
```cpp
#include <stdexcept>
```

12. Confirm that all of the tests are Green.  

13. What other tests might we add at this point.  Based on the current application state, there is no confirmation that purchasing one stock does not effect the quantity of a different stock.  Add a new test to confirm this behavior is as expected.

```cpp
TEST_F(PortfolioTest, Given_a_new_portfolio_the_purchase_of_10_IBM_should_return_stock_count_of_0_for_GOOGL)
{
    // Arrange
    int expected{0};

    // Act
    portfolio.Buy(10, "IBM");
    int actual{portfolio.GetStockCount("GOOGL")};

    // Assert
    EXPECT_EQ(actual, expected);
}
```

14. This passes, which seeems to confirm the code is correct.  Add another tests to confirm that the total is modified by the purchase of a stock.

```cpp
TEST_F(PortfolioTest, Given_a_new_portfolio_the_purchase_of_10_IBM_should_return_stock_count_of_10_for_a_total)
{
    // Arrange
    int expected{10};

    // Act
    portfolio.Buy(expected, "IBM");
    int actual{portfolio.GetStockCount("*")};

    // Assert
    EXPECT_EQ(actual, expected);
}
```

15. This test fails!  Check the logic for `GetStockCount` and notice that the earlier test was passing because the function returns zero if there is not matching symbol.  This time is is supposed to return the sum of the quantities in the map if the symbol is an asterisk.  Modify the function.
```cpp
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
```
16. Confirm that all of the tests pass.

## Summary
This lab incorporates exceptions as a valid response to unexpected behavior.  It also adds additional tests to confirm the expected behavior and catches errors in initial code.

