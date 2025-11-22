add_definitions(-DPLATFORM_ANDROID)

set_target_properties(${PROJECT_NAME} PROPERTIES
        ${BUNDLE_ID_OPTION}
        QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/android
)

find_library(android-lib android)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets HyperRender android)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/android-build/libs/arm64-v8a/")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/lib${PROJECT_NAME}_arm64-v8a.so"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/android-build/libs/arm64-v8a/")