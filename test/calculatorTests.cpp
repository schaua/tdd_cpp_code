#include "../include/calculator.h"
#include <gtest/gtest.h>

// void given_two_positive_integers_when_asked_to_add_returns_their_sum()
// {
//     Calculator hp16c = Calculator {};
//     int a = 1;
//     int b = 2;
//     int expected = a + b;
//     int actual = hp16c.Add(a,b);
//     if (expected != actual) throw expected;
    
// }
TEST(CalcTest, given_two_positive_integers_when_asked_to_add_returns_their_sum)
{
    Calculator hp16c = Calculator {};
    int a = 1;
    int b = 2;
    int expected{a + b};
    EXPECT_EQ(hp16c.Add(a,b), expected);

}
TEST(CalcTest, given_1000_at_5_percent_for_1_year_interest_earned_is_50)
{
    Calculator hp16c;
    double principal{1000.0};
    double rate{5.0}; // 5%
    int time{1};
    double expectedInterest{50.0};
    double actualInterest = hp16c.CalculateInterest(principal, rate, time);
    EXPECT_EQ(actualInterest, expectedInterest);
}

TEST(CalcTest, given_1000_at_10_percent_for_1_year_interest_earned_is_100)
{
    Calculator hp16c;
    double principal{1000.0};
    double rate{10.0}; // 10%
    int time{1};
    double expectedInterest{100.0};
    double actualInterest = hp16c.CalculateInterest(principal, rate, time);
    EXPECT_EQ(actualInterest, expectedInterest);
}

TEST(CalcTest, given_1000_at_5_percent_for_2_year_interest_earned_is_50)
{
    Calculator hp16c;
    double principal{1000.0};
    double rate{5.0}; // 5%
    int time{2};
    double expectedInterest{100.0};
    double actualInterest = hp16c.CalculateInterest(principal, rate, time);
    EXPECT_EQ(actualInterest, expectedInterest);
}

TEST(CalcTest, given_0_at_5_percent_for_1_year__interest_earned_is_0)
{
    Calculator hp16c;
    double principal{0};
    double rate{5.0}; // 5%
    int time{1};
    double expectedInterest{0.0};
    double actualInterest = hp16c.CalculateInterest(principal, rate, time);
    EXPECT_EQ(actualInterest, expectedInterest);
}

TEST(CalcTest, given_1000_at_5_percent_for_0_year__interest_earned_is_0)
{
    Calculator hp16c;
    double principal{1000.0};
    double rate{5.0}; // 5%
    int time{0};
    double expectedInterest{0.0};
    double actualInterest = hp16c.CalculateInterest(principal, rate, time);
    EXPECT_EQ(actualInterest, expectedInterest);
}

// and more tests to triagulate in on the desired behavior of this function
// negative rate
// large principle
// others...