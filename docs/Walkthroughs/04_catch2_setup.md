# Demonstrating Catch2 Test
This walkthrough will add in a link to the Catch2 testing library that has been copied to a shared directory.  In this case on the same machine, but it could be any UNC path.

## Add **Catch2 Test Library** Local Repo

1. The assumption is that the Catch2 repository has already been cloned to a subdirectory of the projects directory on othe current C: drive.  Otherwise, clone the repo.

```cmd
# change directory to  /c/projects (or some other location if you wish)
git clone https://github.com/catchorg/Catch2.git
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

# ADD CATCH2 TEST
# USE GIT_TAG FROM THE DESIRED COMMIT (LATEST?)
include(FetchContent)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY file:///c/projects/catch2/.git
  GIT_TAG v3.7.1 # latest release tag
)

# Make the fetched content declared above (catch2) available
FetchContent_MakeAvailable(catch2)

enable_testing()

# create the executable using the test specifications and the runner
add_executable(${PROJNAME} ${SOURCES} ${TEST_SOURCES})
target_link_libraries(${PROJNAME} PUBLIC ${CODE_UNDER_TEST})
```

3. Delete `testRunner.cpp` since Catch2 will now be providing the main method.

4. Modify the `add_executable` instruction to remove `SOURCES` from the list of source files.

5. Update the `target_link_libraries` instruction to add  `Catch2::Catch2WithMain` after `${CODE_UNDER_TEST}`.

6. Next add `include(Catch)` instruction to bring in `Catch`

7. Finally add `catch_discover_tests(${PROJNAME})` instruction to search for tests.  

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

# ADD CATCH2 TEST
# USE GIT_TAG FROM THE DESIRED COMMIT (LATEST?)
include(FetchContent)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY file:///c/projects/catch2/.git
  GIT_TAG v3.7.1 # latest release tag
)

# Make the fetched content declared above (catch2) available
FetchContent_MakeAvailable(catch2)

enable_testing()

# create the executable using the test specifications and the runner
add_executable(${PROJNAME}  ${TEST_SOURCES})
target_link_libraries(${PROJNAME} PUBLIC ${CODE_UNDER_TEST} Catch2::Catch2WithMain)
include(Catch)
catch_discover_tests(${PROJNAME})
```

8. Rebuild the project and make sure there are no errors.  The output should be that `No tests run` since there are no tests that use the Catch2 macros.

## Update the tests

1. Update `calculatorTests.cpp` to include Catch2 Test header file and to use the `TEST_CASE` macro to redefine the test and the `REQUIRE` macro to replace the `if` block. The `TEST_CASE` macro takes the test name as the first argument and an array of tags as the second argument.  (Tags can be used to filter tests.)

```cpp
// calculatorTests.cpp
#include <calculator.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Given 1 and 2 when added returns 3", "[Caclulator]")
{
    Calculator hp12c;
    int a = 1;
    int b = 2;
    int expected = a + b;
    int actual = hp12c.Add(a,b);
    REQUIRE(actual == expected);
}

TEST_CASE("Given 42 and 0 then added returns 42", "[Calculator]") {
    Calculator hp16c;
    int a = 1;
    int b = 2;
    int expected{a+b};

    REQUIRE(hp16c.Add(a,b)==expected);
}
```
2.  There is no longer a reference to `calculatorTests.h` so that file can be deleted.

## Build and Run Tests

1. Now you can build your project using the CMake extension.

2. To run the tests click the triangle in the bottom status bar of VS Code.

3. The output should appear in the terminal window.
```
C:\projects\tdd_app>"C:/projects/tdd_app/build/CalcProject.exe"
Randomness seeded to: 1738571504
===============================================================================
All tests passed (2 assertions in 2 test cases)
```