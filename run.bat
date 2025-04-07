setlocal enabledelayedexpansion
@echo off
set N_GENERATION=5
set GRAMMAR_FILE=test.txt
set OUTPUT_GRAMMAR_PATH="../build/grammars/gram_gen.txt"

::python script part
set PENCIL_SIZE=1
set ANGLE=90

:: Check if build directory exists, create if not
if not exist "build" (
    echo Build directory not found. Creating build directory...
    mkdir build
)

cd build
echo Running initial CMake configuration...
cmake -G "MinGW Makefiles" ..
cd ..

:: build project
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .

:: generate grammar and put it inside grammar folder
grammar_gen.exe "..\src\grammars\%GRAMMAR_FILE%" %N_GENERATION% %OUTPUT_GRAMMAR_PATH%

:: interpret grammar
cd "..\src\Python" 
python interpreter.py %PENCIL_SIZE% %ANGLE% %OUTPUT_GRAMMAR_PATH%
cd "..\..\" 
