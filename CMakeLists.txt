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
    ${CMAKE_SOURCE_DIR}/Algorithm/Search/Source/BinarySearch.cpp
    ${CMAKE_SOURCE_DIR}/Algorithm/Sort/Source/BubbleSort.cpp 
    ${CMAKE_SOURCE_DIR}/Algorithm/Sort/Source/InsertionSort.cpp
    ${CMAKE_SOURCE_DIR}/Algorithm/Sort/Source/MergeSort.cpp
    ${CMAKE_SOURCE_DIR}/Algorithm/Sort/Source/SelectionSort.cpp
    ${CMAKE_SOURCE_DIR}/Algorithm/Sort/Source/ShellSort.cpp
    ${CMAKE_SOURCE_DIR}/Algorithm/Sort/Source/QuickSort.cpp
    ${CMAKE_SOURCE_DIR}/Tests/Source/Algorithm/SortingTest.cpp
    ${CMAKE_SOURCE_DIR}/Tests/Source/Algorithm/SearchTest.cpp
    ${CMAKE_SOURCE_DIR}/Tests/Source/CommonFunctions.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${AlgorithmSources})

add_executable(AlgorithmTests ${AlgorithmSources})

target_include_directories(AlgorithmTests PRIVATE
    ${CMAKE_SOURCE_DIR}/Algorithm
    ${CMAKE_SOURCE_DIR}/Algorithm/Search/Include
    ${CMAKE_SOURCE_DIR}/Algorithm/Sort/Include
    ${CMAKE_SOURCE_DIR}/Tests/Include)

target_link_libraries(
  AlgorithmTests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(AlgorithmTests)