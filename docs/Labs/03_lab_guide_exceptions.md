# Lab 03

1. Choosing the next test
   Looking at the To-Do list the next candidate for a test looks might be that adding an existing stock should increase the count for that stock. We can start with a test to confirm the quantity for a give stock.

The following steps run through one possible choice for the next test to write.

2. We write a new small failing test.

```cpp
TEST_F(PortfolioTest, AddingAnExistingStockIncreasesTheCountForThatStock)
{
    int qty{10};
    int start = portfolio->GetStockCount("IBM")
    int expected{start + qty};
    ASSERT_THAT(portfolio->GetStockCount("IBM"), Eq(expected));
}
```

We may have hit Red several times in writing this test. The original GetStockCount didn't take an argument. Let's add to the project requirements that if no symbol is provided the count is the total count for all stocks. If a symbol is provided then the count should only reflect the count for that particular stock.

```cpp
void Buy(const int quantity, const std::string symbol)
{
    stock_count_ += quantity;
}

int Portfolio::GetStockCount(const std::string symbol) const
{
    return stock_count_;
}
```

But the test still fails. Since we are not paying attention to the symbol. This is going to require the addition of some sort of collection to hold the stocks. A likely candidate would be a Map with the key as the stock symbol and the value as the quantity of the stock symbol held.

3. We need to fix the logic to get back to Green.

```cpp
// portfolio.h
private:
std::map<std::string, int> stocks{};

// portfolio.cpp
void Portfolio::Buy(const int quantity, const std::string symbol)
{
    if (stocks.contains(symbol))
        stocks[symbol] += quantity;
    else
        stocks[symbol] = quantity;
}

int Portfolio::GetStockCount(const std::string symbol)
{
    if (stocks.contains(symbol))
        return stocks[symbol];
    return 0;
}
```

Now we are back to Green and can look at further clean up. This might require the addition of helper functions. This is considered part of refactoring and the test coverage would be because it was originally in code under test.

4. Now we're back to Green, so lets push the generalized solution a bit further. Add a third case to the `GetStockWithoutSymbolReturnsTotal` test.

```cpp
TEST_F(PortfolioTest, GetStockWithoutSymbolReturnsTotal)
{
    portfolio->Buy(10, "IBM");
    portfolio->Buy(10, "GOOGL");

    int expected{20};

    EXPECT_EQ(portfolio->GetStockCount("IBM"), expected);
    EXPECT_EQ(portfolio->GetStockCount("GOOGL"), expected);
    EXPECT_EQ(portfolio->GetStockCount(), expected);
}
```

5. The requires an overload of the GetStockCount function.

```cpp
int Portfolio::GetStockCount()
{
    int total{0};
    for (auto stock : stocks)
    {
        total += stock.second;
    }
    return total;
}
int Portfolio::GetStockCount(const std::string symbol)
{
    return stocks[symbol];
}
```

6. Consider any refactoring that would be helpful at this time.

7. Confirm that we are still Green and then look at the test. Do we really need three expects to remain confident that the rule is being met? Probably not, so lets eliminate two of them, set the remaining back to `EXPECT_EQ` and choose a different value, just as a bonus to boost our confidence.

```cpp
TEST_F(PortfolioTest, GetStockWithoutSymbolReturnsTotal)
{
    portfolio->Buy(10, "IBM");
    portfolio->Buy(20, "GOOGL");

    int expected{30};

    EXPECT_EQ(portfolio->GetStockCount(), expected);
}
```

8. So we're are all set. Clear clean code and tests to cover it. Let's add a new test for Buy to confirm that a negative quantity is not allowed.

```cpp
TEST_F(PortfolioTest, BuyNegativeQuantityFails)
{
    EXPECT_THROW(portfolio->Buy(-1, "IBM"), std::invalid_argument);
}
```

9. Looking at the `Buy` method, this looks pretty complicated. Perhaps if we refactor it can be made simpler. STOP! Refactoring is only allowed when we have come back to Green. We should not refactor in order to write a new test. We like the idea behind this test, but in order to refactor while Green we need to disable it temporarily. That could be done by commenting it out, or we can take advantage of the `DISABLED_` prefix to ask Google Test to skip over this one.

```cpp
TEST_F(PortfolioTest, DISABLED_BuyNegativeQuantityFails)
{
    EXPECT_THROW(portfolio->Buy(-1, "IBM"), std::invalid_argument);
}
```

10. Now we are back to Green, with an information message that one test is currently disabled. Great, let's take a look at `Buy` and see how we want to refactor.

11. Okay. We're still Green after refactoring and can re-enable the test, which will now fail. So let's negative purchases.

```cpp
void Portfolio::Buy(const int quantity, const std::string symbol)
{
    if (quantity < 0)
        throw std::invalid_argument("quantity cannot be negative");
    if (stocks.contains(symbol))
        stocks[symbol] += quantity;
    else
        stocks[symbol] = quantity;
}
```

12. Back to Green and ready to refactor.

13. Still Green! Let's move on to the next test. How about selling a stock requiring that it be in the portfolio. That sounds reasonably easy.

```cpp
TEST_F(PortfolioTest, MustOwnStockToSellIt)
{
    EXPECT_THROW(portfolio->Sell(10, "IBM"), std::invalid_argument);
}
```

14. This fails like we wanted, but not because the test logic failed. There is no `Sell` function for testing.

```cpp
void Portfolio::Sell(const int quantity, const std::string symbol)
{
    if (!stocks.contains(symbol))
        throw std::invalid_arguments("Symbol does not exist");
}
```

Clean and Green!

15. Add additional tests to force the implementation of the Sell method, such as SellReducesStockCount.
