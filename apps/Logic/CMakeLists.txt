add_library(Logic STATIC
    src/cpp/Grammars/GrammarCS.cpp
    src/cpp/GeneratorRegistry.cpp
)

target_include_directories(Logic PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Logic PRIVATE
    Common
    Serialization
)