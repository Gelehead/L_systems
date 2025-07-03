@echo off
setlocal enabledelayedexpansion

set N_GENERATION=4000
set GRAMMAR_FILE=test.txt
set OUTPUT_GRAMMAR_PATH=gram_gen.txt

:: Python script parameters
set PENCIL_SIZE=3
set ANGLE=22.5

if %1 == 1 (
    call build.bat
)
echo -- Manual Grammar Generation --

:: Check if executable exists
if exist "build\Release\grammar_gen.exe" (
    set GRAMMAR_EXE="build\Release\grammar_gen.exe"
) else (
    echo ERROR: grammar_gen.exe not found in build\Release\
    pause
    exit /b 1
)

:: echo Running: %GRAMMAR_EXE% "build\grammars\%GRAMMAR_FILE%" %N_GENERATION% "build\grammars\%OUTPUT_GRAMMAR_PATH%"
%GRAMMAR_EXE% "build\grammars\%GRAMMAR_FILE%" %N_GENERATION% "build\grammars\%OUTPUT_GRAMMAR_PATH%"

@REM :: Run Python interpreter
@REM echo -- Running Python interpreter --
@REM cd "src\Python"
@REM python interpreter.py %PENCIL_SIZE% %ANGLE% "..\..\build\grammars\%OUTPUT_GRAMMAR_PATH%"
@REM cd "..\..\"

echo -- Process completed successfully --