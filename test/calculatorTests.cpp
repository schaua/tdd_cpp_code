#include "calculatorTests.h"
#include "../src/include/calculator.h"
#include <exception>
#include <format>

void given_1_and_2_when_added_returns_3()
{
    Calculator hp12c;
    int a = 1;
    int b = 2;
    int expected = a + b;
    int actual = hp12c.Add(a,b);
    if (expected != actual) 
    {        
        throw std::logic_error(std::format("Expected {} but actual {}",expected, actual));
    }
}

void given_42_and_0_when_added_returns_42()
{
        Calculator hp12c;
    int a = 42;
    int b = 0;
    int expected = a + b;
    int actual = hp12c.Add(a,b);
    if (expected != actual) 
    {        
        throw std::logic_error(std::format("Expected {} but actual {}",expected, actual));
    }
}
