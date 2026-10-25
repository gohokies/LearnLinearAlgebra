cmake_minimum_required(VERSION 3.21)

project(LearnLinearAlgebra)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()
include(CTest)

add_subdirectory(src)

add_subdirectory(test)