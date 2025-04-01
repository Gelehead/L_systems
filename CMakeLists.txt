cmake_minimum_required(VERSION 3.16)
project(L_systems VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set Vulkan SDK, library and include directories manually
set(VULKAN_SDK_PATH "C:/VulkanSDK/1.4.309.0")

set(Vulkan_INCLUDE_DIR "${VULKAN_SDK_PATH}/Include")
set(Vulkan_LIBRARY "${VULKAN_SDK_PATH}/Lib/vulkan-1.lib") 

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Find Vulkan package
find_package(Vulkan QUIET)
find_package(glfw3 REQUIRED)

if (NOT Vulkan_FOUND)
    message(STATUS "Using manually specified Vulkan paths")
    set(Vulkan_INCLUDE_DIRS ${Vulkan_INCLUDE_DIR})
    set(Vulkan_LIBRARIES ${Vulkan_LIBRARY})
    set(Vulkan_FOUND TRUE)
endif()

# Add source files
set(SOURCES 
    src/cpp/main.cpp
    src/cpp/vulkan_app.cpp
)

# Create executable
add_executable(grammar_gen src/cpp/main.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Vulkan_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        ${Vulkan_LIBRARIES}
        glfw
)

# Shader compilation
# This assumes you have glslc installed (part of Vulkan SDK)
set(SHADER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SHADER_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/shaders)

# Create shader output directory
file(MAKE_DIRECTORY ${SHADER_BINARY_DIR})

# create grammars directory
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/grammars)

# Find all shader files
file(GLOB SHADERS
    ${SHADER_SOURCE_DIR}/*.vert
    ${SHADER_SOURCE_DIR}/*.frag
)

# Compile shaders
foreach(SHADER IN LISTS SHADERS)
    get_filename_component(FILENAME ${SHADER} NAME)
    add_custom_command(
        OUTPUT ${SHADER_BINARY_DIR}/${FILENAME}.spv
        COMMAND ${Vulkan_GLSLC_EXECUTABLE} ${SHADER} -o ${SHADER_BINARY_DIR}/${FILENAME}.spv
        DEPENDS ${SHADER}
        COMMENT "Compiling shader ${FILENAME}"
    )
    list(APPEND SHADER_BINARIES ${SHADER_BINARY_DIR}/${FILENAME}.spv)
endforeach()

# Add shader compilation as a dependency
add_custom_target(shaders DEPENDS ${SHADER_BINARIES})
add_dependencies(${PROJECT_NAME} shaders)