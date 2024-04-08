cmake_minimum_required(VERSION 3.0)
project(Conway)

add_executable(${PROJECT_NAME} src/main.cpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 23)
set(JSON_INCLUDE_DIR /home/carmelo/Escritorio/libs/json-develop/include/nlohmann/)

find_package(wxWidgets REQUIRED COMPONENTS core base)

include(${wxWidgets_USE_FILE})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC src/
)