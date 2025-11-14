cmake_minimum_required(VERSION 3.30)
project(Algorithm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(AlgorithmSources 
    ${CMAKE_SOURCE_DIR}/Algorithm/Precompile.cpp
    ${CMAKE_SOURCE_DIR}/Algorithm/Search/BinarySearch.cpp
    ${CMAKE_SOURCE_DIR}/Algorithm/Sort/BubbleSort.cpp 
    ${CMAKE_SOURCE_DIR}/Algorithm/Sort/InsertionSort.cpp
    ${CMAKE_SOURCE_DIR}/Algorithm/Sort/MergeSort.cpp
    ${CMAKE_SOURCE_DIR}/Algorithm/Sort/SelectionSort.cpp
    ${CMAKE_SOURCE_DIR}/Algorithm/Sort/ShellSort.cpp
    ${CMAKE_SOURCE_DIR}/Algorithm/Sort/QuickSort.cpp
    ${CMAKE_SOURCE_DIR}/Tests/Algorithm/SortingTest.cpp
    ${CMAKE_SOURCE_DIR}/Tests/Algorithm/SearchTest.cpp
    ${CMAKE_SOURCE_DIR}/Tests/CommonFunctions.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${AlgorithmSources})

add_executable(AlgorithmTests ${AlgorithmSources})

target_include_directories(AlgorithmTests PRIVATE
    ${CMAKE_SOURCE_DIR}/Algorithm
    ${CMAKE_SOURCE_DIR}/Algorithm/Search
    ${CMAKE_SOURCE_DIR}/Algorithm/Sort
    ${CMAKE_SOURCE_DIR}/Tests)

target_link_libraries(
  AlgorithmTests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(AlgorithmTests)