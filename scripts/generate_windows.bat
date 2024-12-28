@echo off

:: Ensure script exits on error
setlocal enabledelayedexpansion

:: Check if VCPKG_ROOT is set
if "%VCPKG_ROOT%"=="" (
    echo VCPKG_ROOT is not set. Please set it to the vcpkg installation path.
    exit /b 1
)

:: Delete existing build directory if it exists
if exist build rmdir /s /q build

:: Generate build files
cmake -S . -B build -G "Visual Studio 17 2022" ^
    -DCMAKE_BUILD_TYPE=Release ^
    -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake

echo Build files generated for Windows.