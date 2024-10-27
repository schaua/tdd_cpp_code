# Lab 01

> NOTE: These lab instructions are based upon a project developing a stock portfolio application. The steps involved can be applied to any other development, so if there is something that would be more applicable to your future needs, feel free to substitute the specifics.

## Scenario

1. Start by capturing the initial description of the application. TDD is an iterative process, so do not attempt to capture all of the description. This information can be modified and supplemented as a better understanding develops during the TDD process.

The stock portfolio application tracks stocks owned by a specified owner. It should allow the puchase of a quantity of stock certificates and track the stock market price of those certificates that are in the portfolio. The application should also allow the owner to define rules that describe scenarios where an action should be taken. The action might be to notify the portfolio manager or perhaps to automatically buy or sell some quantity of the certificates in the portfolio.

2. The next step is to gather the initial requirements of the application. Again this does not need to be a complete list of all of the requirements, simply enough to get started on the TDD test writing. As new requirements are discovered they should be added to the list.

## Technical Requirements

The technical requirements are as listed:

1. Create a portfolio by assigning it to a specified owner.
2. When initially create the portfolio will not contain any stock certificates.
3. A quantity of stock certificates for a specified ticker symbol can be purchased. When a purchase has been completed the quantity of stocks in the portfolio will be increased. If stocks are sold the quantity of stocks in the portfolio will be decreased.
4. Stock purchases need to keep track of the date, the quantity and the unit price of the stock at the time of purchase.
5. The application will provide a service that will track the current trading price of the stocks.
6. The owner will be able to define rules that set criteria concerning a given stock and the action or actions that should be taken when that criteria is met.

There are plenty more requirements that could be defined, but this should get us started.

### Possible Objects and Behaviors

Review the requirements. The nouns that are mentioned there are likely to be good candidates for objects that the application will need. The verbs should give an idea of the behaviors that will be required. Use these for creating possible tests.

For example in this application there are the following nouns:

    Portfolio, Owner, Stock Certificate, Stock Market, Rule, Action

there are also the following verbs

    Buy, Sell, Update, Apply(Rule), Take(Action)

## Step 1 Possible Tests

Looking over the requirements, what might be a short list of 3-5 user stories that will get us started on the problem?

1. ***
2. ***
3. ***
4. ***
5. ***

Work through this step individually or in a group and try to list one or two simple starting **tests** that we could work on.

From the user stories come up with a simple test to start with.

- Identify the test that looks like it would the quickest one to complete. Ideally a TDD test should be small enough to write the test, provide the code to make the test pass and review it for refactoring in less than 10 minutes per test.

The `Portfolio` might be a good starting point for the TDD process. It is the object that tracks the stocks purchased by a particular owner. It starts out empty and with each transaction increases or decreases the quantity of a stock that is held.

## Step 2 Create the Project

Project Setup  
Use the notes from the slides to set up the project in a specific directory with a CMake file that includes google test.

### Step-by-Step

1. Create a new project directory called `StockPortfolio` and `cd` into that new directory.
2. Add a _CMakeLists.txt_ to the directory that should look something like this:

```bash
cmake_minimum_required(VERSION 3.15...3.28)
set(PROJNAME StockPortfolio)
set(CODE_UNDER_TEST StockPortfolioCode)
set(TEST_SPECS StockPortfolioTests)

project(${PROJNAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE MY_CODE_UNDER_TEST "src/*.cpp")
file(GLOB_RECURSE MY_TEST_SPECS "test/*.cpp")

add_library(${CODE_UNDER_TEST} STATIC ${MY_CODE_UNDER_TEST})
target_include_directories(${CODE_UNDER_TEST} PUBLIC src/include)
target_compile_features(${CODE_UNDER_TEST} PUBLIC cxx_std_20)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)

# For Windows: Prevent overriding the parent project's compiler/linker
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Make the fetched content (GoogleTest) available
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(${TEST_SPECS} ${MY_TEST_SPECS})
target_link_libraries(${TEST_SPECS} PUBLIC ${CODE_UNDER_TEST} gtest gmock gtest_main)
include(GoogleTest)
gtest_discover_tests(${TEST_SPECS})
```

3. Add the three sub-directories mentioned in the CMakeLists

- _include_
- _test_
- _src_

## Step 3 Write a failing test

Write the first test by adding a file to the _test_ directory. Have the test check that when a portfolio is initially created by assigning the `owner_id` that it contains zero stocks. Add in code for the first test. The test will immediately fail.

### Step-by-Step

1. Add _portfoliotest.cpp_ to the `test` sub-directory.

2. Edit `portfoliotest.cpp` and add the first test for the project.

```cpp
#include <gtest/gtest.h>
#include "../include/portfolio.h"

TEST(PortfolioTest, ANewPortfolioIsInitiallyEmpty){
    int owner_id{100};
    Portfolio portfolio(owner_id);
}
```

Part of the process is to find out if something is failing quickly, so build the project.

This is immediately a failing (Red) test because there is no _Portfolio_ class defined in the project.

3. So now we look at the minimum code necessary to get the test back to passing. That would be to define the _Portfolio_ class.

- Add the _portfolio.h_ file to the _src/include_ sub-directory.
- Edit `portfolio.h` and add the class declaration.

```cpp
class Portfolio {};
```

The test should now be passing (Green). Good, but it really doesn't test anything yet.

4. Expand the current test to better describe the requirement.

```cpp
#include <gtest/gtest.h>
#include "../include/portfolio.h"

TEST(PortfolioTest, ANewPortfolioIsInitiallyEmpty)){
    int owner_id{100};
    Portfolio portfolio{owner_id};
    int expected{0};
    int actual = portfolio.GetStockCount();
}
```

Once again we have a Red. The Portfolio class has no method named GetStockCount that returns an int. The class needs to be updated to get us back to Green. Before we jump into adding the method, it would be a good idea to consider the design. Is the count for all of the stocks, or for some specified stock? This might be something to add to the description and requirements list. For now assume that it is the count of all of the stocks held in the portfolio.

5. Implement the design for now. We can always change it
   later if a problem arises.

```cpp
// portfolio.h
#ifndef Portfolio_H
#define Portfolio_H
class Portfolio
{
    public:
    Portfolio(int owner_id);
    int GetStockCount() const;
};
#endif

// Portfolio.cpp
#include "../include/portfolio.h"

Portfolio::Portfolio(int owner_id)
{
    // there is no test to force doing something with the argument
}

int Portfolio::GetStockCount() const
{
    return 1;
}
```

Great, now we have the required method and it compiles.

6. Build the application and confirm that it now compiles. Back to Green!

The test still needs to be completed from a logic standpoint. We have the arrange part, and the act part, but we need the assert part of the standard test.

7. Add ASSERT or EXPECT

```cpp
#include <gtest/gtest.h>
#include "../include/portfolio.h"

TEST(PortfolioTest, ANewPortfolioIsInitiallyEmpty)){
    int owner_id{100};
    Portfolio portfolio{owner_id};
    int expected{0};
    int actual = portfolio.GetStockCount();
    EXPECT_EQ(actual, expected);
}
```

The project should still compile just fine, but now when we run the tests we are back to Red. That is a good thing. Our GetStockCount method does not return the correct results for the test to pass, so now we have a reason to go back to the code to fix that. Instead of returning the literal value 1 return the expected value, the literal value 0.

```cpp
int Portfolio::GetStockCount() const
{
    return 0;
}
```

Now we are back to Green. The test passes. As part of the TDD cycle we have gone from Red to Green and all that remains is to eliminate duplication and refactor while making sure that we remain Green.

8.  Refactoring

- Change any code that is unclear or not easily readable.
- Eliminate duplication.  
  In this case the test code seems clear, although adding in comments to separate the _Arrange_, _Act_ and _Assert_ sections might be useful. That should have no impact on the tests, but run them anyway to make sure.

```cpp
#include <gtest/gtest.h>
#include "../include/portfolio.h"

TEST(PortfolioTest, ANewPortfolioIsInitiallyEmpty)){
    // Arrange
    int owner_id{100};
    Portfolio portfolio{owner_id};
    int expected{0};

    // Act
    int actual = portfolio.GetStockCount();

    // Assert
    EXPECT_EQ(actual, expected);
}
```

How about looking for duplication. It may a be a bit early for refactoring.

9. Next Test
   Write a new failing test that that the owner_id is stored and can be returned at some future time.

```cpp
TEST(PortfolioTest, ThePortfolioMaintainsAReadonlyOwnerId)
{
    // Arrange
    int owner_id{100};
    Portfolio portfolio{owner_id};
    int expected{100};

    // Act
    int actual = portfolio.GetOwnerId();

    // Assert
    EXPECT_EQ(actual, expected);
}
```

We are back to Red with a failing test, which means we now have permission to write some code. In order for the test to pass the `GetOwnerId` method needs to append return the currently assigned owner_id. The minimal code that is required to get the test to pass will be for the constructor to store its argument into a field and for GetOwnerId to return that field.

In the header file add a new public function and private field;

```cpp
    int GetOwnerId() const;

    private:
    const int owner_id_;
```

```cpp
Portfolio::Portfolio(int owner_id): owner_id_(owner_id) {}

int Portfolio::GetOwnerId() const
{
    return owner_id_;
}
```

Perhaps the next test should be to buy a stock and confirm that the count increases.

```cpp
#include <gtest/gtest.h>
#include "../include/portfolio.h"

TEST(PortfolioTest, BuyingAStockIncreasesTheCountByTheQuantity)){
    // Arrange
    int owner_id{100};
    Portfolio portfolio{owner_id};
    int expected{42};
    std::string stock{""}; // start simple

    // Act
    portfolio.BuyStock(expected, stock);

    // Assert
    EXPECT_EQ(portfolio.GetStockCount(), expected);
}
```

This test uses a string to represent the stock. It is more likely that we need requirements describing the stock object.

Add the code to get back to Green and can look at refactoring. If any refactoring is done, run the tests again to make sure that everything is still passing.

## Review TDD Thinking

- Write a small failing test
- Get it to pass
- Add requirements to the list as discovered
