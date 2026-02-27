cmake_minimum_required(VERSION 3.16)
project(grammarEngine VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# output directories 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# submodules 
find_package(Vulkan REQUIRED)

set(GLFW_BUILD_DOC      OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/vma)

# modules 
add_subdirectory(apps/Common)
add_subdirectory(apps/Serialization)
add_subdirectory(apps/Client)
add_subdirectory(apps/Logic)
add_subdirectory(apps/Renderer)
add_subdirectory(apps/Engine)

# main executable
add_executable(grammarEngine apps/main.cpp)

target_link_libraries(grammarEngine PRIVATE
    Engine
    Client
)

# plateform scripts 
if(WIN32)
    set(RUN_SCRIPT_IN ${CMAKE_SOURCE_DIR}/scripts/templates/run_grammar.bat.in)
    set(RUN_SCRIPT_OUT ${CMAKE_BINARY_DIR}/run.bat)
elseif(UNIX)
    set(RUN_SCRIPT_IN ${CMAKE_SOURCE_DIR}/scripts/templates/run_grammar.sh.in)
    set(RUN_SCRIPT_OUT ${CMAKE_BINARY_DIR}/run.sh)
else()
    message(WARNING "Plateform not supported for run script")
endif()

if(DEFINED RUN_SCRIPT_IN)
    configure_file(${RUN_SCRIPT_IN} ${RUN_SCRIPT_OUT} @ONLY)
    if(UNIX)
        file(CHMOD ${RUN_SCRIPT_OUT} PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE)
    endif()
endif()

# targets 
add_custom_target(run
    COMMAND ${CMAKE_BINARY_DIR}/bin/grammarEngine
    DEPENDS grammarEngine
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running MapEngine..."
)

add_custom_target(run_debug
    COMMAND ${CMAKE_BINARY_DIR}/bin/grammarEngine --debug
    DEPENDS grammarEngine
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running MapEngine in debug mode..."
)

# install 
install(TARGETS grammarEngine DESTINATION bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/apps/Data/ DESTINATION data)

# console output
message(STATUS "")
message(STATUS "┌─────────────────────────────────────────┐")
message(STATUS "│           MapEngine ${PROJECT_VERSION}              │")
message(STATUS "├─────────────────────────────────────────┤")
message(STATUS "│ Build type    : ${CMAKE_BUILD_TYPE}")
message(STATUS "│ Compiler      : ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "│ C++ Standard  : ${CMAKE_CXX_STANDARD}")
message(STATUS "│ Output dir    : ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "│ Vulkan        : ${Vulkan_VERSION}")
message(STATUS "└─────────────────────────────────────────┘")
message(STATUS "")