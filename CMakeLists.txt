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


# grammar generator executable
add_executable(grammar_gen 
    ${CPP_DIR}/main.cpp
    ${CPP_DIR}/GrammarUnified.cpp
    ${CPP_DIR}/GrammarCS_1D.cpp
    ${CPP_DIR}/GrammarCS_3D.cpp
    ${CPP_DIR}/grammar.cpp
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

# Create a platform-independent run script for grammar generator
if(WIN32)
  set(RUN_GRAMMAR_SCRIPT run_grammar.bat)
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
  elseif(UNIX)
  set(RUN_GRAMMAR_SCRIPT run_grammar.sh)
    file(
    # CODE FOR UNIX HERE
    WRITE ${CMAKE_BINARY_DIR}/run_grammar.sh
            "
#!/usr/bin/env bash
#Arguments
GRAMMAR_FILE=\"$1\"
N_GENERATION=\"$2\"
OUTPUT_GRAMMAR_PATH=\"$3\"
PENCIL_SIZE=\"$4\"
ANGLE=\"$5\"
            
echo \"Processing grammar file: \$GRAMMAR_FILE\"
            
# Try to find grammar_gen in common locations
GRAMMAR_EXE=\"\"
            
if [ -x \"${CMAKE_BINARY_DIR}/Release/grammar_gen\" ]; then
  GRAMMAR_EXE=\"${CMAKE_BINARY_DIR}/Release/grammar_gen\"

  elif [ -x \"${CMAKE_BINARY_DIR}/Debug/grammar_gen\" ]; then
    GRAMMAR_EXE=\"${CMAKE_BINARY_DIR}/Debug/grammar_gen\"

    elif [ -x \"${CMAKE_BINARY_DIR}/grammar_gen\" ]; then
      GRAMMAR_EXE=\"${CMAKE_BINARY_DIR}/grammar_gen\"

      elif [ -x \"${CMAKE_BINARY_DIR}/RelWithDebInfo/grammar_gen\" ]; then
        GRAMMAR_EXE=\"${CMAKE_BINARY_DIR}/RelWithDebInfo/grammar_gen\"

        elif [ -x \"${CMAKE_BINARY_DIR}/MinSizeRel/grammar_gen\" ]; then
          GRAMMAR_EXE=\"${CMAKE_BINARY_DIR}/MinSizeRel/grammar_gen\"

          else
            echo \"ERROR: Could not find grammar_gen\"
            echo \"Looked in:\"
            echo \"  ${CMAKE_BINARY_DIR}/Release/grammar_gen\"
            echo \"  ${CMAKE_BINARY_DIR}/Debug/grammar_gen\"
            echo \"  ${CMAKE_BINARY_DIR}/grammar_gen\"
            echo \"  ${CMAKE_BINARY_DIR}/RelWithDebInfo/grammar_gen\"
            echo \"  ${CMAKE_BINARY_DIR}/MinSizeRel/grammar_gen\"
            exit 1
          fi
          
          echo \"Found executable: \$GRAMMAR_EXE\"
            
          # Run the grammar generator
          echo \"Running: \$GRAMMAR_EXE \\\"${CMAKE_BINARY_DIR}/grammars/\$GRAMMAR_FILE\\\" \$N_GENERATION \\\"${CMAKE_BINARY_DIR}/grammars/\$OUTPUT_GRAMMAR_PATH\\\"\"
          \"\$GRAMMAR_EXE\" \"${CMAKE_BINARY_DIR}/grammars/\$GRAMMAR_FILE\" \"\$N_GENERATION\" \"${CMAKE_BINARY_DIR}/grammars/\$OUTPUT_GRAMMAR_PATH\"
            
          EXIT_CODE=\$?
          if [ \$EXIT_CODE -ne 0 ]; then
            echo \"ERROR: Grammar generation failed with error code \$EXIT_CODE\"
            exit \$EXIT_CODE
          fi
            
          echo \"Grammar generation completed successfully\"
          echo \"Output saved to: ${CMAKE_BINARY_DIR}/grammars/\$OUTPUT_GRAMMAR_PATH\"
          "
)
            
# Make the script executable
file(CHMOD ${CMAKE_BINARY_DIR}/run_grammar.sh
PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
GROUP_READ GROUP_EXECUTE
WORLD_READ WORLD_EXECUTE)
endif()

# Add custom targets to run the programs
add_custom_target(run_grammar
    DEPENDS grammar_gen
    COMMAND ${CMAKE_BINARY_DIR}/${RUN_GRAMMAR_SCRIPT}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running L-systems generator"
)

# install executable
install(TARGETS grammar_gen DESTINATION bin)

# Output configuration information
message(STATUS "L-systems configuration:")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Default grammar: ${DEFAULT_GRAMMAR_FILE}")
message(STATUS "  Grammar output: ${DEFAULT_OUTPUT_PATH}")
