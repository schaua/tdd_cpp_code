# Exception Test Example

The previous walkthrough refactored the tests to use parameters.  While working on this test set the question might come up.  +_What to do about a negative term when calculating the interest_.  

Reviewing this scenario with the product owner it has been decided that the code should throw an invalid argument exception when a negative term is submitted.

1. Add a new TEST_F to the test file.  The test can jump right to the Assert that is a negative value is provided for term that it will cause an exception.

```cpp
TEST_F(CalculatorTests, Given_negative_term_then_throws_invalid_argument)
{
    EXPECT_THROW(hp12c.CalculateInterest(1000,"CD", -365, 365), std::invalid_argument);
}
```
2. Run the tests and the new one should fail.  That is as expected since there is no check on negative term values in the code.  

3. Add code to the `CalculateInterest` function so that it checks that the term argument is not less than zero.  

4. If it is less than zero, throw a `std::invalid_argument` with a suitable message.  

```cpp
// partial listing of calculator.cpp
double Calculator::CalculateInterest(const double principal, const std::string& type, const int term, const int compounded) const
{
    if (term < 0) throw std::invalid_argument("Term cannot be a negative value!");
    int times = term / compounded;
    double years = term / 365.0;
    double rate = rates.at(type);

    double amount = principal * std::pow((1 + rate/times),(times*years));
    return amount - principal;
    
}
```
5. Confirm that all of the tests now passes.  

## Summary
Using `EXPECT_THROW` or `ASSERT_THROW` will allow the test to pass if an exception is thrown, and will fail if no exception is thrown.  The exception will not interrupt the other tests or the test runner.