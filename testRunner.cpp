#include <iostream>
#include "calculatorTests h"

int main(int argc, char** argv)
{
    std::string msg;
    try
    {
        given_two_positive_integers_when_asked_to_add_returns_their_sum();
        msg = "Tests successful";
    }
    catch(...)
    {
        msg = "Tests failed";
    }
    std::cout << msg << std::endl;    
    return 0;
}