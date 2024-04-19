cmake_minimum_required(VERSION 3.22.1)
project(computing)

add_executable(${PROJECT_NAME} computing.cpp)

set(CMAKE_CXX_FLAGS "-g -O0")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 23)

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC ../../src/
)