# No Framework Test Walkthrough

## Initial Requirements List

1. Add two positive numbers together.
2. Add one positive and one negative number together.
3. Subtract two positive numbers together.
4. Subtract one positive from one negative number.
5. Subtract one negative number from one positive number.
6. . . . To be continued

## Choose a requirement to start with

There is nothing that special about any of them so lets start with requirement #1

## Write a failing test

```cpp
// TestAda.h
class TestAda
{
    public:
    void add_takes_two_numbers_and_returns_the_sum()
    {
        // Create the object under test
        Ada calculator = Ada();
    }
}
```

### Fail early and fail often

This will already fail because there is no class named Ada. TDD suggests that as soon as we have a failing test that we write the little bit of code that will let it continue.

```cpp
// Ada.h
class Ada
{

}
```

### Continue

```cpp
// TestAda.h
void add_takes_two_numbers_and_returns_the_sum()
{
    // Create the object under test
    Ada calculator = new Ada();

    int arg1 = 1;
    int arg2 = 2;
    int expected = 3;

    int actual = calculator.Add(arg1, arg2);
    // Which fails again and can be corrected by
    // defining Add as a function in the Ada type

    assert(actual == expected);
}
```
### Run the test  
Add a main() method to run the test.
```cpp
// main.cpp
#include "TestAda.h"

int main(int argc, char** argv)
{
    TestAda testSet = TestAda();
    testSet.add_takes_two_numbers_and_returns_the_sum();
}
```
As we hope the assert will fail.  

### Simplest code to pass the test

Write the simplest bit of code to get the test to pass.

```cpp
class Ada
{
    public:
    int Add(int arg1, int arg2)
    {
        return 3;
    }
}
```

### Continue

An additional test can be added that will force the reworking of the Add function to actually do a bit or arithmetic.

This can quickly get tedious and will be much easier if we add in a test library to help create and run the tests.

[END OF FILE]
