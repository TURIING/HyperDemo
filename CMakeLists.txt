cmake_minimum_required(VERSION 3.29)
project(HyperDemo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_SOURCE_DIR}/src/form")

#add_definitions(-DGRAPHICS_VULKAN)
add_definitions(-DGRAPHICS_OPENGL)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(CMAKE_PREFIX_PATH "C:/Qt/6.8.1/msvc2022_64")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(CMAKE_PREFIX_PATH "/Users/turiing/Qt/6.8.1/macos/lib/cmake")
endif ()

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

add_subdirectory(external/HyperRender)

file(GLOB_RECURSE SOURCE CONFIGURE_DEPENDS src/*.cpp src/*.h)
add_executable(${PROJECT_NAME} ${SOURCE})

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    include(${CMAKE_SOURCE_DIR}/cmake/windows.cmake)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    include(${CMAKE_SOURCE_DIR}/cmake/macos.cmake)
endif ()