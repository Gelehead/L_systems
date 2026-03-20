add_library(Renderer STATIC
    src/VulkanContext.cpp
    src/VulkanSwapchain.cpp
    src/VulkanPipeline.cpp
    src/MeshBuilder.cpp
    src/ChunkManager.cpp
    src/ImGuiLayer.cpp
)

target_include_directories(Renderer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Renderer PUBLIC
    Common
    Vulkan::Vulkan
    glfw
    imgui
    glm::glm
    VulkanMemoryAllocator
)

find_program(GLSLC glslc HINTS $ENV{VULKAN_SDK}/bin REQUIRED)

file(GLOB_RECURSE SHADER_SOURCES
    ${CMAKE_SOURCE_DIR}/apps/Data/shaders/*.vert
    ${CMAKE_SOURCE_DIR}/apps/Data/shaders/*.frag
)

foreach(Shader ${SHADER_SOURCES})
    get_filename_component(SHADER_NAME ${SHADER} NAME)
    set(SHADER_OUT ${CMAKE_BINARY_DIR}/shaders/${SHADER_NAME}.spv)
    add_custom_command(
        OUTPUT ${SHADER_OUT}
        COMMAND ${GLSLC} ${SHADER} -o ${SHADER_OUT}
        DEPENDS ${SHADER}
        COMMENT "compiling shader ${SHADER_OUT}"   
    )
    list(APPEND SHADER_OUTPUTS ${SHADER_OUT})
endforeach()

add_custom_target(Shaders ALL DEPENDS ${SHADER_OUTPUTS})
add_dependencies(Renderer Shaders)