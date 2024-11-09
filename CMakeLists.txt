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