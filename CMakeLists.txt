cmake_minimum_required(VERSION 3.26)
project(AdventOfCode)

set(CMAKE_CXX_STANDARD 23)

if (BENCHMARK_ONLY)
    add_compile_definitions(BENCHMARK_ONLY)
endif ()
if (PART1)
    add_compile_definitions(PART1)
endif ()
if (PART2)
    add_compile_definitions(PART2)
endif ()


add_subdirectory(src)
