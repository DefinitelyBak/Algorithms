cmake_minimum_required(VERSION 3.30)
project(Algorithm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(sources 
  ${CMAKE_SOURCE_DIR}/Sort/Precompile.cpp 
  ${CMAKE_SOURCE_DIR}/Sort/Tests/Source/AlgorithmTest.cpp
  ${CMAKE_SOURCE_DIR}/Sort/Tests/Include/AlgorithmTest.h
  )
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

add_executable(SortsTest ${sources})

target_include_directories(SortsTest PRIVATE
    ${CMAKE_SOURCE_DIR}/Sort
    ${CMAKE_SOURCE_DIR}/Sort/Include
    ${CMAKE_SOURCE_DIR}/Sort/Tests/Include
)

target_link_libraries(
  SortsTest
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(SortsTest)
