#include <calculator.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Given 1 and 2 when added returns 3", "[Caclulator]")
{
    Calculator hp12c;
    int a = 1;
    int b = 2;
    int expected = a + b;
    int actual = hp12c.Add(a,b);
    REQUIRE(actual == expected);
}

TEST_CASE("Given 42 and 0 then added returns 42", "[Calculator]") {
    Calculator hp16c;
    int a = 1;
    int b = 2;
    int expected{a+b};

    REQUIRE(hp16c.Add(a,b)==expected);
}