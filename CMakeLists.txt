cmake_minimum_required(VERSION 3.29)
project(HyperDemo)

add_subdirectory(external/HyperGpu)
add_subdirectory(external/HyperRender)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC HyperRender)