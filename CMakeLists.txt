cmake_minimum_required(VERSION 3.15)
project(espresso LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/espresso
)

# Source files
file(GLOB SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/*.cxx
)

# Header files (optional, for IDEs)
file(GLOB HEADER_FILES
    ${CMAKE_SOURCE_DIR}/include/*.hxx
    ${CMAKE_SOURCE_DIR}/include/espresso/*.hxx
)

# Create static library (change to SHARED for DLL)
add_library(espresso STATIC ${SRC_FILES} ${HEADER_FILES})
# Precompiled header support (CMake 3.16+)
target_precompile_headers(espresso PRIVATE src/stdhdr.hxx)

# Optionally, set output directory
set_target_properties(espresso PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    OUTPUT_NAME "espresso"
    OUTPUT_NAME_DEBUG "espressod"
)

# Example: add executable if you have a main
# add_executable(espresso_main src/main.cxx)
# target_link_libraries(espresso_main espresso)

# Platform-specific settings (macOS example)
if(APPLE)
    # Add macOS-specific flags or frameworks here
endif()
