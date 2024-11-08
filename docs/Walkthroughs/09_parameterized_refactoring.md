# Parameterized Tests Example

The previous walkthrough created a series of tests that were the only difference is  the values of the parameters being passed to the code under test and the expected result.  This could be consolidated during refactoring of the tests with the use of parameterized tests.  
A data structure that describes the parameter types and names as well as the expected result type and name provides the starting point.  The fixture class should now publicly inherit from `testing::TestWithParam`.  GoogleTest uses another macro, `TEST_P` to attach the parameter fixture class to a given test.  Finally the `INSTANTIATE_TEST_SUITE_P` macro creates and instance of the data structure for each test run.

1. Define a struct that describes the parameters for the test case and expected return value as fields at the top of the test file, just below the includes.

```cpp
// Define a struct to hold the test parameters
struct InterestTestParams 
{
    double principal;
    std::string type;
    int term;
    int compounded;
    double expected;
};
```
2. Create a new test fixture class that inherits from `testing::TestWithParam`.  This needs to identify the data structure type for the parameters, `InterestTestParams`.  This will support instantiating multiple test cases.

```cpp
// Create a test fixture class for parameterized tests
class CalculatorParamTests : public ::testing::TestWithParam<InterestTestParams> 
{
    protected:
    Calculator hp12c;

    // The setup will be driven by the data so is no longer 
    // the same for each test.

    // SetUp and TearDwon are available if needed.
};
```

3. Add the `INSTANTIATE_TEST_SUITE_P` macro with a name, the test fixture class and a list of values to cover the existing scenarios.  The first argument is the test suite name, the second is the fixture class name and the third argument is the values of the data structure to be used for the tests.

```cpp

// Instantiate the parameterized test with different test cases
INSTANTIATE_TEST_SUITE_P(
    InterestTests,
    CalculatorParamTests,
    ::testing::Values(
        InterestTestParams{1000, "CD", 182, 182, 24.93},        
        InterestTestParams{1000, "Savings", 365, 365, 30.0},     
        InterestTestParams{1000, "Checking", 365, 365, 10.0},         
        InterestTestParams{1000, "CD", 365, 30, 51.16},              
        InterestTestParams{1000, "Savings", 365*5, 30, 161.79}
    )
);
```
4. The existing tests of the CalculateInterest function can be reduced to one testthat does uses the compounded parameter.   Using the `TEST_P` macro that passes the test fixture as the first parameter, refactor the interest tests down from five to one test.  In the test use `GetParam()` to retrieve the current data structure values for each test run and store them in a variable named `params`.

```cpp
// The 
TEST_P(CalculatorParamTests, CalculateInterest)
{
  InterestTestParams params = GetParam();

  double actual = std::trunc(hp12c.CalculateInterest(params.principal, params.type, params.term, params.compounded)*100)/100;

  EXPECT_DOUBLE_EQ(actual, params.expected);
}
```
5. Check that all 7 tests have passed.  It should be that the first test fails.  This has uncovered a bug in the code if the term and the compounded values are less than a year.  Changes to the implementation are an natural result of more testing.  In this case it appears that if the term is less than on year there are some rounding issues in the current implementation.  The first idea is that integer division for the years is causing a problem.  Update the `Calculator::CalculateInterest` to ensure double division, without changing the types of the arguments passed in.
```cpp

double Calculator::CalculateInterest(const double principal, const std::string& type, const int term, const int compounded) const
{
    double times = term / compounded;
    double years = term / 365.0;
    double rate = rates.at(type);

    double amount = principal * std::pow((1 + rate/times),(times*years));
    return amount - principal;
    
}
```
6. One test is still failing, but when the actual vs expected is compared, it looks like an issue with the expected interest being off by a little.  Manual calculation of that scenario gives a result of 24.62, so changes to the test are needed.
```cpp
INSTANTIATE_TEST_SUITE_P(
    InterestTests,
    CalculatorParamTests,
    ::testing::Values(
        InterestTestParams{1000, "CD", 182, 182, 24.62},        
        InterestTestParams{1000, "Savings", 365, 365, 30.0},     
        InterestTestParams{1000, "Checking", 365, 365, 10.0},         
        InterestTestParams{1000, "CD", 365, 30, 51.16},              
        InterestTestParams{1000, "Savings", 365*5, 30, 161.79}
    )
);
```
7.  All tests should now pass.

## Summary
This walksthrough shows how tests can cause updates to the code, as well as to the tests themselves when new information is uncovered.  
- What is the confidence level in the interest calculations>?
- Are additional tests needed to improve the code?