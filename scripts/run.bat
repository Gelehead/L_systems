@echo off
setlocal enabledelayedexpansion

echo -- Full Project Build --

set BUILD_TYPE=Debug
set GENERATOR=Visual Studio 17 2022

:: Clean build
echo -- Cleaning project --
if exist build rmdir /s /q build
mkdir build

:: Configure with CMake
echo -- Configuring project --
cmake -S . -B build -G "%GENERATOR%" -A x64
if %ERRORLEVEL% neq 0 (
    echo ERROR: CMake configuration failed
    pause
    exit /b 1
)

:: Build projects
echo -- Building project --
cd build
cmake --build . --config %BUILD_TYPE% --target grammarEngine
if %ERRORLEVEL% neq 0 (
    echo ERROR: Build failed
    cd ..
    pause
    exit /b 1
)

cd ..

echo -- Build completed successfully --