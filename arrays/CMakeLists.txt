project(arrays)
include_directories(include)
add_library(arrays
        src/arrays.c)
target_include_directories(arrays PUBLIC include)

set(ARRAY_EXAMPLES
        array2d_examples)

foreach(EXAMPLE ${ARRAY_EXAMPLES})
    add_executable(${EXAMPLE} exe/${EXAMPLE}.c)
    target_link_libraries(${EXAMPLE} arrays)
endforeach()