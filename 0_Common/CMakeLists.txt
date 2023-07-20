set(LIBRARY_SOURCES
    src/math_functions_32_bit.c
    src/math_functions_64_bit.c
    src/utilities.c
    src/number_converter.c
    src/file_io.c
    src/misc.c
    )

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(Common ${LIBRARY_SOURCES})

target_include_directories(Common PUBLIC include/)