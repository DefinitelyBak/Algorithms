cmake_minimum_required(VERSION  3.17.1)
project(Algorithm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(benchmark REQUIRED)

file(GLOB src "src/sort/")

add_executable(my_bench main.cpp ${src})

target_link_libraries(my_bench benchmark::benchmark_main)
