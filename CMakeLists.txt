cmake_minimum_required(VERSION 3.16)
project(L_systems VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define output directories in a platform-independent way
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Create output directories
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/grammars)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/noise)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/maps)

# Define source and include directories relative to project root
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CPP_DIR ${SRC_DIR}/cpp)
set(GRAMMARS_DIR ${SRC_DIR}/grammars)
set(PYTHON_DIR ${SRC_DIR}/Python)

# Include directories
include_directories(${INCLUDE_DIR})
include_directories(${CPP_DIR})

# Add Map/Tile testing executable
add_executable(Map_test
    ${CPP_DIR}/Tile_main.cpp
)

# default map json 
set(DEFAULT_MAP_JSON "${CMAKE_BINARY_DIR}/maps/default_map.json")

# Add grammar generator executable
add_executable(grammar_gen 
    ${CPP_DIR}/main.cpp
    ${CPP_DIR}/grammar.cpp
)

# Add Perlin noise generator executable
add_executable(perlin_gen 
    ${CPP_DIR}/noise_main.cpp
    ${CPP_DIR}/noise.cpp
)

# Set the default grammar file and output path as compile definitions
# These can be overridden at runtime
# DEFAULT IS cube_thing.txt
set(DEFAULT_GRAMMAR_FILE "${GRAMMARS_DIR}/cube_thing.txt")
set(DEFAULT_OUTPUT_PATH "${CMAKE_BINARY_DIR}/grammars/gram_gen.txt")

target_compile_definitions(grammar_gen PRIVATE 
    DEFAULT_GRAMMAR_FILE="${DEFAULT_GRAMMAR_FILE}"
    DEFAULT_OUTPUT_PATH="${DEFAULT_OUTPUT_PATH}"
)

# Copy grammar files to build directory
file(GLOB GRAMMAR_FILES "${GRAMMARS_DIR}/*.txt")
file(COPY ${GRAMMAR_FILES} DESTINATION ${CMAKE_BINARY_DIR}/grammars)

# Copy Python interpreter scripts
file(GLOB PYTHON_FILES "${PYTHON_DIR}/*.py")
file(COPY ${PYTHON_FILES} DESTINATION ${CMAKE_BINARY_DIR}/python)

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
    set OUTPUT_GRAMMAR_PATH=\"${CMAKE_BINARY_DIR}/grammars/%3\"
    set PENCIL_SIZE=%4
    set ANGLE=%5

    echo %GRAMMAR_FILE%

    cd \"${CMAKE_BINARY_DIR}/Debug\"

    grammar_gen.exe \"${GRAMMARS_DIR}/%GRAMMAR_FILE%\" %N_GENERATION% %OUTPUT_GRAMMAR_PATH%

    cd \"${CMAKE_BINARY_DIR}/python\"
    python interpreter.py %PENCIL_SIZE% %ANGLE% %OUTPUT_GRAMMAR_PATH%
    cd \"${CMAKE_BINARY_DIR}\"
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

    perlin_gen.exe %WIDTH% %HEIGHT% %FEATURE_SIZE% %OCTAVES% %PERSISTENCE% %OUTPUT_PATH% %COLORED%
        "
    )

    file(
        WRITE ${CMAKE_BINARY_DIR}/map_test.bat
        "
    @echo off
    set JSON_FILE=\"${DEFAULT_MAP_JSON}\"
    set OUTPUT_FILE=%1
    Map_test.exe %JSON_FILE% %OUTPUT_FILE%
        "
    )
else()
    # Unix shell script for grammar generator
    file(WRITE ${CMAKE_BINARY_DIR}/run_grammar.sh "#!/bin/bash
    N_GENERATION=5
    GRAMMAR_FILE=test.txt
    OUTPUT_GRAMMAR_PATH=\"${CMAKE_BINARY_DIR}/grammars/gram_gen.txt\"
    PENCIL_SIZE=1
    ANGLE=90

    \"${CMAKE_BINARY_DIR}/grammar_gen\" \"${CMAKE_BINARY_DIR}/grammars/$GRAMMAR_FILE\" $N_GENERATION \"$OUTPUT_GRAMMAR_PATH\"

    cd \"${CMAKE_BINARY_DIR}/python\"
    python interpreter.py $PENCIL_SIZE $ANGLE \"$OUTPUT_GRAMMAR_PATH\"
    cd \"${CMAKE_BINARY_DIR}\"
    ")
        
        # Unix shell script for Perlin noise generator
        file(WRITE ${CMAKE_BINARY_DIR}/run_perlin.sh "#!/bin/bash
    WIDTH=512
    HEIGHT=512
    FEATURE_SIZE=64
    OCTAVES=6
    PERSISTENCE=0.5
    OUTPUT_PATH=\"${CMAKE_BINARY_DIR}/noise/perlin_terrain.ppm\"
    COLORED=1

    \"${CMAKE_BINARY_DIR}/perlin_gen\" $WIDTH $HEIGHT $FEATURE_SIZE $OCTAVES $PERSISTENCE \"$OUTPUT_PATH\" $COLORED
    ")
    
    # Make the shell scripts executable
    execute_process(COMMAND chmod +x ${CMAKE_BINARY_DIR}/run_grammar.sh)
    execute_process(COMMAND chmod +x ${CMAKE_BINARY_DIR}/run_perlin.sh)
endif()

# For backward compatibility, create a copy of run_grammar.bat/sh as run.bat/sh
if(WIN32)
    configure_file(${CMAKE_BINARY_DIR}/run_grammar.bat ${CMAKE_BINARY_DIR}/run.bat COPYONLY)
else()
    configure_file(${CMAKE_BINARY_DIR}/run_grammar.sh ${CMAKE_BINARY_DIR}/run.sh COPYONLY)
    execute_process(COMMAND chmod +x ${CMAKE_BINARY_DIR}/run.sh)
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