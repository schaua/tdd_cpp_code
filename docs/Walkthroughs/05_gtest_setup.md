# Demonstrating Google Test
This walkthrough will add in a link to the GoogleTest testing library that has been copied to a shared directory.  In this case on the same machine, but it could be any UNC path.

## Add **Google Test Library** Local Repo

1. The assumption is that the GoogleTest repository has already been cloned to a subdirectory of the projects directory on othe current C: drive.  Otherwise, clone the repo.

```cmd
# change directory to  /c/projects (or some other location if you wish)
git clone https://github.com/google/googletest.git
```

2. Edit `CMakeLists.txt` to remove the first file glob location, add `FetchContent` for the testing library and `enable_testing`.

```cmake
cmake_minimum_required(VERSION 3.10...3.28)
set (PROJNAME CalcProject)
set (CODE_UNDER_TEST CalcCode)
project(${PROJNAME} VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# locations for the different source files
file(GLOB_RECURSE COT_SOURCES "./src/*.cpp")
file(GLOB_RECURSE TEST_SOURCES "./test/*.cpp")

# create a library for the code under test
add_library(${CODE_UNDER_TEST} STATIC ${COT_SOURCES})
target_include_directories(${CODE_UNDER_TEST} PUBLIC src/include)

# ADD GOOGLETEST TEST
# USE GIT_TAG FROM THE DESIRED COMMIT (LATEST?)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY file:///c/projects/googletest/.git
  GIT_TAG v1.15.2 # latest release tag
)

# Make the fetched content declared above (googletest) available
FetchContent_MakeAvailable(googletest)

enable_testing()

# create the executable using the test specifications and the runner
add_executable(${PROJNAME} ${SOURCES} ${TEST_SOURCES})
target_link_libraries(${PROJNAME} PUBLIC ${CODE_UNDER_TEST})
```

3. Delete `testRunner.cpp` since GoogleTest will now be providing the main method.

4. Modify the `add_executable` instruction to remove `SOURCES` from the list of source files.

5. Update the `target_link_libraries` instruction to add  `gtest` and `gtest_main` after `${CODE_UNDER_TEST}`.

6. Next add `include(GoogleTest)` instruction to bring in `GoogleTest`

7. Finally add `gtest_discover_tests(${PROJNAME})` instruction to search for tests.  

The final `CMakeLists.txt` should look similar to this:

```cmake
cmake_minimum_required(VERSION 3.10...3.28)
set (PROJNAME CalcProject)
set (CODE_UNDER_TEST CalcCode)
project(${PROJNAME} VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# locations for the different source files
file(GLOB_RECURSE COT_SOURCES "./src/*.cpp")
file(GLOB_RECURSE TEST_SOURCES "./test/*.cpp")

# create a library for the code under test
add_library(${CODE_UNDER_TEST} STATIC ${COT_SOURCES})
target_include_directories(${CODE_UNDER_TEST} PUBLIC src/include)

# ADD GOOGLETEST TEST
# USE GIT_TAG FROM THE DESIRED COMMIT (LATEST?)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY file:///c/projects/googletest/.git
  GIT_TAG v1.15.2 # latest release tag
)

# Make the fetched content declared above (googletest) available
FetchContent_MakeAvailable(googletest)

enable_testing()

# create the executable using the test specifications and the runner
add_executable(${PROJNAME}  ${TEST_SOURCES})
target_link_libraries(${PROJNAME} PUBLIC ${CODE_UNDER_TEST} gtest gtest_main)
include(GoogleTest)
gtest_discover_tests(${PROJNAME})
```

8. Rebuild the project and make sure there are no errors.  The output should be that `0 tests` since there are no tests that use the GoogleTest macros.

## Update the tests

1. Update `calculatorTests.cpp` to include GoogleTest Test header file and to use the `TEST` macro to redefine the test and the `EXPECT_EQ` macro to replace the `if` block. The `TEST` macro takes a test suite name as the first argument and the test name as the second argument.

```cpp
// calculatorTests.cpp
#include <calculator.h>
#include <gtest/gtest.h>

TEST(CalculatorTests, Given_1_and_2_when_added_returns_3)
{
    Calculator hp12c;
    int a = 1;
    int b = 2;
    int expected = a + b;
    int actual = hp12c.Add(a,b);
    EXPECT_EQ(actual,expected);
}

TEST(CalculatorTests, Given_42_and_0_then_added_returns_42) 
{
    Calculator hp16c;
    int a = 1;
    int b = 2;
    int expected{a+b};

    EXPECT_EQ(hp16c.Add(a,b),expected);
}
```
2.  There is no longer a reference to `calculatorTests.h` so that file can be deleted.

## Build and Run Tests

1. Now you can build your project using the CMake extension.

2. To run the tests click the triangle in the bottom status bar of VS Code.

3. The output should appear in the terminal window.
```
$ "C:/projects/tdd_app/build/CalcProject.exe"
Running main() from C:\projects\tdd_app\build\_deps\googletest-src\googletest\src\gtest_main.cc
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from CalculatorTests
[ RUN      ] CalculatorTests.Given_1_and_2_when_added_returns_3
[       OK ] CalculatorTests.Given_1_and_2_when_added_returns_3 (0 ms)
[ RUN      ] CalculatorTests.Given_42_and_0_then_added_returns_42
[       OK ] CalculatorTests.Given_42_and_0_then_added_returns_42 (0 ms)
[----------] 2 tests from CalculatorTests (16 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (29 ms total)
[  PASSED  ] 2 tests.
```