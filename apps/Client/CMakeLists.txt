add_library(Client STATIC
    src/Pages/Visualization.cpp
    src/Pages/Rules.cpp
    src/Pages/Manage.cpp
    src/Widgets/Stepper.cpp
    src/Widgets/FileSelector.cpp
    src/Views/MapView.cpp
)

target_include_directories(Client PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Client PRIVATE
    Common
    Engine      # for MapCommand queue access
    Renderer    # for imgui layer
)
