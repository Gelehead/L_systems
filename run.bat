@echo off
set N_GENERATION=0
set GRAMMAR_FILE=cube_thing.txt
set OUTPUT_GRAMMAR_PATH="../build/grammars/gram_gen.txt"

::python script part
set PENCIL_SIZE=4
set ANGLE=90

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
