cmake_minimum_required(VERSION 3.16)

project(Typewriter)

set(SOURCES
    src/typewriter_functions.c
    src/typewriter_main.c
    )

add_executable(CMAKE_PROJECT_NAME ${SOURCES})

target_include_directories(CMAKE_PROJECT_NAME PRIVATE include/)

target_link_libraries(CMAKE_PROJECT_NAME LINK_PUBLIC Common)

set_target_properties(CMAKE_PROJECT_NAME PROPERTIES OUTPUT_NAME typewriter RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin") # change output name and location