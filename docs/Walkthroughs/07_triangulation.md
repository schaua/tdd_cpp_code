# Triangulation Example

Checking back on the requirements, the function for calculating interest earned should really be compounding the interest at a certain period for each of the types of accounts.  To drive the implementation of this behavior there needs to be a couple of tests written to triangulate in on the desired functionality.  Currently the `CalculateInterest` function takes , will take three parameters:

- `principal`: the initial amount of money deposited.
- `type`: the type of account (which maps to an interest rate).
- `term`: the duration in days for which the interest is calculated.  

The function returns the interest earned based on these parameters, but without any compounding of the interest. Reconsidering the design, the calculation should have an optional fourth parameter to indicate the frequency of compounding.  Start with the simplest case and progressively use the tests to refine the function using TDD.  The existing tests are fine if the frequency of compounding is the same as the term.  Add a test that compounds the interest for a 1 year CD every month.

1. Write the Next Test
Start with the simplest scenario, where the principal is $1000, the type is CD, and the time is 1 year (365 days).  Add a fourth parameter for compounding and set it to 30 days.
```cpp
// calculatorTests.cpp
TEST(CalculatorTests, Given_1000_CD_For_365_Days_Compounded_30_Days_Pays_24_93_Interest)
{
  Calculator hp12c;
  double principal{1000.00};
  std::string type{"CD"};
  int term{365};
  int compounded(30);
  double expected{51.16};
  double actual = std::trunc(hp12c.CalculateInterest(principal, type, term, compounded)*100)/100;
  EXPECT_DOUBLE_EQ(actual, expected);
}
```    
2. As expected this will cause a test failure because there is no function with that name that takes four parameters.  Provide an overloaded version of the `CalculateInteres` function that takes the extra parameter.

```cpp
// Calculator.h
#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <string>
#include <map>
class Calculator
{
    public:
    int Add(int a, int b);
    double CalculateInterest(const double principal, const std::string& type, const int term) const;
    double CalculateInterest(const double principal, const std::string& type, const int term, const int compounded) const;
    private:
    std::map<const std::string, double> rates = {
        {"CD", 0.05},
        {"Savings", 0.03},
        {"Checking", 0.01}
    };
};
#endif
```
3. Still failing so add the definition of the new function to `calculator.cpp`.  This can be the small steps such as returning the literal value 51.16 testing for.
```cpp
double Calculator::CalculateInterest(const double principal, const std::string& type, const int term, const int compounded) const
{
    return 51.16;
}
```
2. Write another test for the term of five years for a savings account compounded monthly.  This test is using triangulation to force changing to the compound interest calculation that interest paid amount is P*(1+rate/times)^(times*years) minus the original principal.  

```cpp
TEST(CalculatorTests, Given_1000_Savings_For_5_Years_Compounded_30_Days_Pays_161_79_Interest)
{
  Calculator hp12c;
  double principal{1000.00};
  std::string type{"Savings"};
  int term{365*5};
  int compounded(30);
  double expected{161.79};
  double actual = std::trunc(hp12c.CalculateInterest(principal, type, term, compounded)*100)/100;
  EXPECT_DOUBLE_EQ(actual, expected);
}
```
3. The definition of the function is driven to use the actual formula. The current implementation (return 51.16) will fail, so modify the implementation to calculate the compount interest correctly:

```cpp
// Calculator.cpp
double Calculator::CalculateInterest(const double principal, const std::string& type, const int term, const int compounded) const
{
    int times = term / compounded;
    int years = term / 365;
    double rate = rates.at(type);

    double amount = principal * std::pow((1 + rate/times),(times*years));
    return amount - principal;
    
}

```
4.  This will require adding `#include <cmath>` to the `calculator.cpp` file.

5. The tests drive the definition towards a more generalized solution to the problem.


## Summary
The process of triangulation goes from a simple solution to the test to a solutoin that accurately meets the business requirements.

- We start with a simple test and a hardcoded solution.
- We progressively add tests driving the design of the function step by step.
- Each new test forces us to refine the implementation until we arrive at a general solution that works for various scenarios.
- This TDD approach ensures that the function calculate_interest is correct, efficient, and handles a broad range of inputs as expected in financial calculations.