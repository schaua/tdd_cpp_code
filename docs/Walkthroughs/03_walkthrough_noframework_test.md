# TDD Concepts Demo
1. Develop an initial list of requirements for a calculator application.
2. Review the list so far and pick the "easiest" requirements to write a test for as a starting point.
3. Create a new project directory named `CalcProject` and open the directory in VS Code.
    ```cmd
    mkdir CalcProject
    cd CalcProject
    code .
    ``` 
4. Create a new text file named `CMakeLists.txt` in the project directory.  
```yaml
cmake_minimum_required(VERSION 3.14...3.28)
set(PROJNAME CalcProject)
project(${PROJNAME})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB MY_CODE "*.cpp)

add_executable(${PROJNAME} ${MYCODE})
```
5. Create a new file named `testRunner.cpp` and write `main` as the starting point.
```cpp
// testRunner.cpp
int main(int argc, char** argv)
{

}
```
6. In `main` call the first test method.  It can be named something descriptive.  Perhaps in the pattern of Business Driven Development (i.e.  *given_preconditions_when_stateundertest_then_expectedbehavior*).  For this document assume the first test is going to be `given_two_positive_integers_when_asked_to_add_returns_their_sum`.  Update `main` to call this test.
```cpp
// testRunner.cpp
#include <iostream>
#include "calculatorTests.h"

int main(int argc, char** argv)
{
    std::string msg;
    try
    {
        given_two_positive_integers_when_asked_to_add_returns_their_sum();
        msg =  "Tests successful";
    }
    catch(...)
    {
        msg = "Tests failed";
    }
    std::cout << msg << std::endl;
    return 0;
}
```
7. Next we need to actually write the test.  For our simple demonstration declare the test a header file named `calculatorTests.h` and define the test in `calculatorTests.cpp`.
```cpp
// calculatorTests.h
#ifndef CALCULATORTESTS_H
#define CALCULATORTESTS_H
void given_two_positive_integers_when_asked_to_add_returns_their_sum();
#endif

// calculatorTests.cpp
#include "calculatorTests.h"
void given_two_positive_integers_when_asked_to_add_returns_their_sum()
{

}
```
8.  Run the application and confirm that it outputs `Tests successful` in the terminal.
9. Now we can start editing calculatorTests.h to described the first requirement.
```cpp
// calculatorTests.h
void given_two_positive_integers_when_asked_to_add_returns_their_sum()
{
    Calculator hp16c;
}
```
10. This requires that we add the Calculator class.
```cpp
// calculator.h
#ifndef CALCULATOR_H
#define CALCULATOR_H
class Calculator
{

};
#endif
```
11. Now actually ask the Calculator to do something in our test.
```cpp
// calculatorTests.h
#include "calculator.h"

void given_two_positive_integers_when_asked_to_add_returns_their_sum()
{
    Calculator hp16c;
    int a = 1;
    int b = 2;
    int expected = a + b;
    int actual = hp16c.Add(a,b);
    if (expected != actual) throw expected;
}
```
12. This forces the definition of the Add method that takes two integers and returns an integer.
```cpp
// calculator.h
class Calculator
{
    public:
    int Add(int a, int b);
};

// calculator.cpp
    #include "calculator.h"
    int Calculator::Add(int a, int b) { return 0; }
```
13. Confirm the test fails and then correct the implementation to succeed.  The least amount of code to get the test to pass would return 3, but we can jump a step here and return the sum of a and b.
```cpp
// calculator.cpp
    int Calculator::Add(int a, int b) { return a+b; }
```
14. Confirm the test passes.
15. Does this exercise suggest and additional requirements that we should add to the backlog list?
16. Is there any repetitive code that might require refactoring?
17. What would be the next likely test to write?
