# Mock Walkthrough

## Manually Created Custom Double 

The following scenario has been added to the CalculateInterest requirements.

The application should use a web service to obtain the current interest rate for a specified type of account.  

The use of an actual http connection would be a problem in TDD or any other unit testing.  The connection might fail, the rate being returned is unknown so expected result can not be determined.  

Another problem could be that the interest rate service component has not even been written yet.  

In this walkthrough a double will be created to stand in for the interest rate service.

First a stub will be manually created to double for the interest rate service.  Then the mocking library provided by GoogleTest will be used instead.

1. Refactor the `Calculator` class to remove the `rates` map and replace it with a `RateService` smart pointer.  Populate the smart point in the constructor.

```cpp
#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <string>
#include <map>
#include <memory>
#include <rateservice.h>

class Calculator
{
    public:
    Calculator() = default;
    Calculator(std::unique_ptr<RateService> rateservice):rateService(std::move(rateservice)){}
    int Add(int a, int b);
    double CalculateInterest(const double principal, const std::string& type, const int term) const;
    double CalculateInterest(const double principal, const std::string& type, const int term, const int compounded) const;

    private:
    std::unique_ptr<RateService> rateService;
    // std::map<const std::string, double> rates = {
    //     {"CD", 0.05},
    //     {"Savings", 0.03},
    //     {"Checking", 0.01}
    // };
};
#endif
```
2. The requirement is to use a RateService to get the rate from the internet.  This will require creating a new class to represent the RateService.  The RateService is going to be an abstract class that describes a contract of how to get a rate.  This will allow for the actual component to be substituted in once it is written and it also allows the substitution of a double or mock for the tests.  Create the abstract class in a new file `rateservice.h`.
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

3. This will cause some tests to fail because the `rates` field has been removed. Change the calls to `rates.at(type)` to call `rateService.GetCurrentRate(type)` instead.

4. Now the problem is that the `rateService` needs a concrete implementation of `RateService`.  Write a new class `InterestRateService` that inherits from `RateService`.
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
5. In the tests pass a smart point to an `InterestRateService` into the `Calculator` constructor.  This will be in both the fixture and the parameter fixture.
```cpp
    Calculator hp12c{std::make_unique<InterestRateService>("http://mybank.com")};
```
6.  The project should now build, but several tests fail.  Implement the `InterestRateService` function to return the interest rate.  While the internet is not available, use a map to stub out the behavior of the service.

```cpp
#ifndef INTERESTRATESERVICE_H
#define INTERESTRATESERVICE_H
#include <rateservice.h>

// This is a double for a future component of the
// application that has not yet been implemented
class InterestRateService : public RateService
{
    public:
    double GetCurrentRate(const std::string& accountType) const override {return rates.at(accountType); }

    InterestRateService(std::string bankURL): bankURL_(bankURL){}

    ~InterestRateService() = default;

    private:
    std::string bankURL_;
    std::map<const std::string, double> rates = {
        {"CD", 0.05},
        {"Savings", 0.03},
        {"Checking", 0.01}
    };
};

#endif
```
7. Confirm that all of the tests once again pass pass.

### Custom Double Summary
The `InterestRateService` is a custom double for a future component that will check the internet to get the current rates for the accounts.  
