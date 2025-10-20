#!/bin/bash

# Exit immediately if any command fails
set -e

# Remove the build directory if it exists
if [ -d build ]; then rm -rf build; fi

mkdir build
cd build

# Release
mkdir Release
cd Release
cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Release "../.."
make -j8

cd ..

# Debug
mkdir Debug
cd Debug
cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug "../.."
make -j8

cd ..
