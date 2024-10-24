# Lab

## Fixtures
We can continue to refactor the tests by noting that the duplicate creation of an instance of Soundex could be moved out to a shared fixture.  The idea of a fixture is common to many testing frameworks.  It provides a place to code setup and tear down behavior that should take place before each and every test or after each and every test.   
To add the fixture two changes are needed.  

1. Define a new class that inherits from the `Test` class in the `testing` namespace and modify the `TEST` macros to instead be `TEST_F`.  We can name the class the same as the test suite name that we have been using to reduce the amount of code that needs to change.  Add the new class at the top of the `soundextest.cpp` file.

```cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using testing::StartsWith;
using testing::Eq;

class SoundexTest : public testing::Test
{
public:
    std::unique_ptr<Soundex> soundex;

    void SetUp() override
    {
        soundex = std::make_unique<Soundex>();
    }

    void TearDown() override
    {
        // smart point takes care of everythin
        // so far
    }
}
``` 
2. Update the TEST macro to TEST_F for the two tests and remove the creation of the `soundex` resource from both tests.  Change the method call to use pointer dereferencing.
```cpp

TEST_F(SoundexTest, RetainsSoleLetterOfOneLetterWord){
    // Arrange
    std::string oneLetterWord{"A"};
    // Act
    auto encoded = soundex->encode(oneLetterWord);
    // Assert
    ASSERT_THAT(oneLetterWord.length(), Eq(1));
    ASSERT_THAT(encoded, StartsWith(oneLetterWord));
}

TEST_F(SoundexTest, PadsWithZerosToEnsureThreeDigitOutput)
{
    // Arrange
    std::string oneLetterWord{"I"};
    std::string expected = oneLetterWord + "000";
    // Act
    auto encoded = soundex->encode(oneLetterWord);
    // Assert
    ASSERT_EQ(encoded, expected);
}
```
3. Compile and run the tests to make sure that we are still Green.

## Review TDD Thinking 
* Write a small failing test
* Get it to pass
* **Review and clean up the design**
* Ensure all the tests still pass

