# Mock Walkthrough

## Manually Created Custom Double 

The following scenario has been added to the CalculateInterest behavior.

The application should use a web service to obtain the current interest rate for a specified type of account.  The use of an actual http connection would be a problem in TDD or any other unit testing.  The connection might fail, the rate being returned is unknown so expected result can not be determined.  The interest rate service itself has not even been written yet.  

In this walkthrough a double will be created to stand in for the interest rate service.

Since this is TDD, the first thing we need to do is write a test.

1. Create a new test using the `TEST_F` macro.

```cpp
TEST_F(InterestCalculatorTest, CalculateInterestAtSavingsRateOf5) 
{
    // Arrange
    std::string accountType{"Savings"};
    std::string bankURL{"https://mybank.com"};
    double principal{1000.0};
    double rate{}; // to be obtained from the service
    int time{1};
    double expected{50.0};
    std::unique_ptr<RateService> interestRateService =  std::make_unique<InterestRateService>(bankURL);
    
    // Act
    rate = interestRateService->GetCurrentRate(accountType)

    // Assert 
    EXPECT_DOUBLE_EQ(hp16c->CalculateInterest(principal, rate, time), expected);
}
```
2. The RateService will be an abstract class that describes the interface and allows the substitution of a double or mock for these tests.
```cpp
#ifndef RATESERVICE_H
#define RATESERVICE_H
#include <string>

class RateService
{
    public:
    virtual double GetCurrentRate(const std::string& accountType) const = 0;
    virtual ~RateService() = default;
};
#endif
```

3.  To get this test to even compile there needs to be the `InterestRateService` class defined that implements `RateService`.  For the present have `GetCurrentRate` return the literal value 5.0.

```cpp
// interestrateservice.h
#ifndef INTERESTRATESERVICE_H
#define INTERESTRATESERVICE_H

// This is a double for a future component of the
// application that has not yet been implemented
class InterestRateService : public RateService
{
    public:
    double GetCurrentRate(const std::string& accountType) const override {return 5.0 };

    InterestRateService(std::string bankURL): bankURL_(bankURL){}

    ~InterestRateService() = default;

    private:
    std::string bankURL_;
};

#endif
```

4.  Confirm that the test now passes.

5. Add another test for checking accounts with a rate of 2%.
```cpp
TEST_F(InterestCalculatorTest, CalculateInterestAtCheckingRateOf2) 
{
    // Arrange
    std::string accountType{"Checking"};
    std::string bankURL{"https://mybank.com"};
    double principal{1000.0};
    double rate{};
    int time{1};
    double expected{20.0};
    std::unique_ptr<RateService> interestRateService = std::make_unique<InterestRateService>(bankURL);

    // Act
    rate = interestRateService.GetCurrentRate(accountType)
    
    // Assert 
    EXPECT_DOUBLE_EQ(hp16c->CalculateInterest(principal, rate, time), expected);
}
```
6. This will fail with the simplistic implementation of `GetCurrentRate`.  Update the `InterestRateService` double implementation to check the accountType and return the correct amount.
```cpp

// Updated GetCurrentRate
    double GetCurrentRate(const std::string& accountType) const override {
        auto iter = rates.find(accountType);
        if (iter != rates.end())
            return iter->second;
        return 0;
     };
    
    private:
    std::map<std::string, double> rates{{"Checking", 2.0},{"Savings",5.0}};

```
7. Confirm that all of the tests still pass.

### Custom Double Summary
The `InterestRateService` is a custom double for a future component that will check the internet to get the current rates for the accounts.  There is a branch for this solution named `double` in the repository.  We will update this to use the google test mock features in the next portion of this walkthrough.

## gMock 
Instead of spending time writing (and debugging) a custom double class.  Many of the testing frameworks provide mock tools which can be setup to provide the necessary behavior.
1. Since the mock is only for testing purposes, move the `InterestRateService.h` into the `test` directory.

2. Change `InterestRateService` to be a mock implementation of the `RateService` interface.
```cpp
#include <gmock/gmock.h>
#include "../include/rateservice.h"

class InterestRateService : public RateService
{
    public:
    MOCK_METHOD(double, GetCurrentRate, (const std::string& accountType), (const override)); 

    InterestRateService(std::string bankURL):bankURL_(bankURL){}

    ~InterestRateService() : default;

    private:
    std::string bankURL_;
    // no longer any need for the rates map
}
```

3. Using the same two tests that we have created above modify the tests to use EXPECT_CALL to train a gMock object.  The file will need an include for gmock and a `using testing::Return` at the top.

```cpp
#include <gmock/gmock.h>

using testing::Return;

// ...

TEST_F(InterestCalculatorTest, CalculateInterestAtSavingsRateOf5) 
{
    // Arrange
    std::string accountType{"Savings"};
    std::string bankURL{"https://mybank.com"};
    double principal{1000.0};
    double rate{}; // to be obtained from mock service
    int time{1};
    double expected{50.0};
    auto mockService = std::make_unique<InterestRateService>(bankURL);
    EXPECT_CALL(*mockService, GetCurrentRate(accountType))
    .WillOnce(Return(5.0));

    // Act
    rate = interestRateService->GetCurrentRate(accountType)

    // Assert 
    EXPECT_DOUBLE_EQ(hp16c->CalculateInterest(principal, rate, time), expected);
}

TEST_F(InterestCalculatorTest, CalculateInterestAtCheckingRateOf2) 
{
    // Arrange
    std::string accountType{"Checking"};

    double principal{1000.0};
    double rate{}; // to be obtained from mock service
    int time{1};
    double expected{20.0};
    auto mockService = std::make_unique<InterestRateService>(bankURL);
    EXPECT_CALL(*mockService, GetCurrentRate(accountType))
    .Times(1) // try changing this to 3 
    .WillOnce(Return(2.0));

    // Act
    rate = interestRateService->GetCurrentRate(accountType)
    
    // Assert 
    EXPECT_DOUBLE_EQ(hp16c->CalculateInterest(principal, rate, time), expected);
}
```
4. Confirm that all tests are successful once again.

### Mock Summary
Using the mocking library it is not necessary to implement the logic for the double.  The mock can be trained to return the appropriate value when called.

### Refactoring
These is an opportunity here to look at refactoring these test, perhaps going with another parameterized set of tests.  Perhaps move the mock into the fixture and modify the EXPECT_CALL in each individual test (or using a param).

There are also so issues with the tests being fragile in dealing with rates other than 2 and 5.

There is also an issue here with what we are actually testing. `GetCurrentRate` may be outside the scope of what we are currently testing with  `hp16c`.  If there is time then add the `RateService` as a dependency to be passed to the `Calculator` for internal use.