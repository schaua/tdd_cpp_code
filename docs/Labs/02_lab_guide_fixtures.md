# Lab 02

## Fixtures

As part of refactoring it is important to consider whether to refactor the tests as well.  One option that the test frameworks provide is to move  duplicate creation logic such as creating an instance of the object under test, `Portfolio`, into a shared fixture class. The concept of a fixture is common to many testing frameworks. It provides a place to define setup and tear down behavior that will take place before each and every test or after each and every test.  

When using GoogleTest a fixture is defined by inheriting from the `Test` class, which is in the `testing` namespace.  That class provides virtual functions `SetUp` and `TearDown` that can be overridden to describe the necessary behaviors.   Once the class has been defined, the `TEST_F` macro associates it with an actual test.  This macro takes the fixture class name as the first argument and the test name as the second argument.  It adds the test as a member function of an object that inherits from the fixture class.  That allows `protected` fields to be visible within the test.

The fixture class is usually defined within the test code file, since it is specific to setting up the starting point for those tests, and moving it to a separate file would make it more difficult to read through and understand what setup is taking place.


### Step-by-Step

1. Define a new class that inherits from the `Test` class in the `testing` namespace.  We can name the class the same as the test suite name that we have been using to reduce the amount of code that needs to change. Add the new class at the top of the `portfoliotest.cpp` file.

```cpp
#include <gtest/gtest.h>
#include <portfolio.h>

class PortfolioTest : public testing::Test
{
    
};
```

2. Override the `SetUp` function in the new class. And move the duplicate code from the existing tests into the body of this function.
```cpp
#include <gtest/gtest.h>
#include <portfolio.h>

class PortfolioTest : public testing::Test
{
    void SetUp() override
    {
        int owner_id{100};
        Portfolio portfolio{owner_id};
    }
};
```
3. This will cause an error with `portfolio` no longer being visible.  Edit the fixture class to declare `portfolio` and `owner_id` as a `protected` fields.  When we initialize these in-line the need for `SetUp` goes away for now.  To prove that it is called before each test, add a `std::cout` statement.

```cpp
#include <gtest/gtest.h>
#include <portfolio.h>

class PortfolioTest : public testing::Test
{
protected:
        int owner_id{100};
        Portfolio portfolio{owner_id};
public:
    void SetUp() override
    {
        std::cout << "PortfolioTest::SetUp" << std::endl;
    }
}
```

4. The fixture is not yet associated with the tests.  Modify the test definition to use the `TEST_F` macro. 

```cpp
TEST_F(PortfolioTest, Given_a_new_portfolio_stock_count_is_zero)
{
    // Arrange
    int expected{0};

    // Act
    int actual{portfolio.GetStockCount("*")}; // The assumption is if * is passed return total count

    // Assert
    EXPECT_EQ(actual, expected);
}

TEST_F(PortfolioTest, Given_a_new_portfolio_get_owner_id_confirm_it_has_been_set)
{
    // Arrange

    // Act
    auto actual{portfolio.GetOwnerId()};

    // Assert
    EXPECT_EQ(actual, owner_id);
}

TEST_F(PortfolioTest, Given_a_new_portfolio_the_purchase_of_10_IBM_should_return_stock_count_of_10_for_IBM)
{
    // Arrange
    int expected{10};

    // Act
    portfolio.Buy(10, "IBM");
    int actual{portfolio.GetStockCount("IBM")};

    // Assert
    EXPECT_EQ(actual, expected);
}
```

5. Build and run the tests to make sure that all of the tests are still Green.

## Summary
This lab has refactored the tests to move duplicate code into a fixture.  Notice that it is only helpful to move  code that is shared by all of the tests associated with this fixture into the fixture.  So for example setting the expected value which is different each test would not likely be moved.

### Review TDD Thinking

- Write a small failing test
- Get it to pass
- **Review and clean up the design**
- Ensure all the tests still pass
