cmake_minimum_required(VERSION 3.16)
project(L_systems VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define output directories in a platform-independent way
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Create output directories
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/out)

# Define source and include directories relative to project root
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CPP_DIR ${SRC_DIR}/cpp)
set(GRAMMARS_DIR ${SRC_DIR}/grammars)
set(PYTHON_DIR ${SRC_DIR}/Python)

# Include directories
include_directories(${INCLUDE_DIR})
include_directories(${CPP_DIR})

# default map json 
set(DEFAULT_MAP_JSON "${CMAKE_BINARY_DIR}/maps/default_map.json")

# grammar generator executable
add_executable(grammar_gen 
    ${CPP_DIR}/main.cpp
    ${CPP_DIR}/GrammarUnified.cpp
    ${CPP_DIR}/GrammarCS.cpp
    ${CPP_DIR}/grammar.cpp
)

# Perlin noise generator executable
add_executable(perlin_gen 
    ${CPP_DIR}/noise_main.cpp
    ${CPP_DIR}/noise.cpp
)

# Set the default grammar file and output path as compile definitions
# These can be overridden at runtime
# DEFAULT IS cube_thing.txt
set(DEFAULT_GRAMMAR_FILE "${GRAMMARS_DIR}/cube_thing.txt")
set(DEFAULT_OUTPUT_PATH "${CMAKE_BINARY_DIR}/out/gram_gen.txt")

target_compile_definitions(grammar_gen PRIVATE 
    DEFAULT_GRAMMAR_FILE="${DEFAULT_GRAMMAR_FILE}"
    DEFAULT_OUTPUT_PATH="${DEFAULT_OUTPUT_PATH}"
)

# Add install rules for better distribution
install(TARGETS grammar_gen perlin_gen DESTINATION bin)
install(FILES ${GRAMMAR_FILES} DESTINATION share/${PROJECT_NAME}/grammars)
install(FILES ${PYTHON_FILES} DESTINATION share/${PROJECT_NAME}/python)

# Create a platform-independent run script for grammar generator
if(WIN32)
    # Windows batch file for grammar generator
    file(
        WRITE ${CMAKE_BINARY_DIR}/run_grammar.bat 
        "
@echo off
set N_GENERATION=%2
set GRAMMAR_FILE=%1
set OUTPUT_GRAMMAR_PATH=%3
set PENCIL_SIZE=%4
set ANGLE=%5

echo Processing grammar file: %GRAMMAR_FILE%

REM Try to find grammar_gen.exe in common locations
set GRAMMAR_EXE=
if exist \"${CMAKE_BINARY_DIR}\\Release\\grammar_gen.exe\" (
    set GRAMMAR_EXE=\"${CMAKE_BINARY_DIR}\\Release\\grammar_gen.exe\"
) else if exist \"${CMAKE_BINARY_DIR}\\Debug\\grammar_gen.exe\" (
    set GRAMMAR_EXE=\"${CMAKE_BINARY_DIR}\\Debug\\grammar_gen.exe\"
) else if exist \"${CMAKE_BINARY_DIR}\\grammar_gen.exe\" (
    set GRAMMAR_EXE=\"${CMAKE_BINARY_DIR}\\grammar_gen.exe\"
) else if exist \"${CMAKE_BINARY_DIR}\\RelWithDebInfo\\grammar_gen.exe\" (
    set GRAMMAR_EXE=\"${CMAKE_BINARY_DIR}\\RelWithDebInfo\\grammar_gen.exe\"
) else if exist \"${CMAKE_BINARY_DIR}\\MinSizeRel\\grammar_gen.exe\" (
    set GRAMMAR_EXE=\"${CMAKE_BINARY_DIR}\\MinSizeRel\\grammar_gen.exe\"
) else (
    echo ERROR: Could not find grammar_gen.exe
    echo Looked in:
    echo   ${CMAKE_BINARY_DIR}\\Release\\grammar_gen.exe
    echo   ${CMAKE_BINARY_DIR}\\Debug\\grammar_gen.exe
    echo   ${CMAKE_BINARY_DIR}\\grammar_gen.exe
    echo   ${CMAKE_BINARY_DIR}\\RelWithDebInfo\\grammar_gen.exe
    echo   ${CMAKE_BINARY_DIR}\\MinSizeRel\\grammar_gen.exe
    exit /b 1
)

echo Found executable: %GRAMMAR_EXE%

REM Run the grammar generator
echo Running: %GRAMMAR_EXE% \"${CMAKE_BINARY_DIR}/grammars/%GRAMMAR_FILE%\" %N_GENERATION% \"${CMAKE_BINARY_DIR}/grammars/%OUTPUT_GRAMMAR_PATH%\"
%GRAMMAR_EXE% \"${CMAKE_BINARY_DIR}/grammars/%GRAMMAR_FILE%\" %N_GENERATION% \"${CMAKE_BINARY_DIR}/grammars/%OUTPUT_GRAMMAR_PATH%\"

if %ERRORLEVEL% neq 0 (
    echo ERROR: Grammar generation failed with error code %ERRORLEVEL%
    exit /b %ERRORLEVEL%
)

echo Grammar generation completed successfully
echo Output saved to: ${CMAKE_BINARY_DIR}/grammars/%OUTPUT_GRAMMAR_PATH%
        "
    )
        
    # Windows batch file for Perlin noise generator
    file(
        WRITE ${CMAKE_BINARY_DIR}/run_perlin.bat 
        "
@echo off
set WIDTH=512
set HEIGHT=512
set FEATURE_SIZE=64
set OCTAVES=6
set PERSISTENCE=0.5
set OUTPUT_PATH=\"${CMAKE_BINARY_DIR}/noise/perlin_terrain.ppm\"
set COLORED=1

REM Find perlin_gen.exe
set PERLIN_EXE=
if exist \"${CMAKE_BINARY_DIR}/perlin_gen.exe\" (
    set PERLIN_EXE=\"${CMAKE_BINARY_DIR}/perlin_gen.exe\"
) else if exist \"${CMAKE_BINARY_DIR}/Debug/perlin_gen.exe\" (
    set PERLIN_EXE=\"${CMAKE_BINARY_DIR}/Debug/perlin_gen.exe\"
) else if exist \"${CMAKE_BINARY_DIR}/Release/perlin_gen.exe\" (
    set PERLIN_EXE=\"${CMAKE_BINARY_DIR}/Release/perlin_gen.exe\"
) else (
    echo ERROR: Could not find perlin_gen.exe
    exit /b 1
)

%PERLIN_EXE% %WIDTH% %HEIGHT% %FEATURE_SIZE% %OCTAVES% %PERSISTENCE% %OUTPUT_PATH% %COLORED%
        "
    )

    file(
        WRITE ${CMAKE_BINARY_DIR}/map_test.bat
        "
@echo off
set JSON_FILE=\"${DEFAULT_MAP_JSON}\"
set OUTPUT_FILE=%1

REM Find Map_test.exe
set MAP_EXE=
if exist \"${CMAKE_BINARY_DIR}/Map_test.exe\" (
    set MAP_EXE=\"${CMAKE_BINARY_DIR}/Map_test.exe\"
) else if exist \"${CMAKE_BINARY_DIR}/Debug/Map_test.exe\" (
    set MAP_EXE=\"${CMAKE_BINARY_DIR}/Debug/Map_test.exe\"
) else if exist \"${CMAKE_BINARY_DIR}/Release/Map_test.exe\" (
    set MAP_EXE=\"${CMAKE_BINARY_DIR}/Release/Map_test.exe\"
) else (
    echo ERROR: Could not find Map_test.exe
    exit /b 1
)

%MAP_EXE% %JSON_FILE% %OUTPUT_FILE%
        "
    )
else()
    # CODE FOR UNIX HERE 
endif()

# Add custom targets to run the programs
add_custom_target(run_grammar
    DEPENDS grammar_gen
    COMMAND ${CMAKE_BINARY_DIR}/run_grammar${CMAKE_EXECUTABLE_SUFFIX}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running L-systems generator"
)

add_custom_target(run_perlin
    DEPENDS perlin_gen
    COMMAND ${CMAKE_BINARY_DIR}/run_perlin${CMAKE_EXECUTABLE_SUFFIX}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Perlin noise generator"
)

# For backward compatibility
add_custom_target(run
    DEPENDS grammar_gen
    COMMAND ${CMAKE_BINARY_DIR}/run${CMAKE_EXECUTABLE_SUFFIX}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running L-systems generator"
)

# Output configuration information
message(STATUS "L-systems configuration:")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Default grammar: ${DEFAULT_GRAMMAR_FILE}")
message(STATUS "  Grammar output: ${DEFAULT_OUTPUT_PATH}")