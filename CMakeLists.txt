cmake_minimum_required(VERSION 3.16)

project(
    ToyPrograms
    LANGUAGES "C"
    DESCRIPTION "Toy Programs v1.0"
)

include(toy_main.cmake)

include_directories(0_Common/include)

if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/0_Common/CMakeLists.txt")
    add_subdirectory(0_Common)
endif()

if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/1_Typewriter/CMakeLists.txt")
    add_subdirectory(1_Typewriter)
endif()

# EOF
