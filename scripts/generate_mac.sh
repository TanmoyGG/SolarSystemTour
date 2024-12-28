#!/bin/bash

# Ensure script exits on error
set -e

# Check if VCPKG_ROOT is set
if [ -z "$VCPKG_ROOT" ]; then
    echo "VCPKG_ROOT is not set. Please set it to the vcpkg installation path."
    exit 1
fi

# Delete existing build directory if it exists
if [ -d "build" ]; then
    rm -rf build
fi

# Generate build files
cmake -S . -B build -G "Xcode" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake

echo "Build files generated for macOS."