@echo off
setlocal enabledelayedexpansion

set N_GENERATION=5
set GRAMMAR_FILE=cube_thing.txt
set OUTPUT_GRAMMAR_PATH=gram_gen.txt

:: Python script parameters
set PENCIL_SIZE=1
set ANGLE=22.5

if "%1" == "1" (
    call build.bat
)

echo -- Manual Grammar Generation --

:: Create necessary directories if they don't exist
if not exist "build" mkdir build
if not exist "build\grammars" mkdir "build\grammars"

:: Check if executable exists
if exist "build\Release\grammar_gen.exe" (
    set GRAMMAR_EXE="build\Release\grammar_gen.exe"
) else (
    echo ERROR: grammar_gen.exe not found in build\Release\
    pause
    exit /b 1
)

:: Check if input grammar file exists
if not exist "src\grammars\%GRAMMAR_FILE%" (
    echo ERROR: Input grammar file not found: src\grammars\%GRAMMAR_FILE%
    pause
    exit /b 1
)

echo Running: %GRAMMAR_EXE% "src\grammars\%GRAMMAR_FILE%" %N_GENERATION% "build\grammars\%OUTPUT_GRAMMAR_PATH%"
%GRAMMAR_EXE% "src\grammars\%GRAMMAR_FILE%" %N_GENERATION% "build\grammars\%OUTPUT_GRAMMAR_PATH%"

:: Check if grammar generation was successful
if not exist "build\grammars\%OUTPUT_GRAMMAR_PATH%" (
    echo ERROR: Grammar generation failed - output file not created
    pause
    exit /b 1
)

:: Run Python interpreter
@REM echo -- Running Python interpreter --
@REM cd "src\Python"
@REM python interpreter.py %PENCIL_SIZE% %ANGLE% "..\..\build\grammars\%OUTPUT_GRAMMAR_PATH%"
@REM cd "..\..\"

@REM echo -- running python tester -- 
@REM cd "src\Python"
@REM python verifyer.py "..\..\build\grammars\%OUTPUT_GRAMMAR_PATH%" > "..\..\test.txt"
@REM cd "..\..\"

echo -- Process completed successfully --