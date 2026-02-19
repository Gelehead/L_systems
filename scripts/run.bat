@echo off
setlocal enabledelayedexpansion

echo -- Full Project Build --

:: Clean build
echo -- Cleaning project --
if exist build rmdir /s /q build
mkdir build

:: Configure with CMake
echo -- Configuring project --
cmake -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_MAP_TEST=OFF
if %ERRORLEVEL% neq 0 (
    echo ERROR: CMake configuration failed
    pause
    exit /b 1
)

:: Build project (only grammar_gen and perlin_gen, skip Map_test)
echo -- Building project --
cd build
cmake --build . --config Release --target grammar_gen --target perlin_gen
if %ERRORLEVEL% neq 0 (
    echo ERROR: Build failed
    cd ..
    pause
    exit /b 1
)

cd ..

echo -- Build completed successfully --
