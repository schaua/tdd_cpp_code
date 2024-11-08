# Mocking with test library
Instead of spending time writing (and debugging) a custom double class.  Many of the testing frameworks provide mock tools which can be setup to provide the necessary behavior.  

The `RateService` abstract class provides the contract for the desired behavior the same as if we are manually creating a double, but now the expected behavior is povided by training the mock to return a specified result in response to a specific function call.  

There are also settings to make sure that the mock object is actually called during the execution of the code.  There is no need for a mock if it is never used.  

## Using gMock 
1. Edit the `CMakeLists.txt` file to add gmock as one of the link libraries.  This requires adding gmock to the `target_link_libraries` line after `add_executable`.

```cmake
add_executable(${PROJNAME}  ${TEST_SOURCES})
target_link_libraries(${PROJNAME} PUBLIC ${CODE_UNDER_TEST} gtest gtest_main gmock)
```
2.  The mock is only for testing purposes so create  `mockrateservice.h` in the `test` directory.  This file will describe the mock.  Add an include for `rateservice.h`.  
```cpp
#ifndef MOCKRATESERVICE_H
#define MOCKRATESERVICE_H
#include <rateservice.h>

class MockRateService : public RateService
{
    
};
#endif
```

3. Define `MockRateService` to be a mock implementation of the `RateService` interface by adding `MOCK_METHOD` macro descriptions of the functions that are to be called.  The macro will require including the `<gmock/gmock.h>` header.  The macro takes the return type as the first argument, the function name as the second argument.  The third argument is a list of the mocked function's arguments, and the final argument of the macro is any modifier.  In this case `const` and `override`.
```cpp
#ifndef MOCKRATESERVICE_H
#define MOCKRATESERVICE_H
#include <gmock/gmock.h>
#include <rateservice.h>

class MockRateService : public RateService
{
    public:
    MOCK_METHOD(double, GetCurrentRate, (const std::string& accountType),(const override));

    MockRateService(std::string bankURL){}
    ~MockRateService() = default;
};
#endif
```

4. In the testing file add the include statement for the mock rate service file to the list of includes.   The constructor for the Calculator needs to be passed a smart pointer to the mock rate service.  Edit `calculatorTests.cpp` to add the include statement.
```cpp
#include "./mockrateservice.h"
```
5. Modify the initialize statement for the Calculator hp12c to use the MockRateService.  This will be in both of the fixture classes defined in the test file.
```cpp
    Calculator hp12c{std::make_unique<MockRateService>("https://mybank.com")};
```

6. To use the mock, the mock will need to be trained on how to respond to the `GetCurrentRate` function call.  Update the two fixture classes to create the mockService and train it to return .05 for "CD", .03 for "Savings" and .01 for "Checking".  

 7. A problem appears because the mock service needs to be trained.  Therefor a pointer to the service is needed both in the `Calculator` and in the tests.  This requires change the `rateService` field to be a std::shared_ptr.  Since it is a shared pointer, the initialization can be simplified as well. 
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
    Calculator(std::shared_ptr<RateService> rateservice):rateService(rateservice){}
    int Add(int a, int b);
    double CalculateInterest(const double principal, const std::string& type, const int term) const;
    double CalculateInterest(const double principal, const std::string& type, const int term, const int compounded) const;

    private:
    std::shared_ptr<RateService> rateService;
};
#endif
 ```
8.  Add a shared_ptr to the MockService and pass that into the Calculator for each of the fixtures.  The test file will need an include for `gmock`, `mockservice.h` but not `interestrateservice.h`.  Also add a `using testing::Return;` statement just after the includes to make the return with the capital R available.  This is a function used in training the mock. Replace the definitions of  `CalculatorParamTests` and `CalculatorTests` fixtures with code to train a mock.


```cpp
// REMOVED #include <interestrateservice.h>
#include <gmock/gmock.h>
#include "./mockservice.h"

using testing::Return;

// ...

class CalculatorParamTests : public ::testing::TestWithParam<InterestTestParams> 
{
    protected:
    std::shared_ptr<MockRateService> mockService = std::make_shared<MockRateService>("https://mybank.com");
    Calculator hp12c{mockService};

    void SetUp() override 
    {
        EXPECT_CALL(*mockService, GetCurrentRate("CD"))
        .WillRepeatedly(Return(0.05));

        EXPECT_CALL(*mockService, GetCurrentRate("Savings"))
        .WillRepeatedly(Return(0.03));

        EXPECT_CALL(*mockService, GetCurrentRate("Checking"))
        .WillRepeatedly(Return(0.01));

    }
    // TearDwon is available if needed.
};

class CalculatorTests : public testing::Test
{
  protected:
    std::shared_ptr<MockRateService> mockService = std::make_shared<MockRateService>("https://mybank.com");
    Calculator hp12c{mockService};
    double principal;
    int term;
    std::string type;
  public:
    void SetUp() override
    {
        // train the mock

        EXPECT_CALL(*mockService, GetCurrentRate("CD"))
        .WillRepeatedly(Return(0.05));

        EXPECT_CALL(*mockService, GetCurrentRate("Savings"))
        .WillRepeatedly(Return(0.03));

        EXPECT_CALL(*mockService, GetCurrentRate("Checking"))
        .WillRepeatedly(Return(0.01));

        // any additional resources can be initialized here
        principal = 1000.0;
        term = 365;
        type = "CD";
        std::cout << "SetUp called" << std::endl;
    }

    void TearDown() override
    {
        // cleans up goes here
        std::cout << "TearDown called" << std::endl;
    }
};
```
4. The mocks are inside of the hp12c, so the tests do not need any editing.  Confirm that all tests are successful once again.

### Summary
Using the mocking library to implement the logic the `GetCurrentRate` behavior make writing a double for a non-existent service much easier.  The mock can then be trained to return the appropriate values when called.

There is also an issue here with holding onto the `RateService`.  Because it needs to be accessed from both the hp12c object and the test functions it can no longer be a unique pointer, but must be converted to a shared pointer.