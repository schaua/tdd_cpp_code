#include <iostream>
#include "./test/calculatorTests.h"

int main(int argc, char** argv)
{
    std::string msg;
    try
    {
        given_1_and_2_when_added_returns_3();
        given_42_and_0_when_added_returns_42();
        msg = "Tests are successful.";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        msg = "Tests failed.";
    }
    std::cout << msg << std::endl;
    return 0;
}