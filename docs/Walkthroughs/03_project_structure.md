# Walkthrough Separating Source and Tests
It is common to want to keep the code under test and the tests themselves separate from each other.  This allows for the tests to be built as a library and then linked to the executable that will run the tests.  
These changes in structure with this walkthrough will also require some changes to the `CMakeLists.txt` configuration so that the project still builds correct.  
## Demonstration
1. The `calculatorTests.cpp` file that contains all of the tests will be the source file for a link library that defines the tests.
2. Create a directory structure to separate the tests from the code under test.  
```
tdd_app/
|- src/
|   |- include/
|- test/
```
3. Move the `calculatorTest.h` and `calculatorTest.cpp` files to the `test` directory.  Move the `calculator.cpp` file to the `src` directory and the `calculator.h` to the `src/includ` directory.
```
project/
|   |- CMakeLists.txt
|   |- testRunner.cpp
|- src/
|   |- calculator.cpp
|   |- include/
|       |- calculator.h
|- test/
|   |- calculatorTests.cpp
|   |- calculatorTests.h
|- build/
```
4. Edit the `#include` statements to reflect the new locations of the `calculator.h` header file.  In `calculator.cpp` change it to `#include "include/calculator.h`.  In `calculatorTests.cpp` change it to `#include "../src/include/calculator.h"`.  Finally in `testRunner.cpp` change it to `#include test/calculatorTests.h`.
5. Edit the `CMakeLists.txt` file to create a library to share the src for the code under test. 
- Modify the executable to include the source for the test specifications as well as the runner code. 
- Add a new variable for `CODE_UNDER_TEST`.  
- Add two additional file definitions to get all of the code files in the src directory as `COT_SOURCES` and the test directory as `TEST_SOURCES`.  
- Add a library for `CODE_UNDER_TEST` and make the `include` directory available.  
- Add the `TEST_SPECS` to the executable source list.
- Add a link to the `CODE_UNDER_TEST` library.   
The result should look similar to this:
```cmake
cmake_minimum_required(VERSION 3.10...3.28)
set (PROJNAME CalcProject)
set (CODE_UNDER_TEST CalcCode)
project(${PROJNAME} VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# locations for the different source files
file(GLOB SOURCES "*.cpp")
file(GLOB_RECURSE COT_SOURCES "./src/*.cpp")
file(GLOB_RECURSE TEST_SOURCES "./test/*.cpp")

# create a library for the code under test
add_library(${CODE_UNDER_TEST} STATIC ${COT_SOURCES})
target_include_directories(${CODE_UNDER_TEST} PUBLIC src/include)

# create the executable using the test specifications and the runner
add_executable(${PROJNAME} ${SOURCES} ${TEST_SOURCES})
target_link_libraries(${PROJNAME} PUBLIC ${CODE_UNDER_TEST})

```
6. Build the project and correct any compiler errors, such as the `#include` statements.  

7. Confirm that the tests are still successful.

8. In the next two walkthroughs we will upgrade the tests to use one of the common test library projects.  Either the [Catch2](./04_catch2_setup.md) or [googleTest](./05_gtest_setup.md) library.

### Test project configuration within VS Code
With the changes made, Visual Studio Code and the CMake extension can be helpful in managing the project.  Open the CMake extension and from the toolbar at the top of the panel select **Delete Cache and Reconfigure**.  
    This will take in all of the changes that we have made and re-create the build scripts.  If prompted, choose the GCC Kit.  We can take some time to explore the features of the extension.  