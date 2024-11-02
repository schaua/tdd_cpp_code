# Parameterized Tests Example

The previous walkthrough created a series of tests that were basically only different based on the values of the parameters being passed to the code under test.  In refactoring the tests after driving the creation of the more accurate code, we might consider the used of parameterized tests.

1. Define a struct that describes the parameters for the test case and expected return value as fields.

```cpp
#include <gtest/gtest.h>
#include "../include/calculator.h"

// Define a struct to hold the test parameters
struct InterestTestParams 
{
    double principal;
    double rate;
    int time;
    double expected;
};
```
2. Create a test fixture class that inherits from `testing::TestWithParam` and defines the type of parameter as `InterestTestParams`.  This will support instantiating multiple test cases.

```cpp
// Create a test fixture class for parameterized tests
class InterestCalculatorTest : public ::testing::TestWithParam<InterestTestParams> 
{
    protected:
    std::unique_ptr<Calculator> hp16c;

    void SetUp() override 
    {
        hp16c = std::make_unique<Calculator>();
        // std::cout << "SetUp Called" << std::endl;
    }
};
```

3. Replace the repeated tests with a new test using the `TEST_P` macro that passes the test fixture as the first parameter.

```cpp
// The test logic for parameterized tests
TEST_P(InterestCalculatorTest, CalculateInterest) 
{
    // Get the test parameters
    InterestTestParams params = GetParam();
    
    // Assert that the calculated interest matches the expected value
    EXPECT_DOUBLE_EQ(hp16c->CalculateInterest(params.principal, params.rate, params.time), params.expected);
}
```
4. Add the `INSTANTIATE_TEST_SUITE_P` macro with a name, the test fixture class and a list of values to cover the various scenarios.

```cpp

// Instantiate the parameterized test with different test cases
INSTANTIATE_TEST_SUITE_P(
    InterestTests,
    InterestCalculatorTest,
    ::testing::Values(
        InterestTestParams{1000, 5, 1, 50.0},         // Single year, 5% rate
        InterestTestParams{1000, 10, 1, 100.0},        // Single year, 10% rate
        InterestTestParams{1000, 5, 2, 100.0},         // Two years, 5% rate
        InterestTestParams{0, 5, 1, 0.0},              // Zero principal
        InterestTestParams{1000, 5, 0, 0.0},           // Zero time
        InterestTestParams{1000, -5, 1, -50.0},        // Negative rate
        InterestTestParams{1000000, 7.5, 5, 375000.0}  // Large values
    )
);
```
5. Check that all 7 tests have passed.  Uncomment the output in SetUp to demonstrate that it is called once for each parameter set.