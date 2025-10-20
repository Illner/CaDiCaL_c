# Top-Level CMakeLists.txt
cmake_minimum_required(VERSION 3.14)

project(Hydra)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_OSX_DEPLOYMENT_TARGET 14.0)

# Add CaDiCaL
add_subdirectory(CaDiCaL)

add_executable(Hydra "main.cpp")

target_link_libraries(Hydra PRIVATE CaDiCaLLibrary)
