# Top-Level CMakeLists.txt
cmake_minimum_required(VERSION 3.14)

project(CaDiCaL_c)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_OSX_DEPLOYMENT_TARGET 14.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-stringop-overread -Wno-class-memaccess -Wno-unknown-warning-option")  # CaDiCaL

# Add CaDiCaL
add_subdirectory(CaDiCaL)

add_executable(CaDiCaL_c "main.cpp")

target_link_libraries(CaDiCaL_c PRIVATE CaDiCaLLibrary)
