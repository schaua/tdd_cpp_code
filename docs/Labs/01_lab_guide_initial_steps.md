# Lab 01

> NOTE: These lab instructions are based upon a project developing a stock portfolio application. The steps involved can be applied to any other development, so if there is something that would be more applicable to your future needs, feel free to substitute the specifics.

## Scenario

1. Start by capturing the initial description of the application. TDD is an iterative process, so do not attempt to capture all of the description. This information can be modified and supplemented as a better understanding develops during the TDD process.

The stock portfolio application tracks stocks owned by a specified owner. It should allow the puchase of a quantity of stock certificates and track the stock market price of those certificates that are in the portfolio. The application should also allow the owner to define rules that describe scenarios where an action should be taken. The action might be to notify the portfolio manager or perhaps to automatically buy or sell some quantity of the certificates in the portfolio.

2. The next step is to gather the initial requirements of the application. Again this does not need to be a complete list of all of the requirements, simply enough to get started on the TDD test writing. As new requirements are discovered they should be added to the list.

## Technical Requirements

The technical requirements are as listed:

1. Create a portfolio by assigning it to a specified owner.
2. When initially created the portfolio will not contain any stock certificates.
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

1. Create a new project directory called `StockPortfolio` and `cd` into that new directory.  It would be a good idea to `git init` so that the project is under version control.  This would also be the time to add a `.gitignore` file to ignore the `build` directory.  If the project is being worked on by multiple developers, it would also be good to ignore the `.vscode` directory where personal configuration for Visaual Studio Code is stored. To be safe ignore any binary files as well.  The contents of the `.gitignore` file should look something like the following:  

```txt
# ignore the build output files
build/   
# ignore the VS Code settings
.vscode/ 
# ignore any executable output
*.exe    
*.dll  
```

2. Create the `CMakeLists.txt` in the directory that defines the instructions for building the project.  This file should look something like this:

```bash
cmake_minimum_required(VERSION 3.10...3.28)
set (PROJNAME StockPortfolio)
set (CODE_UNDER_TEST StockPortfolioCode)
project(${PROJNAME} VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# locations for the different source files
file(GLOB_RECURSE COT_SOURCES "./src/*.cpp")
file(GLOB_RECURSE TEST_SOURCES "./test/*.cpp")

# create a library for the code under test
add_library(${CODE_UNDER_TEST} STATIC ${COT_SOURCES})
target_include_directories(${CODE_UNDER_TEST} PUBLIC src/include)

# ADD GOOGLETEST TEST
# USE GIT_TAG FROM THE DESIRED COMMIT (LATEST?)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY file:///c/projects/googletest/.git
  GIT_TAG v1.15.2 # latest release tag
)

# Make the fetched content declared above (googletest) available
FetchContent_MakeAvailable(googletest)

enable_testing()

# create the executable using the test specifications and the runner
add_executable(${PROJNAME}  ${TEST_SOURCES})
target_link_libraries(${PROJNAME} PUBLIC ${CODE_UNDER_TEST} gtest gtest_main)
include(GoogleTest)
gtest_discover_tests(${PROJNAME})
```

3. Add the three sub-directories mentioned in the CMakeLists with `include` being a sub-directory of `src`.  
```txt
 StockPortfolio
 |
 | - src
 |   |
 |   | - include
 |
 | - test
```
## Step 3 Write a failing test

Write the first test by adding a file to the `test` directory. The test can check that when a portfolio is initially created by assigning the `owner_id` and that it contains zero stocks. As the code is added for the first test there will be several failures.  First the header file will not exist when added as an include.  Then a compiler error as the `Portfolio` class has not been defined.  Then an error as the constructor that takes the `owner_id` has not been declared or defined.  The an error as the `GetStockCount` function has not been declared or defined.  As each error occurs, stop and get the application to compile, then run and eventually to pass the test by slowly adding code to the project.  

Either work on these steps independently, or take a look at the following detailed instructions.

### Step-by-Step

1. Add `portfoliotests.cpp` to the `test` sub-directory.

2. Edit `portfoliotests.cpp` and add the first test for the project.

```cpp
#include <gtest/gtest.h>
#include <portfolio.h>

TEST(PortfolioTest, Given_a_new_portfolio_stock_count_is_zero)
{
    int owner_id{100};
    Portfolio portfolio{owner_id};
}
```

3. A compiler error on `Portfolio`.  This is part of the TDD process.  Correct the error by declaring the `Portfolio` class in the newly added `portfolio.h` file.
```cpp
#ifndef PORTFOLIO_H
#define PORTFOLIO_H
class Portfolio
{

};
#endif
```
4. Now the error moves to the code that passes the id, as there is no such constructor.  Add a constructor to the `Portfolio`.  In-line the constructor to set an internal field with the value of the `owner_id` parameter.
```cpp
#ifndef PORTFOLIO_H
#define PORTFOLIO_H
class Portfolio
{
public:
    Portfolio(int owner_id):owner_id_(owner_id) {}
private:
    int owner_id_;
};
#endif
```
5. Continue to write the current test to better describe the requirement.  In particular get the stock count for all of the stocks.

```cpp
#include <gtest/gtest.h>
#include <portfolio.h>

TEST(PortfolioTest, Given_a_new_portfolio_stock_count_is_zero)
{
    int owner_id{100};
    Portfolio portfolio{owner_id};
    int expected{0};
    int actual{portfolio.GetStockCount("*")}; // The assumption is if not symbol is passed return total count
}
```
6. Once again it is Red (failing). The `Portfolio` class has no method named `GetStockCount` that returns an int. Update to get back to Green. Before jumping straight into adding the method, consider the design. The count is for all of the stocks and not some specified stock symbol.  Eventually a string will be passed as the symbol.  Should a wildcard string be passed for all, or will the lack of a symbol imply that the count is for all?   Another option would be to decide that a separate function can be defined for totol count vs specific count.  The results of this type of analysis is something to add to the description and requirements list. For now assume that the count of all of the stocks held in the portfolio if returned if an asterisk is passed inside of double quotes.

7. Implement this design. We can always change it later if problems arise.  Update the header file.

```cpp
#ifndef PORTFOLIO_H
#define PORTFOLIO_H
class Portfolio
{
public:
    Portfolio(int owner_id):owner_id_(owner_id) {}
    int GetStockCount(const std::string& symbol) const;
private:
    int owner_id_;
};
#endif
```
8. Add `portfolio.cpp` to the `src` directory.  The cpp file looks like this.  The test is expecting a return of 0, so just to be sure it fails when incorrectly defined, return a value of 1.
```cpp
#include <string>
#include <portfolio.h>

int Portfolio::GetStockCount(const std::string& symbol) const
{
    return 1;
}
```

9. Great, the required method is defined and it compiles.  Update the test to actually confirm the results are zero with the EXPECT_EQ macro.
```cpp
#include <gtest/gtest.h>
#include <portfolio.h>

TEST(PortfolioTest, Given_a_new_portfolio_stock_count_is_zero)
{
    int owner_id{100};
    Portfolio portfolio{owner_id};
    int expected{0};
    int actual{portfolio.GetStockCount("*")}; // The assumption is if * is passed return total count
    EXPECT_EQ(actual, expected);
}
```

10. Build the application and confirm that it now compiles. Back to Green for that error, but run the application and the test fails!  This is good.  GetStockCount method does not return the correct results for the test to pass, so go back to the code to fix that. Instead of returning the literal value 1 return the expected value, the literal value 0.

```cpp
#include <string>
#include <portfolio.h>

int Portfolio::GetStockCount(const std::string& symbol) const
{
    return 0;
}
```

Now we are back to Green. The test passes. As part of the TDD cycle we have gone from Red to Green and all that remains is to eliminate duplication and refactor while making sure that we remain Green.

11.  Now is the time to consider refactoring.  The goal is to consider the following:

- Change any code that is unclear or not easily readable.
- Eliminate duplication.  

In this case the test code seems clear, although adding in comments to separate the Arrange, Act and Assert sections of the test could be useful. That should have no impact on the tests, but run them anyway to make sure.

```cpp
#include <gtest/gtest.h>
#include <portfolio.h>

TEST(PortfolioTest, Given_a_new_portfolio_stock_count_is_zero)
{
    // Arrange
    int owner_id{100};
    Portfolio portfolio{owner_id};
    int expected{0};

    // Act
    int actual{portfolio.GetStockCount("*")}; // The assumption is if * is passed return total count

    // Assert
    EXPECT_EQ(actual, expected);
}
```

12. Consider the next test.  Write a new failing test that checks the `owner_id` is stored, can be retrieved and cannot be changed.

```cpp
TEST(PortfolioTest, Given_a_new_portfolio_get_owner_id_confirm_it_has_been_set)
{
    // Arrange
    int owner_id{100};
    Portfolio portfolio{owner_id};

    // Act
    auto actual{portfolio.GetOwnerId()};
    
}
```
13.  At this point there is an error because `GetOwnerId` function does not exist.  Fix the header file.
```cpp
#ifndef PORTFOLIO_H
#define PORTFOLIO_H
class Portfolio
{
public:
    Portfolio(int owner_id):owner_id_(owner_id) {}
    int GetStockCount(const std::string& symbol) const;
    int GetOwnerId() const;
private:
    int owner_id_;
};
#endif
```
14. Then fix the definition.
```cpp
#include <string>
#include <portfolio.h>

int Portfolio::GetStockCount(const std::string& symbol) const
{
    return 0;
}

int Portfolio::GetOwnerId() const
{
    return owner_id_;
}
```
15. Continue writing the test.
```cpp
#include <gtest/gtest.h>
#include <portfolio.h>

TEST(PortfolioTest, Given_a_new_portfolio_stock_count_is_zero)
{
    // Arrange
    int owner_id{100};
    Portfolio portfolio{owner_id};
    int expected{0};

    // Act
    int actual{portfolio.GetStockCount("*")}; // The assumption is if * is passed return total count

    // Assert
    EXPECT_EQ(actual, expected);
}

TEST(PortfolioTest, Given_a_new_portfolio_get_owner_id_confirm_it_has_been_set)
{
    // Arrange
    int owner_id{100};
    Portfolio portfolio{owner_id};

    // Act
    auto actual{portfolio.GetOwnerId()};

    // Assert
    EXPECT_EQ(actual, owner_id);

}
```
16.  Consider what should the next test be.  Perhaps to buy a stock and confirm that the count increases for that stock symbol and remains zero for another stock symbol.  This is actually describing two tests.  These tests will drive the creation of a better data structure to store the stocks.

```cpp
#include <gtest/gtest.h>
#include <portfolio.h>

TEST(PortfolioTest, Given_a_new_portfolio_stock_count_is_zero)
{
    // Arrange
    int owner_id{100};
    Portfolio portfolio{owner_id};
    int expected{0};

    // Act
    int actual{portfolio.GetStockCount("*")}; // The assumption is if * is passed return total count

    // Assert
    EXPECT_EQ(actual, expected);
}

TEST(PortfolioTest, Given_a_new_portfolio_get_owner_id_confirm_it_has_been_set)
{
    // Arrange
    int owner_id{100};
    Portfolio portfolio{owner_id};

    // Act
    auto actual{portfolio.GetOwnerId()};

    // Assert
    EXPECT_EQ(actual, owner_id);

}

TEST(PortfolioTest, Given_a_new_portfolio_the_purchase_of_10_IBM_should_return_stock_count_of_10_for_IBM)
{
        // Arrange
    int owner_id{100};
    Portfolio portfolio{owner_id};
    int expected{10};

    // Act
    portfolio.Buy(10, "IBM");
    int actual{portfolio.GetStockCount("IBM")}; 

    // Assert
    EXPECT_EQ(actual, expected);
}
```
17.  This test will drive the writing of the Buy function.  Declared in the header.
```cpp
#ifndef PORTFOLIO_H
#define PORTFOLIO_H
class Portfolio
{
public:
    Portfolio(int owner_id):owner_id_(owner_id) {}
    int GetStockCount(const std::string& symbol) const;
    int GetOwnerId() const;
    void Buy(const int quantity, const std::string& symbol);
private:
    int owner_id_;
};
#endif
```
18. Defined in the code file.
```cpp
#include <string>
#include <portfolio.h>

int Portfolio::GetStockCount(const std::string& symbol) const
{
    return 0;
}

int Portfolio::GetOwnerId() const
{
    return owner_id_;
}

void Portfolio::Buy(const int quantity, const std::string& symbol)
{
    // define the behavior will require some data structure
}
```
19. The current test is failing because `GetStockCount` always returns 0.  Update `GetStockCount` to return the quantity based upon  the stock symbol.  One solution to this would be to provide a `map` of key/value pairs.  The stock symbol to the quantity owned.  More changes to the header file.

```cpp
#ifndef PORTFOLIO_H
#define PORTFOLIO_H
#include <map>

class Portfolio
{
public:
    Portfolio(int owner_id):owner_id_(owner_id) {}
    int GetStockCount(const std::string& symbol) const;
    int GetOwnerId() const;
    void Buy(const int quantity, const std::string& symbol);
private:
    int owner_id_;
    std::map<const std::string, int> holdings_;
};
#endif
```
20. And definition the update in `Buy` and the lookup in `GetStockCount`.
```cpp
#include <string>
#include <portfolio.h>

int Portfolio::GetStockCount(const std::string& symbol) const
{
    if (holdings_.contains(symbol))
        return holdings_.at(symbol);
    return 0;
}

int Portfolio::GetOwnerId() const
{
    return owner_id_;
}

void Portfolio::Buy(const int quantity, const std::string& symbol)
{
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
## Review TDD Thinking

- Write a small failing test
- Get it to pass
- Add requirements to the list as discovered
