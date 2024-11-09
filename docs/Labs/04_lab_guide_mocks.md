# Lab 04

## Scenario

Discussion about the business purpose of the application make it clear that the `Portfolio` should be able to report the current value.  This is calculated by getting the current price for each stock from a `StockPriceService` and multiplying that by the current quantity.  This should be available for each stock by symbol, and also as a grand total for the portfolio.  

There is currently not `StockPriceService` component available and for testing purposes any such component needs to return consistent values for the test to pass.  Add a mock `StockPriceService` to the project and call that when reporting the price for the stocks and the total for the portfolio.

### Step-by-Step


1. Write a new test to drive the creation of a class named `StockPriceService`.

```cpp
TEST_F(PortfolioTest, Given_a_portfolio_with_two_stocks_calculates_the_total_value)
{
    // Arrange
    portfolio.Buy(10, "IBM"); // 10 @ 100
    portfolio.Buy(20, "GOOGL"); // 20 @ 125
    double expected((10*100)+(20*125));
    // Act
    double actual = portfolio.GetStockValue("*");

    // Assert
    EXPECT_EQ(actual, expected);
}
```
2. This first drives the creation of the `GetValue` function.  A reasonable assumption is that the asterixk is used for a grand total and a stock symbol will later be used for individual values.  Declare the new function and a `StockPriceService` pointer field in the header file.  Add an overloaded constructor to populate the field.
```cpp
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
```
3. Define the new function to call a `StockPriceService` for each stock to get its current price.
```cpp
double Portfolio::GetStockValue(const std::string &symbol) const
{
    double total_value{0.0};

    if (holdings_.contains(symbol))
        total_value = holdings_.at(symbol) * stockPriceService->GetStockPrice(symbol) ;

    if (symbol == "*")
        total_value = std::accumulate(holdings_.begin(), holdings_.end(), 0,
            [this](const double prev_sum, const std::pair<std::string, int> &entry)
            {
                return prev_sum + (entry.second * stockPriceService->GetStockPrice(entry.first));
            });

    return total_value;
}
```
4. The `stockPriceService` does not exist and a mock will be used to provide this service for now.  Define the contract for the service in `stockpriceservice.h`.
```cpp
#ifndef STOCKPRICESERVICE_H
#define STOCKPRICESERVICE_H
#include <string>

class StockPriceSerivce
{
public:
    virtual double GetStockPrice(const std::string& symbol) = 0;
    virtual ~StockPriceSerivce() = default;
};
#endif
```
5. To support mocks add gmock to the link libraries list in `CMakeLists.txt`.
```yaml
# create the executable using the test specifications and the runner
add_executable(${PROJNAME}  ${TEST_SOURCES})
target_link_libraries(${PROJNAME} PUBLIC ${CODE_UNDER_TEST} gtest gtest_main gmock)
```
6. Add a mock of the `StockPriceService` in a file named `mockpriceservice.h` to the `test` directory, as this is only used during testing.
```cpp
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
```
7. Add code to the arrange section of the test to create a pointer to the mock service, and pass it to a new portfolio instance.  Also train the mock to return the expected values for the price. Based on the ealier test this would be 100 for IBM and 125 for GOOGL.  Notice that this test replaces the fixture provided portfolio with a local portfolio.
```cpp
TEST_F(PortfolioTest, Given_a_portfolio_with_two_stocks_calculates_the_total_value)
{
    // Arrange
    std::shared_ptr<MockPriceService> mock = std::make_shared<MockPriceService>();
    
    EXPECT_CALL(*mock, GetStockPrice("GOOGL"))
    .WillRepeatedly(testing::Return(125.0));
    
    EXPECT_CALL(*mock, GetStockPrice("IBM"))
    .WillRepeatedly(testing::Return(100.0));

    Portfolio portfolio{100, mock};
   
    portfolio.Buy(10, "IBM"); // 10 @ 100
    portfolio.Buy(20, "GOOGL"); // 20 @ 125
    double expected((10*100)+(20*125));

    // Act
    double actual = portfolio.GetStockValue("*");

    // Assert
    EXPECT_EQ(actual, expected);
}
```
8. Build and run to confirm the test passes.

9. Add a test to retrieve the two individual values.
```cpp
TEST_F(PortfolioTest, Given_a_portfolio_with_two_stocks_calculates_the_individual_values)
{
    // Arrange
    std::shared_ptr<MockPriceService> mock = std::make_shared<MockPriceService>();
    
    EXPECT_CALL(*mock, GetStockPrice("GOOGL"))
    .WillOnce(testing::Return(125.0));
    
    EXPECT_CALL(*mock, GetStockPrice("IBM"))
    .WillOnce(testing::Return(100.0));

    Portfolio portfolio{100, mock};
   
    portfolio.Buy(10, "IBM"); // 10 @ 100
    portfolio.Buy(20, "GOOGL"); // 20 @ 125
    double expectedIBM(10*100);
    double expectedGOOGL(20*125);
    // Act
    double actualIBM = portfolio.GetStockValue("IBM");
    // The mock has been trainined to respond if called once
    // uncomment the following line and run the test to see
    // how the mock responds if the mocked method is called
    // twice.
    // actualIBM = portfolio.GetStockValue("IBM");
    double actualGOOGL = portfolio.GetStockValue("GOOGL");

    // Assert
    EXPECT_EQ(actualIBM, expectedIBM);
    EXPECT_EQ(actualGOOGL, expectedGOOGL);
}
```
10. This test should pass immediately, however it provide some confidence that the values of the stock are independent of each other.  

11. Experiment with mocks by uncommenting the second assignment to actualIBM and see how the mock responds.  There should be not one, but two errors.  The first for calling more than once, and the second because the return will be the default value of zero for the second call and the EXPECT_EQ will fail.

> Generally the TDD principle is to write a failing test. The fact that this passed immediately might indicate that we are not taking small enough steps, and should consider our future moves carefully. If this becomes a common occurrence we should look at taking smaller incremental steps.

## Summary
This lab has introduced a mock object to represent behavior that is outside of the code currently being tested.  This mock allow for the return of known values to be sure that the code under test is performing as expected.  