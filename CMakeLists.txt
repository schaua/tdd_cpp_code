cmake_minimum_required(VERSION 3.14...3.28)
set(PROJNAME CalcProject) 
# set(CODE_UNDER_TEST CalcCode)
# set(TEST_SPECS CalcTests)
project(${PROJNAME} LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB MY_CODE "*.cpp")
# file(GLOB_RECURSE MY_CODE "src/*.cpp")
# file(GLOB_RECURSE MY_TESTS "test/*.cpp")

# add_library(${CODE_UNDER_TEST} STATIC ${MY_CODE})
# target_include_directories(${CODE_UNDER_TEST} PUBLIC include)
# # target_compile_features(${CODE_UNDER_TEST} public cxx_std_20)

# add_library(${TEST_SPECS} STATIC ${MY_TESTS})
# target_include_directories(${TEST_SPECS} PUBLIC include)

add_executable(${PROJNAME} ${MY_CODE} )
