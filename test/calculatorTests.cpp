#include "../include/calculator.h"
#include <gtest/gtest.h>

struct InterestTestParams 
{
    double principal;
    double rate;
    int time;
    double expected;
};

class InteresteCalculatorTest : public testing::TestWithParam<InterestTestParams>
{
    protected:
    std::unique_ptr<Calculator> hp16c;

    void SetUp() override
    {
        hp16c = std::make_unique<Calculator>();
        std::cout << "Setup Called" << std::endl;
    }
};

TEST_P(InteresteCalculatorTest, CalculateInterest)
{
    InterestTestParams params = GetParam();
    EXPECT_DOUBLE_EQ(hp16c->CalculateInterest(params.principal, params.rate, params.time), params.expected);
}

INSTANTIATE_TEST_SUITE_P(
    InterestTests,
    InteresteCalculatorTest,
    ::testing::Values(
        InterestTestParams{1000,5,1,50.0},
        InterestTestParams{1000,10,1,100.0},
        InterestTestParams{1000,5,2,100.0},
        InterestTestParams{0,5,1,0.0},
        InterestTestParams{1000,5,0,0.0},
        InterestTestParams{1000,-5,1,-50.0},
        InterestTestParams{1000000,7.5,5,375000.0}
    )
);