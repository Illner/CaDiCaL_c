cmake_minimum_required(VERSION 3.14)
project(CaDiCaL)

set(CMAKE_CXX_STANDARD 20)

# Include the root directory
include_directories(${CMAKE_SOURCE_DIR})

add_compile_definitions(NBUILD)

include(CheckFunctionExists)
check_function_exists(closefrom HAVE_CLOSEFROM)

# Define macro if not available
IF (NOT HAVE_CLOSEFROM)
    add_compile_definitions(NCLOSEFROM)
ENDIF ()

# Collect all .cpp files from the CaDiCaL source directory
file(GLOB CADICAL_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/CaDiCaL/src/*.cpp")

# Add the executable
add_executable(CaDiCaL main.cpp ${CADICAL_SRC_FILES})

# set(CADICAL_HOME "${CMAKE_SOURCE_DIR}/")

# Custom function to find the library and check if it was found
FUNCTION(find_and_check_library LIBRARY_VAR LIBRARY_NAME LIBRARY_PATH)
    find_library(${LIBRARY_VAR} ${LIBRARY_NAME} PATHS ${LIBRARY_PATH} NO_SYSTEM_ENVIRONMENT_PATH NO_DEFAULT_PATH)

    # The library was NOT found
    IF (${LIBRARY_VAR} STREQUAL "${LIBRARY_VAR}-NOTFOUND")
        message(FATAL_ERROR "${LIBRARY_NAME} was NOT found in ${LIBRARY_PATH}!")
    # The library was found
    ELSE ()
        target_link_libraries(CaDiCaL PRIVATE ${${LIBRARY_VAR}})
    ENDIF ()
ENDFUNCTION()

#[===[
# macOS
IF (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    # Apple Silicon
    IF (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "arm64")
        message(STATUS "Operating system: macOS (Apple Silicon)")
        find_and_check_library(CaDiCaLLibrary "libcadical.a" "${CADICAL_HOME}/macOS/Apple Silicon/")
    # Intel
    ELSE ()
        message(STATUS "Operating system: macOS (Intel)")
        find_and_check_library(CaDiCaLLibrary "libcadical.a" "${CADICAL_HOME}/macOS/Intel/")
    ENDIF ()

# Windows
ELSEIF ((${CMAKE_SYSTEM_NAME} STREQUAL "Windows") OR (CMAKE_SYSTEM_NAME STREQUAL "CYGWIN"))
    message(STATUS "Operating system: Windows")
    find_and_check_library(CaDiCaLLibrary "libcadical.a" "${CADICAL_HOME}/Windows/")

# Linux
ELSEIF (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    message(STATUS "Operating system: Linux")
    find_and_check_library(CaDiCaLLibrary "libcadical.a" "${CADICAL_HOME}/Linux/")

# Undefined
ELSE ()
    message(FATAL_ERROR "Your operating system (" ${CMAKE_SYSTEM_NAME} ") is not supported!")
ENDIF ()
]===]
