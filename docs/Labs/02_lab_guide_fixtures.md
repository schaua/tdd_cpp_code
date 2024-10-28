# Lab 02

## Fixtures

We can continue to refactor the tests by noting that the duplicate creation of an instance of Portfolio could be moved out to a shared fixture. The idea of a fixture is common to many testing frameworks. It provides a place to code setup and tear down behavior that should take place before each and every test or after each and every test.  
To add the fixture two changes are needed.

1. Define a new class that inherits from the `Test` class in the `testing` namespace and modify the `TEST` macros to instead be `TEST_F`. We can name the class the same as the test suite name that we have been using to reduce the amount of code that needs to change. Add the new class at the top of the `portfoliotest.cpp` file.

```cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using testing::StartsWith;
using testing::Eq;

class PortfolioTest : public testing::Test
{
public:
    std::unique_ptr<Portfolio> portfolio;
    int owner_id{100};

    void SetUp() override
    {
        portfolio = std::make_unique<Portfolio>(owner_id);
    }

    void TearDown() override
    {
        // smart point takes care of everything
        // so far
    }
}
```

2. Update the TEST macro to TEST_F for any tests and where you wish to remove the creation of the `portfolio` resource from the test code. Since we are using smart pointers, change the method call to use pointer dereferencing.

```cpp
#include <gtest/gtest.h>
#include "../include/portfolio.h"

TEST(PortfolioTest, ANewPortfolioIsInitiallyEmpty)){
    // Arrange
    int expected{0};

    // Act
    int actual = portfolio->GetStockCount();

    // Assert
    EXPECT_EQ(actual, expected);
}
TEST_F(PortfolioTest, ThePortfolioMaintainsAReadonlyOwnerId)
{
    // Arrange
    int expected{owner_id};

    // Act
    int actual = portfolio->GetOwnerId();

    // Assert
    EXPECT_EQ(actual, expected);
}
```

3. Compile and run the tests to make sure that we are still Green.

## Review TDD Thinking

- Write a small failing test
- Get it to pass
- **Review and clean up the design**
- Ensure all the tests still pass
