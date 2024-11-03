# TDD Concepts Demo
This walkthrough is setting up a project that will be built upon for the subsequent walkthroughs.  The application represents a financial calculator application.

1. The first step is to develop an _initial_ list of requirements for a calculator application.  This list does not need to be complete as TDD will help generate ideas for new requirements as the process moves along.

2. Review the list so far and pick the _easiest_ requirements to write a test for as a starting point.  _Easy_ is defined as a behavior in the application for which a test can be written to describe and the code written to make it pass in 10 minutes or less.  If the first test turns out to be too complicated it is within the rules of TDD to throw it away and choose something else.

3. The work will be in the project directory named `tdd_app`.  Open the directory in VS Code as the folder either from the menu `File | Open Folder...` or from the command line.
```cmd
cd tdd_app
code .
``` 
4. The CalcProject will replace FirstApp.  Edit the CMake configuration file,  `CMakeLists.txt`, in the project directory.  Change the `PROJNAME` variable to be `CalcProject` and add a `file` entry to look for all of the `.cpp` files in the folder as the source for the executable.  

```yaml
cmake_minimum_required(VERSION 3.10...3.28)
set (PROJNAME CalcProject)
project(${PROJNAME} VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
file(GLOB SOURCES "*.cpp")
add_executable(${PROJNAME} ${SOURCES})
```
This will use a variable, `SOURCES`, to find all of the files that have a cpp file extension to build the executable.  The name of the executable is still assigned using the variable name `PROJNAME` which has been changed.

5. Rename the existing `runner.cpp` file to `testRunner.cpp`.  Delete the content of the  `main` function and replace it with the following starting code.
```cpp
// testRunner.cpp
#include <iostream>

int main(int argc, char** argv)
{
    return 0;
}
```
6. In `main` add try/catch blocks and in the try block add the following line to call the first test function.  The test function does not yet exit.  This code will force us to write the test function.

```cpp
// testRunner.cpp
#include <iostream>

int main(int argc, char** argv)
{
    try
    {
        given_1_and_2_when_added_returns_3();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
```

7. The test function should have a descriptive name .  This one uses the  _given_preconditions_when_stateundertest_then_expectedbehavior_ pattern common in Business Driven Development (BDD).  

8. Above the try/catch declare a local `std::string` variable named `msg`.  In the try block after calling the test function, set `msg` to indicate success.
```cpp
std::string msg;
try
{
    given_1_and_2_when_added_returns_3();
    msg = "Tests are successful.";
}
```
9. In the catch block after the `std::cerr` line, set to indicate failure.
```cpp
catch(const std::exception& e)
{
    std::cerr << e.what() << '\n';
    msg = "Tests failed.";
}
```
10.  After the try/catch and just before the return statement, output `msg` to the console.
```cpp
std::cout << msg << std::endl;
```
11. There is currently an error in the application.  The  `given_1_and_2_when_added_returns_3` function is not defined.  Write the missing test function.  For this demonstration declare the test in a new header file named `calculatorTests.h` in the main project folder.  Tests methods return nothing and take no arguments.
```cpp
// calculatorTests.h
#ifndef CALCULATORTESTS_H
#define CALCULATORTESTS_H
void given_1_and_2_when_added_returns_3();
#endif
```
12. Define the test function behavior in a new source file, also in the project folder,  named `calculatorTests.cpp` that includes the header file.
```cpp
// calculatorTests.cpp
#include "calculatorTests.h"
void given_1_and_2_when_added_returns_3()
{

}
```
13.  Edit `testRunner.cpp` and add an include statement to make the test function available.
```cpp
include "calculatorTests.h"
```
14.  Build and run the application and confirm that it outputs `Tests successful` in the terminal.
- If there are CMake errors it may be necessary to delete the cache and reconfigure the `build` files.  From the Command Palette choose `CMake: Delete Cache and Reconfigure`.  Another option is close VS Code and delete the `build` directory from the project.  

15. Now edit calculatorTests.cpp to described the behavior of the first test that meets our chosen application requirement.   In this case create an instance of the Calculator, which doesn't exist yet.
```cpp
// calculatorTests.cpp
void given_1_and_2_when_added_returns_3()
{
    Calculator hp12c;
}
```
16. This immediately causes an error in the test.  There is no Calculator class.  This requires adding the Calculator class.  Add a `calculator.h` file to declare the class.
```cpp
// calculator.h
#ifndef CALCULATOR_H
#define CALCULATOR_H
class Calculator
{

};
#endif
```
17.  Update `calculatorTests.cpp` to include the new `calculator.h` file and the error will be eliminated.
```cpp
#include "calculator.h"

void given_1_and_2_when_added_returns_3()
{
    Calculator hp12c;
}
```

18. Now call the Calculator function to add two numbers in our test function.
```cpp
// calculatorTests.cpp
#include "calculatorTests.h"
#include "calculator.h"

void given_1_and_2_when_added_returns_3()
{
    Calculator hp12c;
    int a = 1;
    int b = 2;
    int expected = a + b;
    int actual = hp12c.Add(a,b);
}
```
12. This causes the test to fail because there is not function named `Add` in the `Calculator` class.  Declare a new Add function that takes two integer arguments and returns an integer.
```cpp
// calculator.h
class Calculator
{
    public:
    int Add(int a, int b);
};
```
13.  Now the test will fail to compile because there is no definition of the `Add` method.  Add the definition to a new `calculator.cpp` file.
```cpp
// calculator.cpp
    #include "calculator.h"
    int Calculator::Add(int a, int b) { return 0; }
```
13. Run the test and it passes!  That is because there is no actual test of the result compared to an expected value.  Add the following line to the test to compare the results and throw and exception if there is not a match.
```cpp
if (expected != actual) 
{        
    throw std::logic_error(std::format("Expected {} but actual {}",expected, actual));
}
```
14. This will require the addition of some header files to the top of `calculatorTests.cpp`.  The final result should look like this:
```cpp
#include "calculatorTests.h"
#include "calculator.h"
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
```
15.  Confirm the test fails.  The output to the terminal should look like:
```cmd
C:\projects\tdd_app\build>"C:/projects/tdd_app/build/CalcProject.exe"
Expected 3 but actual 0
Tests failed.
```

16. Correct the implementation of the `Add` function so that the test will pass.  The _least_ amount of code to get the test to pass is to return 3.
```cpp
// calculator.cpp
    int Calculator::Add(int a, int b) { return 3; }
```
17. Confirm the test passes.
18.  Follow this pattern to add a second test to the try block for adding a number and zero which should return the first number.
```cpp
try
{
    given_1_and_2_when_added_returns_3();
    given_42_and_0_when_added_returns_42();
    msg = "Tests are successful.";
}
```
19. Walk through the test failures to first declare and then define the new test function by adding it to the `calculatorTests.h` file.
```cpp
#ifndef CALCULATORTESTS_H
#define CALCULATORTESTS_H
void given_1_and_2_when_added_returns_3();
void given_42_and_0_when_added_returns_42();
#endif
```
20. Define the test in the `calculatorTests.cpp` file.
```cpp
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
```
21. The test should now run, but fail since `Add` always returns `3`.  Update the definition of `Add` to return the sum of the two arguments.
```cpp
int Calculator::Add(int a, int b) 
{
    return a+b;
}
```
22. Both test should now pass.

## Summary
1. Does this exercise suggest and additional requirements that we should add to the backlog list?
2. Is there any repetitive code that might require refactoring?
3. What would be the next likely test to write?

This walkthrough illustrates the ideas behind TDD without the introduction of any specific testing library.  The completed code for this walkthrough is in branch `w02`.
