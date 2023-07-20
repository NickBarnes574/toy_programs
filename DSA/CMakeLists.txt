cmake_minimum_required(VERSION 3.16)
project(dsalib VERSION 0.0.0 LANGUAGES "C")

include_directories(${dsalib_SOURCE_DIR}/include)

find_program(CLANG_TIDY_PROG clang-tidy)
if(CLANG_TIDY_PROG)
        set(CMAKE_C_CLANG_TIDY 
        ${CLANG_TIDY_PROG};
        "--checks=* -llvm-include-order, -cppcoreguidelines-*, -readability-magic-numbers, -clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling, -hiccp-no-assembler")
        set(CMAKE_C_FLAGS "-g")
    else()
        set(CMAKE_C_COMPILER gcc)
        set(CMAKE_C_FLAGS "-g -Wall -pedantic")
    endif()

if(EXISTS ${dsalib_SOURCE_DIR}/src/linked_list.c)
    add_library(linked_list SHARED ${dsalib_SOURCE_DIR}/src/linked_list.c)
    target_link_libraries(linked_list cunit Common)
endif()