# Test Fixture

## Add the test fixture 
1. Update `calculatorTests.cpp` to add a new Google Test fixture class. This class should inherit from the `Test` class in the google test library.  It is in the `testing` namespace The fixture uses the resource name with a 'Test' suffix by convention.

2. Use the `TEST_F` macro for each test that needs the shared setup and teardown. The `TEST_F` macro takes the test fixture class name as the first argument and the test name as the second argument. 

```cpp
// calculatorTests.cpp
#include "../include/calculator.h"
#include <gtest/gtest.h>

class CalcTest : testing::Test
{
    std::unique_ptr<Calculator> hp16c;

    void SetUp() override
    {
        hp16c = std::make_unique<Calculator>();
        std::cout << "SetUp called" << std::endl;
    }

    void TearDown() override
    {
        // unique_ptr automatically cleans up after itself
        std::cout << "TearDown called" << std::endl;
    }
};

TEST_F(CalcTest, given_two_positive_integers_when_asked_to_add_returns_their_sum) {
    int a = 1;
    int b = 2;
    int expected{a+b};

    EXPECT_EQ(hp16c->Add(a,b), expected);
}

TEST_F(CalcTest, given_two_negative_integers_when_asked_to_add_returns_their_sum) {
    int a = -1;
    int b = -2;
    int expected{a+b};

    EXPECT_EQ(hp16c->Add(a,b), expected);
}

```
## Build and Run Tests  

1. Now you can build your project using the CMake extension.

2. To run the tests click the triangle in the bottom status bar of VS Code.

3. The output, including the `std::cout` messages,  should appear in the terminal window.  
