cmake_minimum_required(VERSION 3.15)
project(HyperDemo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_SOURCE_DIR}/application/form")

add_definitions(-DGRAPHICS_VULKAN)
#add_definitions(-DGRAPHICS_OPENGL)
include_directories(${CMAKE_SOURCE_DIR}/external/HyperRender/include)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(CMAKE_PREFIX_PATH "C:/Qt/6.8.1/msvc2022_64")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(CMAKE_PREFIX_PATH "/Users/turiing/Qt/6.6.3/macos/lib/cmake")
elseif(CMAKE_SYSTEM_NAME STREQUAL "iOS")
    set(CMAKE_PREFIX_PATH "/Users/turiing/Qt/6.6.3/ios/")
endif ()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

#add_subdirectory(external/spdlog)
add_subdirectory(external/HyperRender)
add_subdirectory(application)
add_subdirectory(tests)



#include(GNUInstallDirs)
#install(TARGETS ${PROJECT_NAME}
#        BUNDLE DESTINATION ..
#        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)
#
#if(QT_VERSION_MAJOR EQUAL 6)
#    qt_finalize_executable(${PROJECT_NAME})
#endif()
