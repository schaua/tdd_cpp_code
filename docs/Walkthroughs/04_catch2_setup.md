# Demonstrating Google Test

## Option 1 Add **Google Test Library** Web Link

1. Edit `CMakeLists.txt` to add fetching googletest.

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

# GOOGLE TEST WILL MERGE THIS WITH THE EXECUTABLE
# add_library(${TEST_SPECS} STATIC ${MY_TESTS})
# target_include_directories(${TEST_SPECS} PUBLIC include)
# target_link_libraries(${TEST_SPECS} PUBLIC ${CODE_UNDER_TEST})

# ADD GOOGLE TEST
# USE GIT_TAG FROM THE DESIRED COMMIT (LATEST?)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2 # latest release tag
)

# For Windows: Prevent overriding the parent project's compiler/linker
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Make the fetched content (GoogleTest) available
FetchContent_MakeAvailable(googletest)

enable_testing()

# GOOGLE TEST WILL PROVIDE THE main METHOD
#add_executable(${PROJNAME} "testRunner.cpp")
#target_link_libraries(${PROJNAME} PUBLIC ${TEST_SPECS})
add_executable(${PROJNAME} ${MY_TESTS})
target_link_libraries(${PROJNAME} PUBLIC ${CODE_UNDER_TEST} gtest gmock gtest_main)
include(GoogleTest)
gtest_discover_tests(${PROJNAME})

```

## Option 2 Add **Google Test Library** Local Repo

1. Clone the googletest repository.

```cmd
# change directory to  /c/projects or some other location as you wish
git clone https://github.com/google/googletest.git
```

Edit `CMakeLists.txt` to add fetching googletest.

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

# GOOGLE TEST WILL MERGE THIS WITH THE EXECUTABLE
# add_library(${TEST_SPECS} STATIC ${MY_TESTS})
# target_include_directories(${TEST_SPECS} PUBLIC include)
# target_link_libraries(${TEST_SPECS} PUBLIC ${CODE_UNDER_TEST})

# ADD GOOGLE TEST
# USE GIT_TAG FROM THE DESIRED COMMIT (LATEST?)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY file:///c/projects/googletest/.git
  GIT_TAG v1.15.2 # latest release tag
)

# For Windows: Prevent overriding the parent project's compiler/linker
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Make the fetched content (GoogleTest) available
FetchContent_MakeAvailable(googletest)

enable_testing()

# GOOGLE TEST WILL PROVIDE THE main METHOD
#add_executable(${PROJNAME} "testRunner.cpp")
#target_link_libraries(${PROJNAME} PUBLIC ${TEST_SPECS})
add_executable(${PROJNAME} ${MY_TESTS})
target_link_libraries(${PROJNAME} PUBLIC ${CODE_UNDER_TEST} gtest gmock gtest_main)
include(GoogleTest)
gtest_discover_tests(${PROJNAME})

```

2. Delete `testRunner.cpp` since GoogleTest will now be providing the main method.

## Update the test

1. Update `calculatorTests.cpp` to include Google Test header file and to use the `TEST` macro to redefine the test and the `EXPECT_EQ` macro to replace the `if`. The `TEST` macro takes the test suite name as the first argument and the test name as the second argument.

```cpp
// calculatorTests.cpp
#include "../include/calculator.h"
#include <gtest/gtest.h>

TEST(CalcTest, given_two_positive_integers_when_asked_to_add_returns_their_sum) {
    Calculator hp16c;
    int a = 1;
    int b = 2;
    int expected{a+b};

    EXPECT_EQ(hp16c.Add(a,b), expected);
}
```

## Build and Run Tests

1. Now you can build your project using the CMake extension.

2. To run the tests click the triangle in the bottom status bar of VS Code.

3. The output should appear in the terminal window.

   There is an optional Testing Extension within VS Code. The one extra requirement that the extension imposes is that the default glob pattern looks for targets that end with test, so it would require that the add_executable, add_link_libraries and gtest_discover_tests all be working with a name that ends with test.
   **NOTE** You can experiment with this if you wish.
