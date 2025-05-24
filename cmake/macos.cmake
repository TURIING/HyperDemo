add_definitions(-DPLATFORM_MACOS)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets HyperRender)
