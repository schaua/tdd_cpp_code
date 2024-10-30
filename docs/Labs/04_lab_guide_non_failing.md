# Non-failing tests

This exercise steps through on approach to dealing with a non-failing test.

1. Let's take a look at the part of the Buy requirements that says if buying an already existing stock the quantity for that particular stock is incremented by the purchased quantity. A test might look like the following.

```cpp
TEST_F(PortfolioTest, AddQuantityToExistingStockAfterBuy)
{
    const int purchaseQuantity{10};
    const std::string symbol{"IBM"};
    const int startingQuantity = portfolio->GetStockCount(symbol);
    const int expectedQuantity{startingQuantity+purchaseQuantity);}

    portfolio->Buy(purchaseQuantity,symbol);
    ASSERT_EQ(portfolio->GetStockCount(symbol), expectedQuantity);
}
```

This test passed immediately. Perhaps it is not necessary. But the test proves that we satisfy a particular portion of the requirement, and it is possible that in the future we may break that and needs this test to catch it for us. So let's leave it in place and move on to the next rule.

> Generally the TDD principle is to write a failing test. The fact that this passed immediately might indicate that we are not taking small enough steps, and should consider our future moves carefully. If this becomes a common occurrence we should look at taking smaller incremental steps.

## What is next?

What tests are we missing? What other scenarios might we can to consider? Where to go from here? All good questions, but for now we can look at the Soundex class that we have created with some confidence that is meeting all of these requirements, because we have the tests to prove it.
