# Triangulation Example

Lets look at a function for  calculating interest earned. 
The function, `calculate_interest`, will take three parameters:

- `principal`: the initial amount of money deposited.
- `rate`: the annual interest rate (as a percentage).
- `time`: the duration in years for which the interest is calculated.  

The function should return the interest earned based on these parameters. Start with the simplest case and progressively refine the function using TDD.

1. Write the First Test
Start with the simplest scenario, where the principal is $1000, the rate is 5%, and the time is 1 year:
```cpp
TEST(CalcTests, given_1000_at_5_precent_for_1_year_interest_earned_is_50) 
{   
    Calculator hp16c;
    double principal{1000.0};
    double rate{5.0}; // 5%
    int time{1} // 1 year
    double expectedInterest{50.0};
    double actualInterest = hp16c.CalculateInterest(principal, rate, time);
    EXPECT_EQ(actualInterest, expectedInterest);
}
```    
We expect the interest to be $50 for this scenario (using simple interest: principal * rate * time / 100). The initial implementation could be as simple as:

```cpp
// Calculator.h
double CalculateInterest(double principal, double rate, int time);

// Calculator.cpp
double Calculator::CalculateInterest(double principal, double rate, int time)
{
    return 50.0;
}

```
This implementation hardcodes the result, but it passes the test.

2. Write a Second Test

Now, write a test for a different rate:
```cpp
TEST(CalcTests, given_1000_at_10_precent_for_1_year_interest_earned_is_100) 
{   
    Calculator hp16c;
    double principal{1000.0};
    double rate{10.0}; // 10%
    int time{1} // 1 year
    double expectedInterest{100.0};
    double actualInterest = hp16c.CalculateInterest(principal, rate, time);
    EXPECT_EQ(actualInterest, expectedInterest);
}  
```
This test forces the function to consider varying interest rates. The current implementation (return 50) will fail, so we modify the implementation to calculate the interest dynamically:

```cpp
// Calculator.cpp
double Calculator::CalculateInterest(double principal, double rate, int time)
{
    return principal * rate / 100 * time;
}

```
This new implementation works for both one-year tests with different rates.

3.  Write a Test for Multiple Years

To move towards a more generalized solution, add a test where the duration (time) is more than 1 year:
```cpp

TEST(CalcTests, given_1000_at_5_precent_for_2_year_interest_earned_is_100)
{
    Calculator hp16c;
    double principal{1000.0};
    double rate{5.0}; // 10%
    int time{2} // 2 years
    double expectedInterest{100.0};
    double actualInterest = hp16c.CalculateInterest(principal, rate, time);
    EXPECT_EQ(actualInterest, expectedInterest);
}
```
The current implementation should already pass this test because it takes time into account in the formula. This confirms that our function handles multiple years correctly.

4. Test Edge Cases (e.g., Zero Values)
Next, we test edge cases, such as when the principal or time is zero:
```cpp
TEST(CalcTests, given_0_at_5_precent_for_1_year_interest_earned_is_0)
{

}

TEST(CalcTests, 
given_1000_at_5_precent_for_0_year_interest_earned_is_0)
{

}
```
These tests ensure that when the principal or time is zero, the interest is correctly calculated as zero. Our current implementation should pass these tests as well.

5.  Add a Test for a Negative Interest Rate  

To further validate the function, we add a test for an edge case where the interest rate is negative (representing, for example, a fee or loss scenario):
```cpp
TEST(CalcTests, given_1000_at_negative_5_precent_for_1_year_interest_earned_is_negative_50)
{

}
```
This test forces the function to handle negative rates, which the current implementation should already support.

6. Test Large Values 

Finally, test the function with larger values to ensure it performs correctly:
```cpp
TEST(CalcTests, 
given_1000000_at_7_5_precent_for_5_year_interest_earned_is_375000)
{
    
}
```
The implementation should pass this test without any further modifications, demonstrating that it can handle large inputs correctly.

Summary
In this, the process of triangulation is clear:

We start with a simple test and a hardcoded solution.
We progressively add tests for different rates, durations, and edge cases, driving the design of the function step by step.
Each new test forces us to refine the implementation until we arrive at a general solution that works for various scenarios.
This TDD approach ensures that the function calculate_interest is correct, efficient, and handles a broad range of inputs as expected in financial calculations.