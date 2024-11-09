#include <gtest/gtest.h>
#include <portfolio.h>
#include "./mockpriceservice.h"

class PortfolioTest : public testing::Test
{
protected:
        int owner_id{100};
        Portfolio portfolio{owner_id};
public:
    void SetUp() override
    {
        std::cout << "PortfolioTest::SetUp" << std::endl;
    }
};

TEST_F(PortfolioTest, Given_a_new_portfolio_stock_count_is_zero)
{
    // Arrange
    int expected{0};

    // Act
    int actual{portfolio.GetStockCount("*")}; // The assumption is if * is passed return total count

    // Assert
    EXPECT_EQ(actual, expected);
}

TEST_F(PortfolioTest, Given_a_new_portfolio_get_owner_id_confirm_it_has_been_set)
{
    // Arrange

    // Act
    auto actual{portfolio.GetOwnerId()};

    // Assert
    EXPECT_EQ(actual, owner_id);
}

TEST_F(PortfolioTest, Given_a_new_portfolio_the_purchase_of_10_IBM_should_return_stock_count_of_10_for_IBM)
{
    // Arrange
    int expected{10};

    // Act
    portfolio.Buy(10, "IBM");
    int actual{portfolio.GetStockCount("IBM")};

    // Assert
    EXPECT_EQ(actual, expected);
}

TEST_F(PortfolioTest, Given_a_new_portfolio_the_purchase_of_10_IBM_should_return_stock_count_of_0_for_GOOGL)
{
    // Arrange
    int expected{0};

    // Act
    portfolio.Buy(10, "IBM");
    int actual{portfolio.GetStockCount("GOOGL")};

    // Assert
    EXPECT_EQ(actual, expected);
}

TEST_F(PortfolioTest, Given_a_new_portfolio_the_purchase_of_10_IBM_should_return_stock_count_of_10_for_a_total)
{
    // Arrange
    int expected{10};

    // Act
    portfolio.Buy(expected, "IBM");
    int actual{portfolio.GetStockCount("*")};

    // Assert
    EXPECT_EQ(actual, expected);
}


TEST_F(PortfolioTest, Given_a_portfolio_the_purchase_of_negative_quantity_throws_an_exception)
{
    // Arrange
    // Act
    // Assert 
    EXPECT_THROW(portfolio.Buy(-1, "IBM"), std::invalid_argument);
}

TEST_F(PortfolioTest, Given_a_portfolio_with_two_stocks_calculates_the_total_value)
{
    // Arrange
    std::shared_ptr<MockPriceService> mock = std::make_shared<MockPriceService>();
    
    EXPECT_CALL(*mock, GetStockPrice("GOOGL"))
    .WillRepeatedly(testing::Return(125.0));
    
    EXPECT_CALL(*mock, GetStockPrice("IBM"))
    .WillRepeatedly(testing::Return(100.0));

    Portfolio portfolio{100, mock};
   
    portfolio.Buy(10, "IBM"); // 10 @ 100
    portfolio.Buy(20, "GOOGL"); // 20 @ 125
    double expected((10*100)+(20*125));

    // Act
    double actual = portfolio.GetStockValue("*");

    // Assert
    EXPECT_EQ(actual, expected);
}

TEST_F(PortfolioTest, Given_a_portfolio_with_two_stocks_calculates_the_individual_values)
{
    // Arrange
    std::shared_ptr<MockPriceService> mock = std::make_shared<MockPriceService>();
    
    EXPECT_CALL(*mock, GetStockPrice("GOOGL"))
    .WillOnce(testing::Return(125.0));
    
    EXPECT_CALL(*mock, GetStockPrice("IBM"))
    .WillOnce(testing::Return(100.0));

    Portfolio portfolio{100, mock};
   
    portfolio.Buy(10, "IBM"); // 10 @ 100
    portfolio.Buy(20, "GOOGL"); // 20 @ 125
    double expectedIBM(10*100);
    double expectedGOOGL(20*125);
    // Act
    double actualIBM = portfolio.GetStockValue("IBM");
    // The mock has been trainined to respond if called once
    // uncomment the following line and run the test to see
    // how the mock responds if the mocked method is called
    // twice.
    // actualIBM = portfolio.GetStockValue("IBM");
    double actualGOOGL = portfolio.GetStockValue("GOOGL");

    // Assert
    EXPECT_EQ(actualIBM, expectedIBM);
    EXPECT_EQ(actualGOOGL, expectedGOOGL);
}