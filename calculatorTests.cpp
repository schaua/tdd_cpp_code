#include "./calculator.h"

void given_two_positive_integers_when_asked_to_add_returns_their_sum()
{
    Calculator hp16c = Calculator {};
    int a = 1;
    int b = 2;
    int expected = a + b;
    int actual = hp16c.Add(a,b);
    if (expected != actual) throw expected;
    
}