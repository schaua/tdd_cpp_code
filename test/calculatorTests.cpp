#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/calculator.h"
#include "interestrateservice.h"

using testing::Return;

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

TEST_F(InteresteCalculatorTest, NegativeTimeThrowsException)
{
    EXPECT_THROW(hp16c->CalculateInterest(1000,5,-1), std::invalid_argument);
}

TEST_F(InteresteCalculatorTest, CalculateInterestAtSavingsRateOf5)
{
    // Arrange
    std::string accountType{"Savings"};
    std::string bankURL{"https://mybank.com"};
    double principal{1000.0};
    double rate{}; // to be obtained from mock service
    int time{1};
    double expected{50.0};
    auto mockService = std::make_unique<InterestRateService>(bankURL);
    EXPECT_CALL(*mockService, GetCurrentRate(accountType))
    .WillOnce(Return(5.0));

    // Act
    rate = mockService->GetCurrentRate(accountType);

    // Assert
    EXPECT_DOUBLE_EQ(hp16c->CalculateInterest(principal, rate, time), expected);
}

TEST_F(InteresteCalculatorTest, CalculateInterestAtCheckingRateOf2)
{
        // Arrange
    std::string accountType{"Checking"};
    std::string bankURL{"https://mybank.com"};
    double principal{1000.0};
    double rate{}; // to be obtained from mock service
    int time{1};
    double expected{20.0};
    auto mockService = std::make_unique<InterestRateService>(bankURL);
    EXPECT_CALL(*mockService, GetCurrentRate(accountType))
    .Times(1) // try changing this to 3
    .WillOnce(Return(2.0));

    // Act
    rate = mockService->GetCurrentRate(accountType);

    // Assert
    EXPECT_DOUBLE_EQ(hp16c->CalculateInterest(principal, rate, time), expected);
}