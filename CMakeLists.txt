cmake_minimum_required(VERSION 3.17.1)
project(Algorithm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(benchmark REQUIRED)

include_directories(src)

set(benchmarksSrc
    ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/common/Generators.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/common/Generators.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/Sorting.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/Matrix.cpp
)

add_executable(benchmarks ${benchmarksSrc})
target_link_libraries(benchmarks benchmark::benchmark_main)

set(testsSrc
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/Sorting.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/Matrix.cpp
)

enable_testing()
add_executable(tests ${testsSrc})
include(GoogleTest)
find_package(GTest REQUIRED)
target_link_libraries(tests GTest::gtest_main)
gtest_discover_tests(tests)