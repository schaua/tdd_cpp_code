#include <calculator.h>
#include <gtest/gtest.h>
#include <cmath>

struct InterestTestParams 
{
    double principal;
    std::string type;
    int term;
    int compounded;
    double expected;
};

class CalculatorParamTests : public ::testing::TestWithParam<InterestTestParams> 
{
    protected:
    Calculator hp12c;

    // The setup will be driven by the data so is no longer 
    // the same for each test.

    // SetUp and TearDwon are available if needed.
};

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


TEST_P(CalculatorParamTests, CalculateInterest)
{
  InterestTestParams params = GetParam();

  double actual = std::trunc(hp12c.CalculateInterest(params.principal, params.type, params.term, params.compounded)*100)/100;

  EXPECT_DOUBLE_EQ(actual, params.expected);
}

