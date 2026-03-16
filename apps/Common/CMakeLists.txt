add_library(Common STATIC
    src/Region/Domain.cpp
    src/Region/Region.cpp
    src/Region/RegionMap.cpp
    src/Logger.cpp
)

target_include_directories(Common PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)