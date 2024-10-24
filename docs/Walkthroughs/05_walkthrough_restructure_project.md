# Walkthrough Separating Source and Tests
## Demonstration
1. Create a directory structure to separate the tests from the code under test.  Rename the `calculatorTest.h` to `calculatorTest.cpp`.
```
project/
|   |- CMakeLists.txt
|   |- testRunner.cpp
|- include/
|   |- calculator.h
|   |- calculatorTests.h
|- src/
|   |- calculator.cpp
|- test/
|   |- calculatorTests.cpp
|- build/
```
2. Edit the CMakeLists.txt to create a target to the src as a library and a target to the test as an executable.  
```cmake
cmake_minimum_required(VERSION 3.15...3.28)

set(PROJNAME CalcProject)
set(CODE_UNDER_TEST CalcCode)
set(TEST_SPECS CalcTests)
project(${PROJNAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE MY_CODE "src/*.cpp")
file(GLOB_RECURSE MY_TESTS "test/*.cpp")

# define a new target named code_under_test to make the code under test
# available to the test runner
add_library(${CODE_UNDER_TEST} STATIC ${MY_CODE})
target_include_directories(${CODE_UNDER_TEST} PUBLIC include)

add_library(${TEST_SPECS} STATIC ${MY_TESTS})
target_include_directories(${TEST_SPECS} PUBLIC include)
target_link_libraries(${TEST_SPECS} PUBLIC ${CODE_UNDER_TEST})

add_executable(${PROJNAME} "testRunner.cpp")
target_link_libraries(${PROJNAME} PUBLIC ${TEST_SPECS})

```
3. Move `calculator.cpp` into the `src` folder, move `calculator.h` and `calculatorTests.h` to the `include` folder and move `calculatorTests.cpp` to the `test` folder test.

5. Build the project and correct any compiler errors, such as the `#include` statements.  

6. In the next walkthrough we will upgrade the tests to use googleTest syntax.

### Test project configuration within VS Code
With the changes made, Visual Studio Code and the CMake extension can be helpful in managing the project.  Open the CMake extension and from the toolbar at the top of the panel select **Delete Cache and Reconfigure**.  
    This will take in all of the changes that we have made and re-create the build scripts.  If prompted, choose the GCC Kit.  We can take some time to explore the features of the extension.  