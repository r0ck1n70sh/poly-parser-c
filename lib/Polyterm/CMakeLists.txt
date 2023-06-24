cmake_minimum_required (VERSION 3.12)

project (Polyterm)

# export lib
add_library (Polyterm)
target_include_directories (Polyterm PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/lib")
target_sources(Polyterm PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/Polyterm.c")


# unit tests

# debug
# set(CMAKE_BUILD_TYPE Debug)

add_executable (test_polyterm "${CMAKE_CURRENT_SOURCE_DIR}/test/test_polyterm.c")
target_include_directories (test_polyterm PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/lib")
target_sources(test_polyterm PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/Polyterm.c")
