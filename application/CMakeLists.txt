include_directories(ui/)

file(GLOB_RECURSE SOURCE CONFIGURE_DEPENDS ./*.cpp ./*.h ./*.mm)

add_library(application OBJECT ${SOURCE})

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/windows.cmake)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/macos.cmake)
elseif (CMAKE_SYSTEM_NAME STREQUAL "iOS")
    include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/ios.cmake)
endif ()

target_include_directories(application PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})