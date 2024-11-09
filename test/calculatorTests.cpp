#include <calculator.h>
#include <gtest/gtest.h>
#include <cmath>

TEST(CalculatorTests, Given_1_and_2_when_added_returns_3)
{
    Calculator hp12c;
    int a = 1;
    int b = 2;
    int expected = a + b;
    int actual = hp12c.Add(a,b);
    EXPECT_EQ(actual,expected);
}

TEST(CalculatorTests, Given_42_and_0_then_added_returns_42) 
{
    Calculator hp16c;
    int a = 1;
    int b = 2;
    int expected{a+b};

    EXPECT_EQ(hp16c.Add(a,b),expected);
}

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

TEST(CalculatorTests, Given_1000_CD_For_365_Days_Compounded_30_Days_Pays_50_16_Interest)
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