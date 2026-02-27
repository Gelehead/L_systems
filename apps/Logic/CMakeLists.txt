add_library(Logic STATIC
    src/cpp/GrammarCS_3D.cpp
    src/cpp/GrammarCS_1D.cpp
    src/cpp/Grammar.cpp
    src/cpp/GeneratorRegistry.cpp
)

target_include_directories(Logic PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
    Common
    Serialization
)