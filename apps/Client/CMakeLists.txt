add_library(Client STATIC
    src/Pages/src/Visualization.cpp
    src/Pages/src/Rules.cpp
    src/Pages/src/Manage.cpp
    src/Widgets/src/Stepper.cpp
    src/Widget/src/FileSelctor.cpp
    src/Views/src/MapView.cpp
)

target_include_directories(Client PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Client PRIVATE
    Common
    Engine      # for MapCommand queue access
    Renderer    # for imgui layer
)
