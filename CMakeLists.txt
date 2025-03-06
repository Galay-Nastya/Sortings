cmake_minimum_required(VERSION 3.10)

project(sort_strings)

set(CMAKE_C_STANDARD 99)

option(USE_MMAP "Use mmap for file reading" OFF)

set(SOURCES
    src/sort_strings.c
    lib/sortings.c
    lib/reader.c
)

add_executable(sort_strings ${SOURCES})

target_include_directories(sort_strings PRIVATE ${CMAKE_SOURCE_DIR}/lib)

target_compile_options(sort_strings PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
    -fsanitize=address
    -fno-omit-frame-pointer
)

target_link_options(sort_strings PRIVATE -fsanitize=address)

if(USE_MMAP)
    target_compile_definitions(sort_strings PRIVATE USE_MMAP)
endif()

add_executable(tests tests/test_sortings.c lib/sortings.c lib/reader.c)

target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/lib)

if(USE_MMAP)
    target_compile_definitions(tests PRIVATE USE_MMAP)
endif()

configure_file(${CMAKE_SOURCE_DIR}/input.txt ${CMAKE_BINARY_DIR}/input.txt COPYONLY)

enable_testing()

add_test(NAME tests COMMAND tests WORKING_DIRECTORY ${CMAKE_BINARY_DIR})