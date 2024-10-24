# Exception Test Example

The previous walkthrough refactored the tests to use parameters.  While working on this the question came up as to what to do about a negative time in calculating the interest.  

Reviewing this with the product owner it has been decided that the code should throw an invalid argument exception when that scenario arises.

1. Add a new TEST_F to the test code.  There is really no need for the Arrange section of the test, and the Act and Assert are combined since we what the action to generate an exception.

```cpp
TEST_F(InterestCalculatorTest, NegativeTimeThrowsException) 
{
    EXPECT_THROW(hp16c->CalculateInterest(1000, 5, -1), std::invalid_argument);
}
```
2. Run the test and it should fail.   
3. Add code to the function under test to check that the time argument is not less than zero.
4. If it is less than zero, throw a std::invalid_argument which requires an include for `<stdexcept>` be added to `calculator.cpp`.
```cpp
#include <stdexcept>

// ...

double Calculator::CalculateInterest(double principal, double rate, int time)
{
    // Negative time is nonsense
    if (time < 0)
        throw std::invalid_argument(
            "Time cannot be a negative value"
    );

    return principal * rate / 100 * time;
}
```
5. Confirm that the test now passes.  