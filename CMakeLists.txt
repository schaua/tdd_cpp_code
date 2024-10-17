cmake_minimum_required(VERSION 3.14...3.28)
set(PROJNAME CalcProject) 
set(CODE_UNDER_TEST CalcCode)
set(TEST_SPECS CalcTests)
project(${PROJNAME} LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# file(GLOB MY_CODE "*.cpp")
file(GLOB_RECURSE MY_CODE "src/*.cpp")
file(GLOB_RECURSE MY_TESTS "test/*.cpp")

add_library(${CODE_UNDER_TEST} STATIC ${MY_CODE})
target_include_directories(${CODE_UNDER_TEST} PUBLIC include)

# GOOGLE TEST WILL MERGE THIS WITH THE EXECUTABLE
# add_library(${TEST_SPECS} STATIC ${MY_TESTS})
# target_include_directories(${TEST_SPECS} PUBLIC include)
# target_link_libraries(${TEST_SPECS} PUBLIC  ${CODE_UNDER_TEST})

# ADD GOOGLE TEST
# USE GIT_TAG FROM THE DESIRED COMMIT (LATEST?)
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2 
    # df1544bcee0c7ce35cd5ea0b3eb8cc81855a4140
)

# For windows: Prevent overriding the partent project's compiler/linker
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)


# Make the fetched content (GoogleTest) available
FetchContent_MakeAvailable(googletest)

enable_testing()
# add_executable(${PROJNAME} "testRunner.cpp" )
# target_link_libraries(${PROJNAME} PUBLIC ${TEST_SPECS})
add_executable(${PROJNAME} ${MY_TESTS})
target_link_libraries(${PROJNAME} PUBLIC ${CODE_UNDER_TEST} gtest gmock gtest_main)
include(GoogleTest)
gtest_discover_tests(${PROJNAME})