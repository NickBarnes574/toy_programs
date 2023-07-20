cmake_minimum_required(VERSION 3.16)

project(SDL2Test)

set(SOURCES
    src/sdl_functions.c
    src/sdl_main.c
    )

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(SDL2Test ${SOURCES})

target_include_directories(SDL2Test PRIVATE include/)

target_link_libraries(SDL2Test LINK_PUBLIC Common ${SDL2_LIBRARIES})

set_target_properties(SDL2Test PROPERTIES OUTPUT_NAME sdl2test RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin") # change output name and location