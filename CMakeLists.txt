cmake_minimum_required(VERSION 3.16)
project(L_systems VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define output directories in a platform-independent way
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Create output directories
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/grammars)

# Define source and include directories relative to project root
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CPP_DIR ${SRC_DIR}/cpp)
set(GRAMMARS_DIR ${SRC_DIR}/grammars)
set(PYTHON_DIR ${SRC_DIR}/Python)

# Include directories
include_directories(${INCLUDE_DIR})
include_directories(${CPP_DIR})

# Add grammar generator executable
add_executable(grammar_gen ${CPP_DIR}/main.cpp)

# Set the default grammar file and output path as compile definitions
# These can be overridden at runtime
set(DEFAULT_GRAMMAR_FILE "${GRAMMARS_DIR}/test.txt")
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
install(TARGETS grammar_gen DESTINATION bin)
install(FILES ${GRAMMAR_FILES} DESTINATION share/${PROJECT_NAME}/grammars)
install(FILES ${PYTHON_FILES} DESTINATION share/${PROJECT_NAME}/python)

# Create a platform-independent run script
if(WIN32)
    # Windows batch file
    file(WRITE ${CMAKE_BINARY_DIR}/run.bat "
@echo off
set N_GENERATION=5
set GRAMMAR_FILE=test.txt
set OUTPUT_GRAMMAR_PATH=\"${CMAKE_BINARY_DIR}/grammars/gram_gen.txt\"
set PENCIL_SIZE=1
set ANGLE=90

grammar_gen.exe \"${CMAKE_BINARY_DIR}/grammars/%GRAMMAR_FILE%\" %N_GENERATION% %OUTPUT_GRAMMAR_PATH%

cd \"${CMAKE_BINARY_DIR}/python\"
python interpreter.py %PENCIL_SIZE% %ANGLE% %OUTPUT_GRAMMAR_PATH%
cd \"${CMAKE_BINARY_DIR}\"
")
else()
    # Unix shell script
    file(WRITE ${CMAKE_BINARY_DIR}/run.sh "#!/bin/bash
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
    # Make the shell script executable
    execute_process(COMMAND chmod +x ${CMAKE_BINARY_DIR}/run.sh)
endif()

# Add a custom target to run the program
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