#include <calculator.h>
#include <gtest/gtest.h>
#include <cmath>

class CalculatorTests : public testing::Test
{
  protected:
    Calculator hp12c;
    double principal;
    int term;
    std::string type;
  public:
    void SetUp() override
    {
        // any additional resources can be initialized here
        principal = 1000.0;
        term = 365;
        type = "CD";
        std::cout << "SetUp called" << std::endl;
    }

    void TearDown() override
    {
        // cleans up goes here
        std::cout << "TearDown called" << std::endl;
    }
};

TEST_F(CalculatorTests, Given_1_and_2_when_added_returns_3)
{
    int a = 1;
    int b = 2;
    int expected = a + b;
    int actual = hp12c.Add(a,b);
    EXPECT_EQ(actual,expected);
}

TEST_F(CalculatorTests, Given_42_and_0_then_added_returns_42) 
{
    int a = 1;
    int b = 2;
    int expected{a+b};

    EXPECT_EQ(hp12c.Add(a,b),expected);
}

TEST_F(CalculatorTests, Given_1000_CD_For_182_Days_Pays_24_93_Interest)
{
  int term{182};
  double expected{24.93};
  double actual = std::trunc(hp12c.CalculateInterest(principal, type, term)*100)/100;
  EXPECT_DOUBLE_EQ(actual, expected);
}

TEST_F(CalculatorTests, Given_1000_Savings_For_365_Days_Pays_30_Interest)
{
  std::string type{"Savings"};
  double expected{30.0};
  double actual = std::trunc(hp12c.CalculateInterest(principal, type, term)*100)/100;
  EXPECT_DOUBLE_EQ(actual, expected);
}

TEST_F(CalculatorTests, Given_1000_Checking_For_365_Days_Pays_10_Interest)
{
  std::string type{"Checking"};
  double expected{10.0};
  double actual = std::trunc(hp12c.CalculateInterest(principal, type, term)*100)/100;
  EXPECT_DOUBLE_EQ(actual, expected);
}

TEST_F(CalculatorTests, Given_1000_CD_For_365_Days_Compounded_30_Days_Pays_50_16_Interest)
{
  int compounded(30);
  double expected{51.16};
  double actual = std::trunc(hp12c.CalculateInterest(principal, type, term, compounded)*100)/100;
  EXPECT_DOUBLE_EQ(actual, expected);
}

TEST_F(CalculatorTests, Given_1000_Savings_For_5_Years_Compounded_30_Days_Pays_161_79_Interest)
{
  std::string type{"Savings"};
  int term{365*5};
  int compounded(30);
  double expected{161.79};
  double actual = std::trunc(hp12c.CalculateInterest(principal, type, term, compounded)*100)/100;
  EXPECT_DOUBLE_EQ(actual, expected);
}