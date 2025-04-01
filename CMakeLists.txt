cmake_minimum_required(VERSION 3.14)
project(CaDiCaL)

set(CMAKE_CXX_STANDARD 20)

add_executable(CaDiCaL main.cpp)

# macOS
IF (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    # Apple Silicon
    IF (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "arm64")
        message("Operating system: macOS (Apple Silicon)")
        target_link_libraries(CaDiCaL "${CMAKE_SOURCE_DIR}/macOS/Apple Silicon/libcadical.a")
    # Intel
    ELSE ()
        message("Operating system: macOS (Intel)")
        target_link_libraries(CaDiCaL "${CMAKE_SOURCE_DIR}/macOS/Intel/libcadical.a")
    ENDIF ()

# Windows
ELSEIF ((${CMAKE_SYSTEM_NAME} STREQUAL "Windows") OR (CMAKE_SYSTEM_NAME STREQUAL "CYGWIN"))
    message("Operating system: Windows")
    target_link_libraries(CaDiCaL ${CMAKE_SOURCE_DIR}/Windows/libcadical.a)

# Linux
ELSEIF (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    message("Operating system: Linux")
    target_link_libraries(CaDiCaL ${CMAKE_SOURCE_DIR}/Linux/libcadical.a)

# Undefined
ELSE ()
    message(FATAL_ERROR "Your operating system (" ${CMAKE_SYSTEM_NAME} ") is not supported!")
ENDIF ()
