add_library(Engine STATIC
    src/Engine.cpp
    src/GenerationScheduler.cpp
)

target_include_directories(Engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include`
)

target_link_libraries(
    Common
    Renderer
    Logic
    Serialization   
)