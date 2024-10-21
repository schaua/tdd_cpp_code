#include "../include/calculator.h"
#include <gtest/gtest.h>


class CalcTest : public testing::Test
{
    protected:

    std::unique_ptr<Calculator> hp16c;

    void SetUp() override
    {
        hp16c = std::make_unique<Calculator>();
        std::cout << "SetUp called" << std::endl;
    }

    void TearDown() override
    {
        // unique_ptr cleans up after itself
        std::cout << "TearDown called" << std::endl;
    }
};

TEST_F(CalcTest, given_two_positive_integers_when_asked_to_add_returns_their_sum)
{
    int a = 1;
    int b = 2;
    int expected{a + b};
    EXPECT_EQ(hp16c->Add(a,b), expected);

}

TEST_F(CalcTest, given_two_negative_integers_when_asked_to_add_returns_their_sum)
{
    int a = -1;
    int b = -2;
    int expected{a + b};
    EXPECT_EQ(hp16c->Add(a,b), expected);

}