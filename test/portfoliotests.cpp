#include <gtest/gtest.h>
#include <portfolio.h>

TEST(PortfolioTest, Given_a_new_portfolio_stock_count_is_zero)
{
    // Arrange
    int owner_id{100};
    Portfolio portfolio{owner_id};
    int expected{0};

    // Act
    int actual{portfolio.GetStockCount("*")}; // The assumption is if * is passed return total count

    // Assert
    EXPECT_EQ(actual, expected);
}

TEST(PortfolioTest, Given_a_new_portfolio_get_owner_id_confirm_it_has_been_set)
{
    // Arrange
    int owner_id{100};
    Portfolio portfolio{owner_id};

    // Act
    auto actual{portfolio.GetOwnerId()};

    // Assert
    EXPECT_EQ(actual, owner_id);

}

TEST(PortfolioTest, Given_a_new_portfolio_the_purchase_of_10_IBM_should_return_stock_count_of_10_for_IBM)
{
        // Arrange
    int owner_id{100};
    Portfolio portfolio{owner_id};
    int expected{10};

    // Act
    portfolio.Buy(10, "IBM");
    int actual{portfolio.GetStockCount("IBM")}; 

    // Assert
    EXPECT_EQ(actual, expected);
}