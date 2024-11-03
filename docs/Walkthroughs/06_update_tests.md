# Adding Additional Tests

The next feature of interest is the interest rate calculations.  When given a principal amount, and account type and a term the function should return the total interest earned over the term, using an interest rate that is associated with each account type of either `CD`, `Savings`, `Checking`.  The interest rates will eventually be obtained dynamically, but for now `CD` pays 5%, `Savings` pays 3% and `Checking` pays 1%.

> The remaining walkthrough use GoogleTest.  Similar steps can be used if Catch2 is preferred.  See the documentation on the Catch2 macros for more information.
[Catch2 Reference](https://github.com/catchorg/Catch2/blob/devel/docs/Readme.md#top).

1. Add a new test to `calculatorTests.cpp` for calculating the interest on principal of 1000.00 for a CD with a term of 182 days.
```cpp
TEST(CalculatorTests, Given_1000_CD_For_182_Days_Pays_24_93_Interest)
{

}
```
2. All three tests will pass at this point, because this last test is not actually asserting anything.  Add in some actual work for the test, starting with a call to the Calculator `CalculateInterest` function. (Which doesn't yet exist)
```cpp
TEST(CalculatorTests, Given_1000_CD_For_182_Days_Pays_24_93_Interest)
{
  Calculator hp12c;
  double principal{1000.00};
  std::string type{"CD"};
  int term{182};
  double expected{ 24.93};
  double actual = hp12c.CalculateInterest(principal, type, term);
  EXPECT_DOUBLE_EQ(actual, expected);

}
```
3.  A test error because there is no `CalculateInterest` function so add it to the `Calculator`.  The arguments passed in will not be modified, so make them `const`.  The function also does not change the state of the object so make it a `const` function as well.  The `std::string` requires adding the `#include <string>` to the header file.
```cpp
// calculator.h
#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <string>
class Calculator
{
    public:
    int Add(int a, int b);
    double CalculateInterest(const double principal, const std::string& type, const int term) const;
};
#endif
```
4. And define the behavior to get the test to pass.
```cpp
// calculator.cpp
double Calculator::CalculateInterest(const double principal, const std::string& type, const int term) const
{
    return 24.93;
}

```
5. While this is the minimum code to get the test to pass, it is a bit obvious that it is not very useful.  Refactor the code to actually calculate the interest paid.
```cpp

TEST(CalculatorTests, Given_1000_CD_For_182_Days_Pays_24_93_Interest)
{
  Calculator hp12c;
  double principal{1000.00};
  std::string type{"CD"};
  int term{182};
  double expected{24.93};
  double actual = hp12c.CalculateInterest(principal, type, term);
  EXPECT_DOUBLE_EQ(actual, expected);
}
```
6.  Now the test fails with the following output:
```
Expected equality of these values:
  actual
    Which is: 24.931506849315067
  expected
    Which is: 24.9315
```
7. Fix the test to only compare two decimal places.
```cpp
TEST(CalculatorTests, Given_1000_CD_For_182_Days_Pays_24_93_Interest)
{
  Calculator hp12c;
  double principal{1000.00};
  std::string type{"CD"};
  int term{182};
  double expected{24.93};
  double actual = std::trunc(hp12c.CalculateInterest(principal, type, term)*100)/100;
  EXPECT_DOUBLE_EQ(actual, expected);
}
```
8. The `std::trunc` function requires adding `#include <cmath>` at the top of the file.

9. The test should now pass.  So it is time to consider what refactoring could be added.  For example we could make this more flexible for future account types by mapping the type to the rate in a map.  Add the `std::map` to `calculator.h`.
```cpp
#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <string>
#include <map>
class Calculator
{
    public:
    int Add(int a, int b);
    double CalculateInterest(const double principal, const std::string& type, const int term) const;
    private:
    std::map<const std::string, double> rates{
      {"CD", 0.05},
      {"Savings", 0.03},
      {"Checking", 0.01}
    };
};
#endif
```
10. Use the new `rates` map in the `CalculateInterest` to simplify the function.  

```cpp
double Calculator::CalculateInterest(const double principal, const std::string& type, const int term) const
{
    double rate = rates.at(type);
    return principal * rate * term / 365;
}

```
11.  Confirm that all of the tests still pass.

12.  Adding another test with a different type will add confidence that everything is working correctly.

```cpp
TEST(CalculatorTests, Given_1000_Savings_For_365_Days_Pays_30_Interest)
{
  Calculator hp12c;
  double principal{1000.00};
  std::string type{"Savings"};
  int term{365};
  double expected{30.0};
  double actual = std::trunc(hp12c.CalculateInterest(principal, type, term)*100)/100;
  EXPECT_DOUBLE_EQ(actual, expected);
}
```
13. Adding a third test for `Checking` will complete this walkthrough.
```cpp
TEST(CalculatorTests, Given_1000_Checking_For_365_Days_Pays_10_Interest)
{
  Calculator hp12c;
  double principal{1000.00};
  std::string type{"Checking"};
  int term{365};
  double expected{10.0};
  double actual = std::trunc(hp12c.CalculateInterest(principal, type, term)*100)/100;
  EXPECT_DOUBLE_EQ(actual, expected);
}
```

## Summary
Notice that the test is rounding down the result to get the level of accuracy desired, and that it is not the actual `CalculateInterest` function that applies some potentially invalid assumption as to accuracy.