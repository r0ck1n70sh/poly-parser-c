cmake_minimum_required (VERSION 3.13)

add_subdirectory("lib/Polyterm")

project (poly_parser)

# debug
# set(CMAKE_BUILD_TYPE Debug)
add_executable (main "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c")
target_link_libraries (main PRIVATE Polyterm) 
