project(arrays)
include_directories(include)
add_library(arrays
        src/arrays.c)
target_include_directories(arrays PUBLIC include)

add_executable(array_examples exe/array_examples.c)
target_link_libraries(array_examples arrays)

#set(ARRAY_EXAMPLES
#        array_examples)
#
#foreach(EXAMPLE ${ARRAY_EXAMPLES})
#    add_executable(${EXAMPLE} exe/${EXAMPLE}.c)
#    target_link_libraries(${EXAMPLE} arrays)
#endforeach()